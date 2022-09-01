find_package(gtest REQUIRED)

include(GoogleTest)

macro(add_gtest name)
	add_executable (${name} "${name}.cpp")
        target_link_libraries (${name} PRIVATE GTest::gtest GTest::gtest_main ${LIBRARY_NAME})
        gtest_discover_tests(${name})
endmacro()

add_gtest(tests)
