cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME MY_PROJECT)

option(${PROJECT_NAME}_TESTING "Build the tests." OFF)
option(${PROJECT_NAME}_BENCHMARKS "Build the benchmarks." OFF)
option(${PROJECT_NAME}_EXAMPLES "Build the examples." OFF)
option(${PROJECT_NAME}_PROFILING "Enable profiling support." OFF)
option(${PROJECT_NAME}_DOCS "Build the docs." OFF)

if(${PROJECT_NAME}_TESTING)
  list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

if(${PROJECT_NAME}_BENCHMARKS)
  list(APPEND VCPKG_MANIFEST_FEATURES "benchmarks")
endif()

if(${PROJECT_NAME}_EXAMPLES)
  list(APPEND VCPKG_MANIFEST_FEATURES "examples")
endif()

if(${PROJECT_NAME}_PROFILING)
  list(APPEND VCPKG_MANIFEST_FEATURES "profiling")
endif()

if(${PROJECT_NAME}_DOCS)
  list(APPEND VCPKG_MANIFEST_FEATURES "docs")
endif()

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(${PROJECT_NAME})

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(external)

if(${PROJECT_NAME}_TESTING)
  enable_testing()
  add_subdirector(tests)
endif()

if(${PROJECT_NAME}_EXAMPLES)
  add_subdirectory(examples)
endif()

if(${PROJECT_NAME}_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()

if(${PROJECT_NAME}_DOCS)
  add_subdirectory(docs)
endif()

