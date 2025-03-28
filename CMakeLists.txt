cmake_minimum_required(VERSION 3.16)
project(zbuild VERSION 0.1.0 LANGUAGES CXX)

# Set standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/Users/nicholasraynes/Qt6")

# Use folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Find Qt6 dynamically (Core, Gui, Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Wrapper library (shared for dynamic linking)
add_library(zbuild SHARED
    src/main.cpp
    # Add more .cpp files here
)

# Public headers exposed for users
target_include_directories(zbuild
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Dynamically link Qt
target_link_libraries(zbuild
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# Export wrapper as a CMake package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/zbuildConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "cmake/zbuildConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/zbuildConfig.cmake"
    INSTALL_DESTINATION lib/cmake/zbuild
)

install(TARGETS zbuild
    EXPORT zbuildTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT zbuildTargets
    FILE zbuildTargets.cmake
    NAMESPACE zbuild::
    DESTINATION lib/cmake/zbuild
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/zbuildConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/zbuildConfigVersion.cmake"
    DESTINATION lib/cmake/zbuild
)
