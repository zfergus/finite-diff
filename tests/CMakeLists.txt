################################################################################
# Tests
################################################################################

add_executable(finitediff_tests
  test_gradient.cpp
  test_jacobian.cpp
  test_hessian.cpp
  test_flatten.cpp
)

################################################################################
# Required Libraries
################################################################################

target_link_libraries(finitediff_tests PUBLIC finitediff::finitediff)

include(finitediff_warnings)
target_link_libraries(finitediff_tests PRIVATE finitediff::warnings)

include(catch2)
target_link_libraries(finitediff_tests PUBLIC Catch2::Catch2WithMain)

################################################################################
# Compiler options
################################################################################

# target_compile_definitions(${PROJECT_NAME}_tests PUBLIC CATCH_CONFIG_ENABLE_BENCHMARKING)

################################################################################
# Register tests
################################################################################

FetchContent_GetProperties(catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)

# Register tests
set(PARSE_CATCH_TESTS_ADD_TO_CONFIGURE_DEPENDS ON)
catch_discover_tests(finitediff_tests)
