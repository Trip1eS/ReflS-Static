#pragma once

#include "Member.hpp"
#include "Traits.hpp"

#include <type_traits>

namespace ReflS {

template<typename...>
struct List;

template<typename, typename, typename>
struct Function;

template<typename T>
struct Argument {
	using Type = T;
};

namespace Detail {

	template<typename>
	struct FunctionTrait;

	template<typename _Ret, typename... _Args>
	struct FunctionTrait<_Ret(_Args...)> {
		using ReturnType			  = _Ret;
		static constexpr auto ArgList = List<Argument<_Args>...> {};
	};

} // namespace Detail

template<typename _Name, typename _PointerLambda, typename _AttrList = List<>>
struct Function : Member<_Name, _PointerLambda, _AttrList>,
				  Detail::FunctionTrait<
					  typename Detail::MemberTrait<decltype(_PointerLambda {}())>::Type> {

	constexpr Function(_Name, _PointerLambda, _AttrList = {}) {}
	constexpr Function() = default;
};

} // namespace ReflS