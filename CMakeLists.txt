cmake_minimum_required(VERSION 3.19)
project(ZBuild VERSION 0.1.0 LANGUAGES CXX)
file(WRITE "${CMAKE_BINARY_DIR}/zbuild_version.txt" ${PROJECT_VERSION})
file(WRITE "${CMAKE_BINARY_DIR}/zbuild_name.txt" ${PROJECT_NAME})

# Set standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Use folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Find Qt6 dynamically (Core, Gui, Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Wrapper library (shared for dynamic linking)
file(GLOB_RECURSE ZBUILD_HEADERS CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
)

file(GLOB_RECURSE ZBUILD_SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE ZBUILD_TESTS CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/test/*.cpp"
)

add_library(ZBuild SHARED ${ZBUILD_SOURCES} ${ZBUILD_HEADERS})

set(INCLUDE_DIRS "")
foreach(path IN LISTS ZBUILD_HEADERS)
    get_filename_component(dir ${path} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${dir})
endforeach()

foreach(path IN LISTS ZBUILD_SOURCES)
    get_filename_component(dir ${path} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

# Public headers exposed for users
target_include_directories(ZBuild
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${INCLUDE_DIRS}
)

# Dynamically link Qt
target_link_libraries(ZBuild
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# Export wrapper as a CMake package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ZBuildConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "cmake/ZBuildConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/ZBuildConfig.cmake"
    INSTALL_DESTINATION lib/cmake/ZBuild
)

install(TARGETS ZBuild
    EXPORT ZBuildTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES ${ZBUILD_HEADERS} DESTINATION include/ZBuild)
install(EXPORT ZBuildTargets
    FILE ZBuildTargets.cmake
    NAMESPACE ZBuild::
    DESTINATION lib/cmake/ZBuild
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ZBuildConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ZBuildConfigVersion.cmake"
    DESTINATION lib/cmake/ZBuild
)

# Run custom scripts.
if(DEFINED ENV{ZBUILD_AUTO_PACKAGE})
    add_custom_target(auto_package ALL
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/cmake/ZBuildPackage.cmake
    )
    add_dependencies(auto_package ZBuild)
    if(DEFINED ENV{ZBUILD_AUTO_INSTALL})
        add_custom_target(auto_install ALL
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/cmake/ZBuildInstall.cmake
        )
        add_dependencies(auto_install auto_package)
    endif()
endif()

foreach(path IN LISTS ZBUILD_TESTS)
    get_filename_component(filename ${path} NAME)
    string(REPLACE ".cpp" "" testname ${filename})
    add_executable(${testname} ${path})
    target_link_libraries(${testname}
        PRIVATE
            ZBuild
    )
endforeach()
