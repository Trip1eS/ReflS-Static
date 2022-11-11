#pragma once

#include <type_traits>

#include "List.hpp"

namespace ReflS {

template<typename _Type, typename... _Args>
struct Constructor {
	static constexpr decltype(auto) Invoke(_Args&&... args) {
		return _Type {std::forward<_Args>(args)...};
	}
};

} // namespace ReflS