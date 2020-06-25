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

# Eigen
function(finite_diff_download_eigen)
    finite_diff_download_project(eigen
        URL           http://bitbucket.org/eigen/eigen/get/3.3.7.tar.bz2
        URL_MD5       05b1f7511c93980c385ebe11bd3c93fa
    )
endfunction()

## spdlog
function(finite_diff_download_spdlog)
    finite_diff_download_project(spdlog
       GIT_REPOSITORY https://github.com/gabime/spdlog.git
       GIT_TAG        v1.3.1
    )
endfunction()

# Catch2 for unit tests
function(finite_diff_download_catch2)
  finite_diff_download_project(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.12.2
  )
endfunction()
