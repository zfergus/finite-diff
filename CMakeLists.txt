cmake_minimum_required(VERSION 3.9)
project(FiniteDiff)

################################################################################

# project-options
option(FINITE_DIFF_BUILD_UNIT_TESTS         "Build unit-tests"      OFF)

################################################################################

### Configuration
set(FINITE_DIFF_EXTERNAL "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(Warnings)
include(${PROJECT_NAME}Dependencies)

################################################################################
# FiniteDiff Library
################################################################################

add_library(${PROJECT_NAME} "finitediff.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

################################################################################
# Required Libraries
################################################################################

# Eigen
target_link_libraries(${PROJECT_NAME} PUBLIC Eigen3::Eigen)

# Logger
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

# Extra warnings
target_link_libraries(${PROJECT_NAME} PRIVATE warnings::all)

################################################################################
# Compiler options
################################################################################

# Use C++11
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

################################################################################
# Tests
################################################################################

if(FINITE_DIFF_BUILD_UNIT_TESTS)
    # Catch2
    if(NOT TARGET Catch2::Catch2)
        finite_diff_download_catch2()
        add_subdirectory(${FINITE_DIFF_EXTERNAL}/Catch2 catch2)
        list(APPEND CMAKE_MODULE_PATH ${FINITE_DIFF_EXTERNAL}/Catch2/contrib)
    endif()

    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()
