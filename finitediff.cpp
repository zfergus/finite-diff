// Functions to compute gradients using finite difference.
// Based on the functions in https://github.com/PatWie/CppNumericalSolvers
// and rewritten to use Eigen
#include "finitediff.hpp"

#include <array>
#include <vector>

namespace fd {

// Compute the gradient of a function at a point using finite differences.
void finite_gradient(const Eigen::VectorXd& x,
    std::function<double(const Eigen::VectorXd&)> f,
    Eigen::VectorXd& grad,
    AccuracyOrder accuracy,
    const double eps)
{
    // Create an array of the coefficients for finite differences.
    // See: https://en.wikipedia.org/wiki/Finite_difference_coefficient
    // clang-format off
    // The external coefficients, c1, in c1 * f(x + c2).
    static const std::array<std::vector<double>, 4> coeff =
    { { {1, -1}, {1, -8, 8, -1}, {-1, 9, -45, 45, -9, 1}, {3, -32, 168, -672, 672, -168, 32, -3} } };
    // The internal coefficients, c2, in c1 * f(x + c2).
    static const std::array<std::vector<double>, 4> coeff2 =
    { { {1, -1}, {-2, -1, 1, 2}, {-3, -2, -1, 1, 2, 3}, {-4, -3, -2, -1, 1, 2, 3, 4} } };
    // clang-format on
    // The denominators of the finite difference.
    static const std::array<double, 4> dd = { { 2, 12, 60, 840 } };

    grad.resize(x.rows());

    const size_t innerSteps = 2 * (accuracy + 1);
    const double ddVal = dd[accuracy] * eps;

    Eigen::VectorXd xx = x;
    for (long d = 0; d < x.rows(); d++) {
        grad[d] = 0;
        for (size_t s = 0; s < innerSteps; ++s) {
            double tmp = x[d];
            xx[d] += coeff2[accuracy][s] * eps;
            grad[d] += coeff[accuracy][s] * f(xx);
            xx[d] = tmp;
        }
        grad[d] /= ddVal;
    }
}

void finite_jacobian(const Eigen::VectorXd& x,
    std::function<Eigen::VectorXd(const Eigen::VectorXd&)> f,
    Eigen::MatrixXd& jac,
    const AccuracyOrder accuracy,
    const double eps)
{
    // Create an array of the coefficients for finite differences.
    // See: https://en.wikipedia.org/wiki/Finite_difference_coefficient
    // clang-format off
    // The external coefficients, c1, in c1 * f(x + c2).
    static const std::array<std::vector<double>, 4> coeff =
    { { {1, -1}, {1, -8, 8, -1}, {-1, 9, -45, 45, -9, 1}, {3, -32, 168, -672, 672, -168, 32, -3} } };
    // The internal coefficients, c2, in c1 * f(x + c2).
    static const std::array<std::vector<double>, 4> coeff2 =
    { { {1, -1}, {-2, -1, 1, 2}, {-3, -2, -1, 1, 2, 3}, {-4, -3, -2, -1, 1, 2, 3, 4} } };
    // clang-format on
    // The denominators of the finite difference.
    static const std::array<double, 4> dd = { { 2, 12, 60, 840 } };

    jac.resize(f(x).rows(), x.rows());

    const size_t innerSteps = 2 * (accuracy + 1);
    const double ddVal = dd[accuracy] * eps;

    Eigen::VectorXd xx = x;
    for (long d = 0; d < x.rows(); d++) {
        jac.col(d).setZero();
        for (size_t s = 0; s < innerSteps; ++s) {
            double tmp = x[d];
            xx[d] += coeff2[accuracy][s] * eps;
            jac.col(d) += coeff[accuracy][s] * f(xx);
            xx[d] = tmp;
        }
        jac.col(d) /= ddVal;
    }
}

// Compare if two gradients are close enough.
bool compare_gradient(
    const Eigen::VectorXd& x, const Eigen::VectorXd& y, const double test_eps)
{
    assert(x.rows() == y.rows());

    bool same = true;
    for (long d = 0; d < x.rows(); ++d) {
        double scale = std::max(std::max(fabs(x[d]), fabs(y[d])), double(1.0));
        double abs_diff = fabs(x[d] - y[d]);

        if (abs_diff > test_eps * scale) {
            same = false;
        }
    }
    return same;
}

// Compare if two jacobians are close enough.
bool compare_jacobian(
    const Eigen::MatrixXd& x, const Eigen::MatrixXd& y, const double test_eps)
{
    assert(x.rows() == y.rows());
    assert(x.cols() == y.cols());

    bool same = true;
    for (long d = 0; d < x.rows(); ++d) {
        for (long c = 0; c < x.cols(); ++c) {
            double scale
                = std::max(std::max(fabs(x(d, c)), fabs(y(d, c))), double(1.0));

            double abs_diff = fabs(x(d, c) - y(d, c));

            if (abs_diff > test_eps * scale) {
                same = false;
            }
        }
    }
    return same;
}

} // namespace fd