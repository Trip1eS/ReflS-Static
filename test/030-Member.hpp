#pragma once
#include <catch2/catch_test_macros.hpp>
#include <ReflS/ReflS.hpp>
#include <type_traits>

using namespace ReflS;

namespace Test3 {

struct A {
	int		   a = 0;
	static int s_a;
	int		   f(int x) { return a * x; }
	static int s_f() { return -1; }
	int		   h() { return 0; }
	void	   h(float) {}
};

int A::s_a = 0;

}; // namespace Test3

TEST_CASE("Member") {
	using namespace Test3;

	A a;

	SECTION("Field") {
		constexpr auto a_a = Field(Str<"a"> {}, [] { return &A::a; });
		REQUIRE(a_a.Name == "a");
		REQUIRE(a_a.IsStatic == false);
		REQUIRE(a_a.GetPointer() == &A::a);
		a.a = 1;
		REQUIRE(a_a.Invoke(a) == 1);
		a_a.Invoke(a) = 2;
		REQUIRE(a.a == 2);

		constexpr auto a_s_a = Field(Str<"s_a"> {}, [] { return &A::s_a; });
		REQUIRE(a_s_a.Name == "s_a");
		REQUIRE(a_s_a.IsStatic == true);
		REQUIRE(a_s_a.GetPointer() == &A::s_a);
		// TODO: getting a static data member
	}

	SECTION("Function") {
		constexpr auto a_f = Function(Str<"f"> {}, [] { return &A::f; });
		REQUIRE(a_f.Name == "f");
		REQUIRE(a_f.IsStatic == false);
		REQUIRE(a_f.GetPointer() == &A::f);
		REQUIRE(std::is_same_v<
				std::remove_cvref_t<decltype(a_f.ArgList)>,
				List<Argument<int>>>);
		a.a = 2;
		REQUIRE(a_f.Invoke(a, 3) == 6);

		constexpr auto a_s_f = Function(Str<"s_f"> {}, [] { return &A::s_f; });
		REQUIRE(a_s_f.Name == "s_f");
		REQUIRE(a_s_f.IsStatic == true);
		REQUIRE(a_s_f.GetPointer() == &A::s_f);
		REQUIRE(std::is_same_v<std::remove_cvref_t<decltype(a_s_f.ArgList)>, List<>>);
		REQUIRE(a_s_f.Invoke() == -1);
	}

	SECTION("Function overloading") {
		constexpr auto h1 =
			Function(Str<"h"> {}, []() -> MemberPointerType<A, int()> { return &A::h; });
		constexpr auto h2 =
			Function(Str<"h"> {}, []() -> MemberPointerType<A, void(float)> {
				return &A::h;
			});
		REQUIRE(std::is_same_v<typename decltype(h1)::ReturnType, int>);
		REQUIRE(std::is_same_v<std::remove_cvref_t<decltype(h1.ArgList)>, List<>>);
		REQUIRE(std::is_same_v<typename decltype(h2)::ReturnType, void>);
		REQUIRE(std::is_same_v<
				std::remove_cvref_t<decltype(h2.ArgList)>,
				List<Argument<float>>>);
	}
}