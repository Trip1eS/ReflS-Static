cmake_minimum_required(VERSION 3.13.4)
#project(ReflS-Tests)

add_subdirectory(3rdparty/Catch2)

set(sources 000-TestCases.cpp)

add_executable(ReflS-Test ${sources})
target_link_libraries(ReflS-Test PRIVATE ReflS Catch2::Catch2)
target_compile_features(ReflS-Test PRIVATE cxx_std_20)
# target_include_directories(ReflS-Test PRIVATE ${REFLS_INCLUDE_DIR})
target_compile_definitions(ReflS-Test PRIVATE)

if (MINGW)
    # MingW cannot dynamic link stdc++?
    target_link_libraries(ReflS-Test PRIVATE -static-libstdc++)
endif()