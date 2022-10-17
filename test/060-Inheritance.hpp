#pragma once
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <ReflS/ReflS.hpp>
#include <type_traits>

namespace Test6 {

struct A {
	int			a = 99;
	virtual int f() { return a + 1; }
	virtual int h() { return a * 2; }
};

struct B : A {
	int			b = 0;
	virtual int f() { return b + 2; }
};

struct C : B {
	int			c = 0;
	virtual int f() { return c + 3; }
};

} // namespace Test6

REFLS_TYPE(
	Test6::A,
	BASES(),
	CTORS(DEFAULT_CTOR()),
	MEMBERS(FIELD(a), FUNCTION(f), FUNCTION(h))
);
REFLS_TYPE(
	Test6::B,
	BASES(Test6::A),
	CTORS(DEFAULT_CTOR()),
	MEMBERS(FIELD(b), FUNCTION(f))
);
REFLS_TYPE(
	Test6::C,
	BASES(Test6::B),
	CTORS(DEFAULT_CTOR()),
	MEMBERS(FIELD(c), FUNCTION(f))
);

TEST_CASE("Inheritance") {
	constexpr auto tA = TypeDescriptor<Test6::A> {};
	constexpr auto tB = TypeDescriptor<Test6::B> {};
	constexpr auto tC = TypeDescriptor<Test6::C> {};

	SECTION("Bases") {
		REQUIRE(tA.DeclaredBases.Size == 0);
		REQUIRE(tA.Bases.Size == 0);

		REQUIRE(tB.DeclaredBases.Size == 1);
		REQUIRE(tB.Bases.Size == 1);
		REQUIRE(std::is_same_v<decltype(tB.Bases.Get<0>()), BaseInfo<Test6::A>>);

		REQUIRE(tC.DeclaredBases.Size == 1);
		REQUIRE(tC.Bases.Size == 2);
	}

	SECTION("Members") {
		REQUIRE(tB.DeclaredMembers.Size == 2);
		REQUIRE(tB.Members.Size == 4); // a, b, f, h

		REQUIRE(tC.DeclaredMembers.Size == 2);
		REQUIRE(tC.Members.Size == 5); // a, b, c, f, h
	}
}