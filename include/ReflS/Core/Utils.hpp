#pragma once

namespace ReflS {

namespace Detail {
	template<typename _Parent, typename _Type>
	struct MemberPointerTypeImpl {
		using Type = _Type _Parent::*;
	};
} // namespace Detail

template<typename _Parent, typename _Type>
using MemberPointerType = typename Detail::MemberPointerTypeImpl<_Parent, _Type>::Type;

template<typename...>
struct List;

namespace Detail {
	template<template<typename> typename Tmpl, typename... Args>
	struct MakeListForEachImpl;

	template<template<typename> typename Tmpl, typename Arg0, typename... Args>
	struct MakeListForEachImpl<Tmpl, Arg0, Args...> {
		using Result = List<Tmpl<Arg0>, Tmpl<Args>...>;
	};

	template<template<typename> typename Tmpl>
	struct MakeListForEachImpl<Tmpl> {
		using Result = List<>;
	};

} // namespace Detail

template<template<typename> typename Tmpl, typename... Args>
inline constexpr auto MakeListForEach =
	typename Detail::MakeListForEachImpl<Tmpl, Args...>::Result {};

} // namespace ReflS