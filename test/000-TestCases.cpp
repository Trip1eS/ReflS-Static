#define CATCH_CONFIG_RUNNER
#include <catch2/catch_all.hpp>

#include "010-Str.hpp"
#include "020-List.hpp"
#include "030-Member.hpp"
#include "040-TypeInfo.hpp"
#include "050-Attribute.hpp"
#include "060-Inheritance.hpp"

int main(int argc, const char* argv[]) {
	return Catch::Session().run(argc, argv);
}