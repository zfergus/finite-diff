# Finite Differences

[![Build Status](https://github.com/zfergus/finite-diff/actions/workflows/continuous.yml/badge.svg)](https://github.com/zfergus/finite-diff/actions/workflows/continuous.yml)
[![License](https://img.shields.io/github/license/zfergus/finite-diff.svg?color=blue)](https://opensource.org/licenses/MIT)

**A simple finite-difference library using Eigen.**

## Usage

### Add it to CMake

The easiest way to add the library to an existing CMake project is to download it through CMake.
CMake provides functionality for doing this called [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) (requires CMake ≥ 3.14).
We use this same process to download all external dependencies.
For example,

```CMake
include(FetchContent)
FetchContent_Declare(
    finite-diff
    GIT_REPOSITORY https://github.com/zfergus/finite-diff.git
    GIT_TAG ${FINITE_DIFF_GIT_TAG}
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(finite-diff)
```

where `FINITE_DIFF_GIT_TAG` is set to the version you want to use. This will download and add the library to CMake. The library can then be linked against using

```CMake
target_link_libraries(${TARGET_NAME} PUBLIC finitediff::finitediff)
```

where `TARGET_NAME` is the name of your library/executable.

### API

All functiononality can be included with `#include <finitediff.hpp>`.

The library provides three main function `finite_gradient`, `finite_jacobian`, and `finite_hessian`.

#### `finite_gradient`:

```c++
void finite_gradient(
    const Eigen::VectorXd& x,
    const std::function<double(const Eigen::VectorXd&)>& f,
    Eigen::VectorXd& grad,
    const AccuracyOrder accuracy = SECOND,
    const double eps = 1.0e-8);
```

The `finite_gradient` function computes the [gradient](https://en.wikipedia.org/wiki/Gradient) (first derivative) `grad` of a function `f: ℝⁿ ↦ ℝ` at a point `x`. This will result in a vector of size `n`.

#### `finite_jacobian`:

```c++
void finite_jacobian(
    const Eigen::VectorXd& x,
    const std::function<Eigen::VectorXd(const Eigen::VectorXd&)>& f,
    Eigen::MatrixXd& jac,
    const AccuracyOrder accuracy = SECOND,
    const double eps = 1.0e-8);
```

The `finite_jacobian` function computes the [Jacobian](https://en.wikipedia.org/wiki/Jacobian_matrix_and_determinant) (first derivative) `jac` of a function `f: ℝⁿ ↦ ℝᵐ` at a point `x`. This will result in a matrix of size `m × n`.


#### `finite_hessian`:

```c++
void finite_hessian(
    const Eigen::VectorXd& x,
    const std::function<double(const Eigen::VectorXd&)>& f,
    Eigen::MatrixXd& hess,
    const AccuracyOrder accuracy = SECOND,
    const double eps = 1.0e-5);
```

The `finite_hessian` function computes the [Hessian](https://en.wikipedia.org/wiki/Hessian_matrix) (second derivative) `hess` of a function `f: ℝⁿ ↦ ℝ` at a point `x`. This will result in a matrix of size `n × n`.

#### `AccuracyOrder`:

Each finite difference function takes as input the accuracy order for the method. Possible options are:
```c++
enum AccuracyOrder {
    SECOND, // Second order accuracy.
    FOURTH, // Fourth order accuracy.
    SIXTH,  // Sixth order accuracy.
    EIGHTH  // Eighth order accuracy.
};
```

#### `eps`:

The parameter `eps` is the finite difference step size. Smaller values result in a more accuracate approximation, but too small of a value can result in large numerical error because the difference will be divided by a small number.

## Dependencies

**All dependancies are downloaded through CMake** depending on the build options.
The following libraries are used in this project:

* [Eigen](https://eigen.tuxfamily.org/): linear algebra
* [spdlog](https://github.com/gabime/spdlog): logging information

### Optional

* [Catch2](https://github.com/catchorg/Catch2.git): testing (see [Unit Tests](#unit_tests))

## <a name="unit_tests"></a>Unit Tests

We provide unit tests for ensuring the correctness of our functions.
To enable the unit tests use the flag `-DFINITE_DIFF_BUILD_UNIT_TESTS=ON` with CMake.

## Contributing

This project is open for contributors! Contibutions can come in the form of feature requests, bug fixes, documentation, tutorials and the like. We highly recommend to file an Issue first before submitting a Pull Request.

Simply fork this repository and make a Pull Request! We'd definitely appreciate:

* Implementation of new features
* Bug Reports
* Documentation
* Testing

## License

MIT License © 2019, Zachary Ferguson (See [`LICENSE.txt`](https://github.com/zfergus/finite-diff/blob/main/LICENSE) for details).

### Acknowledgements

Based on the functions in [CppNumericalSolvers](https://github.com/PatWie/CppNumericalSolvers/blob/v2/include/cppoptlib/utils/derivatives.h)
by Patrick Wieschollek and rewritten to use Eigen.
