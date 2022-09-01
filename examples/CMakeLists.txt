macro(add_example name)
	add_executable (${name} "${name}.cpp")
        target_link_libraries (${name} PRIVATE ${LIBRARY_NAME})
endmacro()

add_benchmark(benchmark)
