#pragma once

#include "List.hpp"
#include "Utils.hpp"

namespace ReflS {

template<typename>
struct TypeInfo;

template<typename _Type>
struct BaseInfo {
	using Type = _Type;
	static constexpr TypeInfo<_Type> Info {};
};

template<typename... Args>
inline constexpr auto MakeBaseList = MakeListForEach<BaseInfo, Args...>;

} // namespace ReflS