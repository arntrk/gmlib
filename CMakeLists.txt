cmake_minimum_required(VERSION 3.15)

project(SplineBasis LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS On)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_library(${PROJECT_NAME} INTERFACE)

# target_link_libraries()

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)


if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()


if (BUILD_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(tests)
endif()
