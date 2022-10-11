#pragma once
#include <catch2/catch_test_macros.hpp>
#include <ReflS/ReflS.hpp>
#include <string>
#include <type_traits>

using namespace ReflS;

template<int N>
struct Int {
	static constexpr int Value = N;
};

TEST_CASE("List") {
	SECTION("Basic properties") {
		REQUIRE(List<>::Size == 0);
		REQUIRE(List<int>::Size == 1);
		REQUIRE(List<int, float>::Size == 2);
	}

	SECTION("MakeListForEach") {
		REQUIRE(std::is_same_v<
				std::remove_cvref_t<decltype(MakeListForEach<BaseInfo, int, float>)>,
				List<BaseInfo<int>, BaseInfo<float>>>);
	}

	SECTION("Get") {
		REQUIRE(std::is_same_v<decltype(List<float, int>::Get<0>()), float>);
		REQUIRE(std::is_same_v<decltype(List<float, int>::Get<1>()), int>);
	}

	SECTION("ForEach") {
		using TestList = List<Int<2>, Int<0>, Int<3>>;

		std::string result;
		TestList::ForEach([&](auto m) { result += std::to_string(m.Value); });
		REQUIRE(result == "203");

		result = "";
		TestList::ForEach([&]<typename T>(T m) {
			if constexpr (T::Value != 0) {
				result += std::to_string(m.Value);
			}
		});
		REQUIRE(result == "23");
	}

	SECTION("Find") {
		using TestList = List<Int<2>, Int<0>, Int<3>>;
		REQUIRE(std::is_same_v<
				decltype(TestList::Find([](auto m) { return m.Value == 2; })),
				Int<2>>);
		REQUIRE(TestList::FindIndex([](auto m) { return m.Value == 3; }) == 2);
	}

	SECTION("Filter") {
		using TestList = List<Int<2>, Int<0>, Int<3>, Int<10>, Int<19>>;
		REQUIRE(std::is_same_v<
				decltype(TestList::Filter([](auto m) { return m.Value % 2 == 0; })),
				List<Int<2>, Int<0>, Int<10>>>);
	}

	SECTION("Map") {
		using TestList = List<Int<2>, Int<0>, Int<3>, Int<10>, Int<19>>;
		REQUIRE(std::is_same_v<
				decltype(TestList::Map([](auto m) { return Int<m.Value * 2> {}; })),
				List<Int<4>, Int<0>, Int<6>, Int<20>, Int<38>>>);
	}

	SECTION("Contains") {
		using TestList = List<Int<2>, Int<0>, Int<3>>;
		REQUIRE(TestList::Contains<Int<2>>());
		REQUIRE_FALSE(TestList::Contains<Int<1>>());
	}

	SECTION("Insert") {
		using TestList = List<Int<2>, Int<0>>;
		REQUIRE(std::is_same_v<
				decltype(TestList::Insert(Int<1> {})),
				List<Int<2>, Int<0>, Int<1>>>);
		REQUIRE(std::is_same_v<decltype(TestList::Insert(Int<0> {})), TestList>);
	}

	SECTION("InsertList") {
		using TestList = List<Int<2>, Int<0>>;
		REQUIRE(std::is_same_v<
				decltype(TestList::InsertList(List<Int<2>, Int<3>> {})),
				List<Int<2>, Int<0>, Int<3>>>);
	}

	SECTION("PushBack") {
		using TestList = List<Int<2>, Int<0>>;
		REQUIRE(std::is_same_v<
				decltype(TestList::PushBack(Int<0> {})),
				List<Int<2>, Int<0>, Int<0>>>);
	}

	SECTION("Concat") {
		using TestList = List<Int<2>, Int<0>>;
		REQUIRE(std::is_same_v<
				decltype(TestList::Concat(List<Int<2>, Int<3>> {})),
				List<Int<2>, Int<0>, Int<2>, Int<3>>>);
		// ReflS::Detail::ListImpl
	}
}