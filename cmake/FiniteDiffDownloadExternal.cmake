include(DownloadProject)

# With CMake 3.8 and above, we can hide warnings about git being in a
# detached head by passing an extra GIT_CONFIG option
if(NOT (${CMAKE_VERSION} VERSION_LESS "3.8.0"))
  set(${PROJECT_NAME}_EXTRA_OPTIONS "GIT_CONFIG advice.detachedHead=false")
else()
  set(${PROJECT_NAME}_EXTRA_OPTIONS "")
endif()

function(custom_download_project name)
  download_project(
    PROJ         ${name}
    SOURCE_DIR   ${${PROJECT_NAME}_EXTERNAL}/${name}
    DOWNLOAD_DIR ${${PROJECT_NAME}_EXTERNAL}/.cache/${name}
    QUIET
    ${${PROJECT_NAME}_EXTRA_OPTIONS}
    ${ARGN}
  )
endfunction()

################################################################################

## Eigen
function(download_eigen)
	custom_download_project(eigen
		GIT_REPOSITORY https://github.com/eigenteam/eigen-git-mirror.git
		GIT_TAG        3.3.7
	)
endfunction()
