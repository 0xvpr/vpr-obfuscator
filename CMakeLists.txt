cmake_minimum_required( VERSION 3.14 FATAL_ERROR )

project( vpr-obf
         LANGUAGES CXX )

set( CMAKE_CXX_STANDARD          20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
#set( CMAKE_CXX_EXTENSIONS      OFF )

project(
    vpr-obfuscator
    VERSION 1.0.0
    DESCRIPTION "VPR's compile-time obfuscator for C++20 and later"
    LANGUAGES CXX
)

option(VPR_OBF_BUILD_TESTS "Build tests for vpr obfuscator" ON)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# If you need modern features, set this to 20 or 23 as needed:
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
)

install(DIRECTORY include/
        DESTINATION include
)

include(CMakePackageConfigHelpers)

install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE vpr::
  DESTINATION lib/cmake/${PROJECT_NAME}
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION lib/cmake/${PROJECT_NAME}
)

if(VPR_OBF_BUILD_TESTS)
    enable_testing()
    add_subdirectory( ut )
endif()
