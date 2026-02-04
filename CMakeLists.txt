# Detects whether this is a top-level project
get_directory_property(HAS_PARENT PARENT_DIRECTORY)
if(HAS_PARENT)
    set(FINITE_DIFF_TOPLEVEL_PROJECT OFF)
else()
    set(FINITE_DIFF_TOPLEVEL_PROJECT ON)
endif()

# Check required CMake version
set(REQUIRED_CMAKE_VERSION "3.14.0")
if(FINITE_DIFF_TOPLEVEL_PROJECT)
    cmake_minimum_required(VERSION ${REQUIRED_CMAKE_VERSION})
else()
    # Don't use cmake_minimum_required here to avoid implicitly overriding parent policies
    if(${CMAKE_VERSION} VERSION_LESS ${REQUIRED_CMAKE_VERSION})
        message(FATAL_ERROR "CMake required version to build finite-diff is ${REQUIRED_CMAKE_VERSION}")
    endif()
endif()

################################################################################

project(FiniteDiff
        DESCRIPTION "A simple finite difference library."
        LANGUAGES CXX)

option(FINITE_DIFF_BUILD_UNIT_TESTS  "Build unit-tests"  ${FINITE_DIFF_TOPLEVEL_PROJECT})

# Set default minimum C++ standard
if(FINITE_DIFF_TOPLEVEL_PROJECT)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/finitediff/")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/recipes/")

include(finitediff_cpm_cache)

################################################################################
# Finite Diff Library
################################################################################

add_library(finitediff_finitediff
    src/finitediff.cpp
)
add_library(finitediff::finitediff ALIAS finitediff_finitediff)

# Public include directory
target_include_directories(finitediff_finitediff PUBLIC src)

################################################################################
# Optional Definitions
################################################################################

# For MSVC, do not use the min and max macros.
target_compile_definitions(finitediff_finitediff PUBLIC NOMINMAX)

################################################################################
# Dependencies
################################################################################

# Extra warnings
include(finitediff_warnings)
target_link_libraries(finitediff_finitediff PRIVATE finitediff::warnings)

# Eigen
include(eigen)
target_link_libraries(finitediff_finitediff PUBLIC Eigen3::Eigen)

# Logger
include(spdlog)
target_link_libraries(finitediff_finitediff PUBLIC spdlog::spdlog)

################################################################################
# Compiler options
################################################################################

# Use C++17
target_compile_features(finitediff_finitediff PUBLIC cxx_std_17)

################################################################################
# Tests
################################################################################

if(FINITE_DIFF_BUILD_UNIT_TESTS)
    include(CTest)
    enable_testing()

    add_subdirectory(tests)
endif()
