# Prepare dependencies
#
# For each third-party library, if the appropriate target doesn't exist yet,
# download it via external project, and add_subdirectory to build it alongside
# this project.


# Download and update 3rd_party libraries
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
include(${PROJECT_NAME}DownloadExternal)

################################################################################
# Required libraries
################################################################################

# Eigen
if(NOT TARGET Eigen3::Eigen)
  download_eigen()
  add_library(${PROJECT_NAME}_eigen INTERFACE)
  target_include_directories(${PROJECT_NAME}_eigen SYSTEM INTERFACE
    $<BUILD_INTERFACE:${FINITE_DIFF_EXTERNAL}/eigen>
    $<INSTALL_INTERFACE:include>
  )
  set_property(TARGET ${PROJECT_NAME}_eigen PROPERTY EXPORT_NAME Eigen3::Eigen)
  add_library(Eigen3::Eigen ALIAS ${PROJECT_NAME}_eigen)
endif()

# spdlog
if(NOT TARGET spdlog::spdlog)
    download_spdlog()
    add_library(spdlog INTERFACE)
    add_library(spdlog::spdlog ALIAS spdlog)
    target_include_directories(spdlog SYSTEM INTERFACE ${FIXING_COLLISIONS_EXTERNAL}/spdlog/include)
    target_compile_definitions(spdlog INTERFACE -DSPDLOG_FMT_EXTERNAL)
    target_link_libraries(spdlog INTERFACE fmt::fmt)
endif()
