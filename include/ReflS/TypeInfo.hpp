#pragma once

#include "List.hpp"

namespace ReflS {

template<typename... Ts>
struct List;

template<typename _Type>
struct TypeInfo {
	using Type = _Type;

	/**
	 * For the "Reflectable" concept.
	 * Having this struct defined means the user has not specialized
	 * TypeInfo<T> for the type.
	 */
	struct InvalidMarker {};

	static constexpr std::string_view Name {};

	static constexpr List Bases {};
	static constexpr List Members {};
};

template<typename T>
concept Unreflectable = requires { typename TypeInfo<T>::InvalidMarker; };

template<typename T>
concept Reflectable = !
Unreflectable<T>;

namespace Detail {

	template<Reflectable Type>
	constexpr auto GetBases(Type = {}) {
		return TypeInfo<Type>::Bases.Accumulate(List<> {}, [](auto r, auto e) {
			if constexpr (e.Info.Bases.Size == 0) {
				return r.Insert(e);
			} else {
				return r.Insert(e)
					.InsertList(e.Info.Bases)
					.InsertList(e.Info.Bases.Accumulate(List<> {}, [](auto r, auto e) {
						return r.InsertList(GetBases<typename decltype(e)::Type>());
					}));
			}
		});
	}

	template<Reflectable Type>
	constexpr auto GetMembers(Type = {}) {
		return GetBases<Type>().Accumulate(TypeInfo<Type>::Members, [](auto r, auto e) {
			return r.template InsertList<decltype(e.Info.Members), MemberEqualComp>(
				e.Info.Members
			);
		});
	}

} // namespace Detail

template<Reflectable _Type>
struct TypeDescriptor {
	using Info = TypeInfo<_Type>;
	using Type = _Type;

	static constexpr auto Name = Info::Name;

	static constexpr auto DeclaredMembers = Info::Members;
	static constexpr auto DeclaredBases	  = Info::Bases;
	static constexpr auto Bases			  = Detail::GetBases<Type>();
	static constexpr auto Members		  = Detail::GetMembers<Type>();
};

} // namespace ReflS