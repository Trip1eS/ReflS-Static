#pragma once

#include <algorithm>
#include <cstdint>
#include <tuple>

namespace ReflS {

namespace Detail {

	template<class L, class F, class R>
	constexpr auto AccumulateImpl(const L&, F&&, R r, std::index_sequence<>) {
		return r;
	}

	template<class L, class F, class R, std::size_t N0, std::size_t... Ns>
	constexpr auto
	AccumulateImpl(const L& l, F&& f, R r, std::index_sequence<N0, Ns...>) {
		return AccumulateImpl(
			l,
			std::forward<F>(f),
			f(std::move(r), l.template Get<N0>()),
			std::index_sequence<Ns...> {}
		);
	}

	struct DefaultCompare {
		template<typename T, typename U>
		constexpr bool operator()(T = {}, U = {}) {
			return std::is_same_v<T, U>;
		}
	};

	template<template<typename...> typename ListTmpl, typename... Ts>
	struct ListImpl {
		static constexpr std::tuple<Ts...> Elems {};
		static constexpr size_t			   Size = sizeof...(Ts);

		constexpr ListImpl(Ts...) {}

		template<size_t N>
		static constexpr auto Get();

		template<class Init, class Func>
		static constexpr auto Accumulate(Init init, Func&& func);

		template<typename Func>
		static constexpr auto ForEach(Func&& func);

		template<typename Pred>
		static constexpr size_t FindIndex(Pred pred);

		template<typename Pred>
		static constexpr auto Find(Pred pred);

		template<typename Pred>
		static constexpr auto Filter(Pred pred);

		template<typename Unary>
		static constexpr auto Map(Unary unary);

		template<typename T, typename Comp = DefaultCompare>
		static constexpr bool Contains(T = {});

		template<typename T, typename Comp = DefaultCompare>
		static constexpr auto Insert(T = {});

		template<typename ListType, typename Comp = DefaultCompare>
		static constexpr auto InsertList(ListType list = {});

		template<typename T>
		static constexpr auto PushBack(T = {});

		template<typename ListType>
		static constexpr auto Concat(ListType list = {});
	};

} // namespace Detail

template<typename...>
struct List;

template<>
struct List<> : Detail::ListImpl<List> {
	constexpr List() : Detail::ListImpl<List>() {}
};

template<typename T, typename... Ts>
struct List<T, Ts...> : Detail::ListImpl<List, T, Ts...> {
	constexpr List() : Detail::ListImpl<List, T, Ts...>(T {}, Ts {}...) {}
	constexpr List(T, Ts...) : Detail::ListImpl<List, T, Ts...>(T {}, Ts {}...) {}
};

template<typename T, typename... Ts>
List(T, Ts...) -> List<T, Ts...>;

} // namespace ReflS

#include "Impl/List.inl"