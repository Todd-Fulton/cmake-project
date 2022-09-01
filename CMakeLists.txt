cmake_minimum_required(VERSION 3.20)

# TODO: Change MY_PROJECT to your project name
set(PROJECT_NAME hello)

# TODO: Make sure a valid library name
set(LIBRARY_NAME hello)

option(${PROJECT_NAME}_TESTING "Build the tests." OFF)
option(${PROJECT_NAME}_BENCHMARKS "Build the benchmarks." OFF)
option(${PROJECT_NAME}_EXAMPLES "Build the examples." OFF)
option(${PROJECT_NAME}_PROFILING "Enable profiling support." OFF)

set(${PROJECT_NAME}_SANITIZERS "" CACHE STRING
  "Enable sanatizers. [Address;Memory;MemoryWithOrigins;Undefined;Thread;Leak;CFI]"
)

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

set(USE_SANITIZER "${PROJECT_NAME}_SANITIZERS")

# Include external dependencies not available in vcpkg
add_subdirectory(external)

project(${PROJECT_NAME})

# Use upcomming C++23, and no extensions
cxx_23()

add_library(${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:include>
)

if(${CMAKE_CXX_COMPILER_ID} IN_LIST "Clang;GNU")
  target_code_coverage(${LIBRARY_NAME})
  target_link_time_optimization(${LIBRARY_NAME})
endif()

add_subdirectory(include)
add_subdirectory(src)

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

