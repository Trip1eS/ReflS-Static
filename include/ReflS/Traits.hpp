#pragma once

#include <type_traits>

namespace ReflS {

namespace Detail {
	template<class, template<class, class...> class>
	struct IsInstanceImpl : public std::false_type {};

	template<class... Ts, template<class, class...> class U>
	struct IsInstanceImpl<U<Ts...>, U> : public std::true_type {};
} // namespace Detail

template<class T, template<class, class...> class U>
inline constexpr bool IsInstance = Detail::IsInstanceImpl<T, U>::value;

} // namespace ReflS