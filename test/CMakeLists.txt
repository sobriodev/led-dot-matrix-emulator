include_directories(${leddotmatrixemulator_SOURCE_DIR}/lib)
add_executable(test main.c)
target_link_libraries(test lib)
