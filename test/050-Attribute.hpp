#pragma once
#include <catch2/catch_test_macros.hpp>
#include <ReflS/ReflS.hpp>
#include <type_traits>

#include <iostream>

using namespace ReflS;

struct Range {
	float min;
	float max;
};

struct AttrTest {
	static constexpr List Attributes {ATTR(Range {.min = -1.0f, .max = 1.0f})};
};

TEST_CASE("Attribute") {
	SECTION("") {
		constexpr auto range =
			AttrTest::Attributes
				.Find([](auto attr) {
					return std::is_same_v<typename decltype(attr)::Type, Range>;
				})
				.Get();
		REQUIRE(range.min == -1.0f);
		REQUIRE(range.max == 1.0f);
	}
}