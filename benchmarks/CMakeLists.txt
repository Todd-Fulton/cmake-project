find_package(benchmark REQUIRED)

macro(add_benchmark name)
	add_executable (${name} "${name}.cpp")
        target_link_libraries (${name} PRIVATE benchmark::benchmark ${LIBRARY_NAME})
endmacro()

add_benchmark(benchmark)
