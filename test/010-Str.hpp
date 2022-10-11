#pragma once
#include <catch2/catch_test_macros.hpp>
#include <ReflS/ReflS.hpp>
#include <type_traits>

using namespace ReflS;

TEST_CASE("Str") {
	SECTION("Str") {
		constexpr auto str = Str<"Test"> {};
		REQUIRE(str.View() == std::string_view {"Test"});
		char c_str[] = "Test";
		REQUIRE(std::strcmp(str.Data(), c_str) == 0);
		REQUIRE(str.Size() == 4);
	}
}