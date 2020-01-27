cmake_minimum_required(VERSION 3.9)
project(FiniteDiff)

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
