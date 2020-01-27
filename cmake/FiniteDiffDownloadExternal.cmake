include(DownloadProject)

# With CMake 3.8 and above, we can hide warnings about git being in a
# detached head by passing an extra GIT_CONFIG option
if(NOT (${CMAKE_VERSION} VERSION_LESS "3.8.0"))
  set(FINITE_DIFF_EXTRA_OPTIONS "GIT_CONFIG advice.detachedHead=false")
else()
  set(FINITE_DIFF_EXTRA_OPTIONS "")
endif()

function(finite_diff_download_project name)
  download_project(
    PROJ         ${name}
    SOURCE_DIR   ${FINITE_DIFF_EXTERNAL}/${name}
    DOWNLOAD_DIR ${FINITE_DIFF_EXTERNAL}/.cache/${name}
    QUIET
    ${FINITE_DIFF_EXTRA_OPTIONS}
    ${ARGN}
  )
endfunction()

################################################################################

## Eigen
function(download_eigen)
	finite_diff_download_project(eigen
		GIT_REPOSITORY https://github.com/eigenteam/eigen-git-mirror.git
		GIT_TAG        3.3.7
	)
endfunction()

## spdlog
function(download_spdlog)
    finite_diff_download_project(spdlog
       GIT_REPOSITORY https://github.com/gabime/spdlog.git
       GIT_TAG        v1.3.1
    )
endfunction()
