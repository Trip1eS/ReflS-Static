#pragma once

#include "../List.hpp"

namespace ReflS::Detail {

template<template<typename...> typename ListTmpl, typename... Ts>
template<size_t N>
constexpr auto ListImpl<ListTmpl, Ts...>::Get() {
	return std::get<N>(Elems);
}

template<template<typename...> typename ListTmpl, typename... Ts>
template<class Init, class Func>
constexpr auto ListImpl<ListTmpl, Ts...>::Accumulate(Init init, Func&& func) {
	return AccumulateImpl(
		ListTmpl<Ts...> {},
		std::forward<Func>(func),
		std::move(init),
		std::make_index_sequence<Size> {}
	);
}

template<template<typename...> typename ListTmpl, typename... Ts>
template<typename Func>
constexpr auto ListImpl<ListTmpl, Ts...>::ForEach(Func&& func) {
	return std::apply(
		[&](const auto&... elems) { (std::forward<Func>(func)(elems), ...); },
		Elems
	);
}

template<template<typename...> typename ListTmpl, typename... Ts>
template<typename Pred>
constexpr size_t ListImpl<ListTmpl, Ts...>::FindIndex(Pred pred) {
	size_t index		= Size;
	size_t currentIndex = 0;
	bool   found		= false;
	ForEach([&](auto& elem) {
		if (!found && pred(elem)) {
			index = currentIndex;
			found = true;
		}
		++currentIndex;
	});
	return index;
}

template<template<typename...> typename ListTmpl, typename... Ts>
template<typename Pred>
constexpr auto ListImpl<ListTmpl, Ts...>::Find(Pred pred) {
	constexpr auto idx = FindIndex(pred);
	return Get<idx>();
}

template<template<typename...> typename ListTmpl, typename... Ts>
template<typename Pred>
constexpr auto ListImpl<ListTmpl, Ts...>::Filter(Pred pred) {
	return Accumulate(
		ListTmpl<> {},
		[&]<typename ListType, typename MemberType>(ListType r, MemberType e) {
			if constexpr (pred(MemberType {})) {
				return r.Insert(MemberType {});
			} else {
				return r;
			}
		}
	);
}

template<template<typename...> typename ListTmpl, typename... Ts>
template<typename Unary>
constexpr auto ListImpl<ListTmpl, Ts...>::Map(Unary unary) {
	return Accumulate(ListTmpl<> {}, [&](auto r, auto e) { return r.Insert(unary(e)); });
}

template<template<typename...> typename ListTmpl, typename... Ts>
template<typename T, typename Comp>
constexpr bool ListImpl<ListTmpl, Ts...>::Contains(T) {
	return (Comp {}(Ts {}, T {}) || ...);
}

template<template<typename...> typename ListTmpl, typename... Ts>
template<typename T, typename Comp>
constexpr auto ListImpl<ListTmpl, Ts...>::Insert(T) {
	if constexpr (Contains<T, Comp>()) {
		return ListTmpl<Ts...> {};
	} else {
		return ListTmpl<Ts..., T> {};
	}
}

template<template<typename...> typename ListTmpl, typename... Ts>
template<typename ListType, typename Comp>
constexpr auto ListImpl<ListTmpl, Ts...>::InsertList(ListType list) {
	return list.Accumulate(ListTmpl<Ts...> {}, [](auto r, auto e) {
		return r.template Insert<decltype(e), Comp>(e);
	});
}

template<template<typename...> typename ListTmpl, typename... Ts>
template<typename T>
constexpr auto ListImpl<ListTmpl, Ts...>::PushBack(T) {
	return ListTmpl<Ts..., T> {};
}

template<template<typename...> typename ListTmpl, typename... Ts>
template<typename ListType>
constexpr auto ListImpl<ListTmpl, Ts...>::Concat(ListType list) {
	return list.Accumulate(ListTmpl<Ts...> {}, [](auto r, auto e) {
		return r.PushBack(e);
	});
}

} // namespace ReflS::Detail