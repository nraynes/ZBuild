# ZBuildInstall.cmake
cmake_minimum_required(VERSION 3.16)
message(STATUS "Installing project")

# === CONFIG ===]
file(READ "${CMAKE_CURRENT_LIST_DIR}/../build/zbuild_version.txt" PROJECT_VERSION)
file(READ "${CMAKE_CURRENT_LIST_DIR}/../build/zbuild_name.txt" PROJECT_NAME)
string(STRIP "${PROJECT_VERSION}" PROJECT_VERSION)
string(STRIP "${PROJECT_NAME}" PROJECT_NAME)
set(BUILD_DIR "build")
set(INSTALL_DIR "zbuild-install")
set(HOME_DIR $ENV{HOME})
set(ZBUILD_DIR "${HOME_DIR}/ZBuild")
set(SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/..")
set(INSTALL_PREFIX "${SOURCE_DIR}/${INSTALL_DIR}")
set(PACKAGE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}.tar.gz")
set(PACKAGE_PATH "${INSTALL_PREFIX}/${PACKAGE_NAME}")

# === Step 1: Remove old install ===
if(EXISTS ${ZBUILD_DIR})
    message(STATUS "Removing old install at: ${ZBUILD_DIR}")
    file(REMOVE_RECURSE ${ZBUILD_DIR})
endif()

if(EXISTS ${INSTALL_PREFIX})
    message(STATUS "Installing ZBuild")
    file(MAKE_DIRECTORY ${ZBUILD_DIR})
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${PACKAGE_PATH} ${ZBUILD_DIR})
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar "xzf" ${PACKAGE_NAME}
        WORKING_DIRECTORY ${ZBUILD_DIR}
        RESULT_VARIABLE tar_result
    )
    if(NOT tar_result EQUAL 0)
        message(FATAL_ERROR "Failed to extract ${PROJECT_NAME}: ${tar_result}")
    endif()
    file(REMOVE "${ZBUILD_DIR}/${PACKAGE_NAME}")
    message(STATUS "Done! ZBuild has been installed")
else()
    message(STATUS "Could not find package to install")
endif()
