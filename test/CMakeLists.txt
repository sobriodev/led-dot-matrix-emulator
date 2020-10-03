include_directories(${leddotmatrixemulator_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/unity_framework)

add_subdirectory(unity_framework)

add_executable(test vt100_test_runner.c)
target_link_libraries(test lib unity_framework)
