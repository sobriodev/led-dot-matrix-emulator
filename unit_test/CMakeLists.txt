include_directories(${leddotmatrixemulator_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/unity_framework)

add_subdirectory(unity_framework)

add_executable(unit_test
    main.c
    common_test_suite.h
    common_test_suite.c
    vt100_test_suite.h
    vt100_test_suite.c
)

target_link_libraries(unit_test lib unity_framework)
