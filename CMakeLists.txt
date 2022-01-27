cmake_minimum_required(VERSION 3.15)

project(gmlib VERSION 0.0.2 LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_EXPORT_COMPILE_COMMANDS On)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_library(${PROJECT_NAME} INTERFACE)

message("* Adding module '${CMAKE_PROJECT_NAME}' '${PROJECT_NAME}'")
add_library(${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)


if (BUILD_EXAMPLES)
  add_subdirectory(example)
endif()


if (BUILD_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(tests)
endif()

include(CMakePackageConfigHelpers)

set(config_install_dir  "share/cmake/${PROJECT_NAME}/")
set(targets_export_name "${PROJECT_NAME}-targets")

set(project_config "${PROJECT_NAME}-config.cmake")
set(version_config "${PROJECT_NAME}-config-version.cmake")


configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}-config.cmake.in"
    "${PROJECT_BINARY_DIR}/${project_config}"
    INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
    NO_SET_AND_CHECK_MACRO
)

write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/${version_config}"
    COMPATIBILITY AnyNewerVersion
)


include(GNUInstallDirs)
 
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
     
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h*"
)

install(FILES
    ${CMAKE_BINARY_DIR}/${project_config}
    ${CMAKE_BINARY_DIR}/${version_config}
    DESTINATION ${config_install_dir}
)

install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
  DESTINATION "."
)

install(EXPORT ${targets_export_name}
  NAMESPACE "${PROJECT_NAME}::"
  DESTINATION ${config_install_dir}
)

export(
  TARGETS ${built_components}
  NAMESPACE "${PROJECT_NAME}::"
  FILE ${CMAKE_BINARY_DIR}/${targets_export_name}.cmake
)
