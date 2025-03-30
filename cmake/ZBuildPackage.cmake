# ZBuildPackage.cmake
cmake_minimum_required(VERSION 3.16)
message(STATUS "Packaging project")

# === CONFIG ===]
file(READ "${CMAKE_CURRENT_LIST_DIR}/../build/zbuild_version.txt" PROJECT_VERSION)
file(READ "${CMAKE_CURRENT_LIST_DIR}/../build/zbuild_name.txt" PROJECT_NAME)
string(STRIP "${PROJECT_VERSION}" PROJECT_VERSION)
string(STRIP "${PROJECT_NAME}" PROJECT_NAME)
set(BUILD_DIR "build")
set(INSTALL_DIR "zbuild-install")
set(SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/..")
set(INSTALL_PREFIX "${SOURCE_DIR}/${INSTALL_DIR}")
set(PACKAGE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}.tar.gz")
set(PACKAGE_PATH "${INSTALL_PREFIX}/${PACKAGE_NAME}")

# === Step 1: Remove old install ===
if(EXISTS ${INSTALL_PREFIX})
    message(STATUS "Removing old install at: ${INSTALL_PREFIX}")
    file(REMOVE_RECURSE ${INSTALL_PREFIX})
endif()

# # === Step 2: Install ===
message(STATUS "Installing ${PROJECT_NAME} to ${INSTALL_PREFIX}...")
execute_process(COMMAND ${CMAKE_COMMAND} -B ${BUILD_DIR} -S ${SOURCE_DIR} -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX}
                WORKING_DIRECTORY ${SOURCE_DIR}
                RESULT_VARIABLE install_config_result)
if(NOT install_config_result EQUAL 0)
    message(FATAL_ERROR "Failed to reconfigure for install.")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --install ${BUILD_DIR}
                WORKING_DIRECTORY ${SOURCE_DIR}
                RESULT_VARIABLE install_result)
if(NOT install_result EQUAL 0)
    message(FATAL_ERROR "Failed to install ${PROJECT_NAME}.")
endif()

# # === Step 3: Package ===
message(STATUS "Creating archive ${PACKAGE_NAME} in ${INSTALL_PREFIX}")

file(GLOB INSTALL_CONTENTS "${INSTALL_PREFIX}")

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar "czf" ${PACKAGE_NAME} ${INSTALL_CONTENTS} --format=gnutar
    WORKING_DIRECTORY ${INSTALL_PREFIX}
    RESULT_VARIABLE tar_result
)
if(NOT tar_result EQUAL 0)
    message(FATAL_ERROR "Failed to package ${PROJECT_NAME}: ${tar_result}")
endif()

message(STATUS "Done! Package created at ${PACKAGE_PATH}")