#pragma once
#include <catch2/catch_test_macros.hpp>
#include <ReflS/ReflS.hpp>
#include <type_traits>

using namespace ReflS;

namespace Test4 {
struct A {
	int a = 99;
	int f() { return a + 1; }
};
} // namespace Test4

REFLS_TYPE(Test4::A, BASES(), CTORS(DEFAULT_CTOR()), MEMBERS(FIELD(a), FUNCTION(f)));

TEST_CASE("TypeInfo") {
	using namespace Test4;
	auto TypeA = TypeDescriptor<A> {};

	SECTION("Name") {
		REQUIRE(TypeA.Name == "Test4::A");
	}

	SECTION("Members") {
		REQUIRE(TypeA.DeclaredMembers.Size == 2);
		REQUIRE(TypeA.Members.Size == 2);
	}
}