/**
 * @brief Functions to compute gradients using finite difference.
 *
 * Based on the functions in https://github.com/PatWie/CppNumericalSolvers
 * and rewritten to use Eigen
 */
#pragma once

#include <Eigen/Core>

namespace fd {

/**
 * @brief Enumeration of available orders of accuracy for finite differences.
 *
 * The corresponding integer values are used internally and should be ignored.
 */
enum AccuracyOrder {
    SECOND = 0, ///< @brief Second order accuracy.
    FOURTH = 1, ///< @brief Fourth order accuracy.
    SIXTH = 2,  ///< @brief Sixth order accuracy.
    EIGHTH = 3  ///< @brief Eighth order accuracy.
};

/**
 * @brief Compute the gradient of a function using finite differences.
 *
 * @param[in]  x         Point at which to compute the gradient.
 * @param[in]  f         Compute the gradient of this function.
 * @param[out] grad      Computed gradient.
 * @param[in]  accuracy  Accuracy of the finite differences.
 * @param[in]  eps       Value of the finite difference step.
 */
void finite_gradient(const Eigen::VectorXd& x,
    std::function<double(const Eigen::VectorXd&)> f,
    Eigen::VectorXd& grad,
    AccuracyOrder accuracy = SECOND,
    const double eps = 1.0e-8);

/**
 * @brief Compute the jacobian of a function using finite differences.
 *
 * @param[in]  x         Point at which to compute the gradient.
 * @param[in]  f         Compute the gradient of this function.
 * @param[out] jac       Computed jacobian.
 * @param[in]  accuracy  Accuracy of the finite differences.
 * @param[in]  eps       Value of the finite difference step.
 */
void finite_jacobian(const Eigen::VectorXd& x,
    std::function<Eigen::VectorXd(const Eigen::VectorXd&)> f,
    Eigen::MatrixXd& jac,
    const AccuracyOrder accuracy = SECOND,
    const double eps = 1.0e-8);

/**
 * @brief Compare if two gradients are close enough.
 *
 * @param[in] x         The first gradient to compare.
 * @param[in] y         The second gradient to compare against.
 * @param[in] test_eps  Tolerance of equality.
 *
 * @return A boolean for if x and y are close to the same value.
 */
bool compare_gradient(const Eigen::VectorXd& x,
    const Eigen::VectorXd& y,
    const double test_eps = 1e-4);

/**
 * @brief Compare if two jacobians are close enough.
 *
 * @param[in] x         The first jacobian to compare.
 * @param[in] y         The second jacobian to compare against.
 * @param[in] test_eps  Tolerance of equality.
 *
 * @return A boolean for if x and y are close to the same value.
 */
bool compare_jacobian(const Eigen::MatrixXd& x,
    const Eigen::MatrixXd& y,
    const double test_eps = 1e-4);

} // namespace fd
