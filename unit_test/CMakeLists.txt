include_directories(${leddotmatrixemulator_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/unity_framework)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mock)

add_subdirectory(unity_framework)
add_subdirectory(mock)

add_executable(unit_test
    main.c
    common_test_suite.h
    common_test_suite.c
    vt100_test_suite.h
    vt100_test_suite.c
    device_test_suite.h
    device_test_suite.c
)

target_link_libraries(unit_test lib mock unity_framework)
