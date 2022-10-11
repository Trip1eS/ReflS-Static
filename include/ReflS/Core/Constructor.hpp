#pragma once

#include <type_traits>

#include "List.hpp"

namespace ReflS {

template<typename _Type, typename... _Args>
struct Constructor {
	decltype(auto) Invoke(_Args&&... args) const {
		return _Type {std::forward<_Args>(args)...};
	}
};

template<typename _Type, typename... _Ts>
struct ConstructorList : List<_Ts...> {
	constexpr ConstructorList(_Ts... elems) : List<_Ts...>(elems...) {}
};

/**
 * For classes that have no user-defined constructors
 */
template<typename _Type>
	requires std::is_trivially_constructible_v<_Type>
struct ConstructorList<_Type> : List<Constructor<_Type>> {
	constexpr ConstructorList() : List<Constructor<_Type>>(Constructor<_Type> {}) {}
};

} // namespace ReflS