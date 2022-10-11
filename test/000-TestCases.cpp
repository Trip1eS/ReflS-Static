#define CATCH_CONFIG_RUNNER
#include <catch2/catch_all.hpp>

#include <ReflS/ReflS.hpp>

using namespace ReflS;

#include "010-Str.hpp"
#include "020-List.hpp"
#include "030-Member.hpp"
#include "040-TypeInfo.hpp"
#include "050-Attribute.hpp"
#include "060-Inheritance.hpp"

#include <iostream>
#include <type_traits>

int main(int argc, const char* argv[]) {
	// A4	 a;
	// B4 b;
	// auto members = TypeInfo<B4>::Members;
	// auto f		 = members.Find([](auto m) { return m.Name == "f"; });
	// auto f = Member(Str<"f">{},&B4::f);
	// auto m_b	 = members.Find([](auto m) { return m.Name == "b"; });
	// auto p		 = &B4::f;
	// static_assert(std::is_same_v<decltype(p), decltype(f)::MemberType>);
	// (b.*p)();
	// using MemberType = decltype(&B4::b);
	// std::invoke(f.Type, b);
	// std::cout << std::invoke(m_b.Type, b);

	// using F = Method<Str<"f">, declt>
	// auto fa = Function(Str<"f"> {}, []() { return &A4::f; });
	// auto fb = TypeDescriptor<B4>::Members.Find([](auto m) { return m.Name == "f"; });
	// using F = decltype(fb);

	// TypeDescriptor<B4>::Members.Get<0>();

	// std::cout << TypeDescriptor<B4>::Members.Size << "\n";

	// using T = decltype(&B4::f);

	// static_assert(std::is_same_v<F::ReturnType, int>);
	// static_assert(std::is_same_v<F::ArgList, List<>>);
	// static_assert(!F::IsStatic);
	// static_assert(MemberEqual<decltype(fa), decltype(fb)>);

	// List<>			 l1;
	// List<int, float> l2;
	// List			 l3 {1, 1.0f};

	// static_ass.0f(;!Detail::FunctionEqual<decltype(gb), decltype(fb)>::Value);
	// static_assert()
	// static_assert(std::is_same_v<decltype(&B4::f), decltype(&A4::f)>);

	// std::cout << f.Invoke(b);
	// std::cout << std::invoke(&B4::f, b);
	// fs.ForEach([&](auto m) { std::cout << ":" << m.Invoke(b) << "\n"; });
	// std::cout << members.Find([](auto m) { return m.Name == "f"; }).Invoke(b);
	return Catch::Session().run(argc, argv);
}