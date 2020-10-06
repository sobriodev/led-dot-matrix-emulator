cmake_minimum_required(VERSION 3.5)

project(leddotmatrixemulator LANGUAGES C)

add_subdirectory(lib)
add_subdirectory(unit_test)

enable_testing()
add_test(NAME unit_test COMMAND unit_test)

