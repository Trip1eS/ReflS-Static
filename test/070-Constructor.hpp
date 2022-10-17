#pragma once
#include <catch2/catch_test_macros.hpp>
#include <ReflS/ReflS.hpp>
#include <type_traits>

using namespace ReflS;

namespace Test7 {

struct NoCtor {
	int x;
};

struct DefaultCtor {
	int x;
	DefaultCtor() = default;
};

struct MultiCtor {
	int x;
	MultiCtor() {}
	MultiCtor(int _x) {}
};

struct NoCtorTest {
	static constexpr List Constructors {Constructor<NoCtor> {}};
};

struct DefaultCtorTest {
	static constexpr List Constructors {Constructor<DefaultCtor> {}};
};

struct MultiCtorTest {
	static constexpr List Constructors {
		Constructor<MultiCtor> {},
		Constructor<MultiCtor, int> {}};
};

} // namespace Test7

TEST_CASE("Constructor") {
	using namespace Test7;

	SECTION("Implicitly-declared default constructor") {
		constexpr auto ctor		= NoCtorTest::Constructors.Get<0>();
		auto		   instance = ctor.Invoke();
		REQUIRE(std::is_same_v<decltype(instance), NoCtor>);
	}

	SECTION("Default constructor") {
		constexpr auto ctor		= DefaultCtorTest::Constructors.Get<0>();
		auto		   instance = ctor.Invoke();
		REQUIRE(std::is_same_v<decltype(instance), DefaultCtor>);
	}

	SECTION("Multiple constructors") {
		constexpr auto ctor0	 = MultiCtorTest::Constructors.Get<0>();
		constexpr auto ctor1	 = MultiCtorTest::Constructors.Get<1>();
		auto		   instance0 = ctor0.Invoke();
		auto		   instance1 = ctor1.Invoke(1);
		REQUIRE(std::is_same_v<decltype(instance0), MultiCtor>);
		REQUIRE(std::is_same_v<decltype(instance1), MultiCtor>);
	}
}