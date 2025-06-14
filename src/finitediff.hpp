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
    SECOND, ///< @brief Second order accuracy.
    FOURTH, ///< @brief Fourth order accuracy.
    SIXTH,  ///< @brief Sixth order accuracy.
    EIGHTH  ///< @brief Eighth order accuracy.
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
void finite_gradient(
    const Eigen::Ref<const Eigen::VectorXd>& x,
    const std::function<double(const Eigen::VectorXd&)>& f,
    Eigen::VectorXd& grad,
    const AccuracyOrder accuracy = SECOND,
    const double eps = 1.0e-8);

/**
 * @brief Compute the Jacobian of a function using finite differences.
 *
 * @param[in]  x         Point at which to compute the Jacobian.
 * @param[in]  f         Compute the Jacobian of this function.
 * @param[out] jac       Computed Jacobian.
 * @param[in]  accuracy  Accuracy of the finite differences.
 * @param[in]  eps       Value of the finite difference step.
 */
void finite_jacobian(
    const Eigen::Ref<const Eigen::VectorXd>& x,
    const std::function<Eigen::MatrixXd(const Eigen::VectorXd&)>& f,
    Eigen::MatrixXd& jac,
    const AccuracyOrder accuracy = SECOND,
    const double eps = 1.0e-8);

/**
 * @brief Compute the Hessian of a function using finite differences.
 *
 * @param[in]  x         Point at which to compute the Hessian.
 * @param[in]  f         Compute the Hessian of this function.
 * @param[out] hess      Computed Hessian.
 * @param[in]  accuracy  Accuracy of the finite differences.
 * @param[in]  eps       Value of the finite difference step.
 */
void finite_hessian(
    const Eigen::Ref<const Eigen::VectorXd>& x,
    const std::function<double(const Eigen::VectorXd&)>& f,
    Eigen::MatrixXd& hess,
    const AccuracyOrder accuracy = SECOND,
    const double eps = 1.0e-5);

/**
 * @brief Compare if two gradients are close enough.
 *
 * @param[in] x         The first gradient to compare.
 * @param[in] y         The second gradient to compare against.
 * @param[in] test_eps  Tolerance of equality.
 * @param[in] msg       Debug message header.
 *
 * @return A boolean for if x and y are close to the same value.
 */
bool compare_gradient(
    const Eigen::Ref<const Eigen::VectorXd>& x,
    const Eigen::Ref<const Eigen::VectorXd>& y,
    const double test_eps = 1e-4,
    const std::string& msg = "compare_gradient ");

/**
 * @brief Compare if two Jacobians are close enough.
 *
 * @param[in] x         The first Jacobian to compare.
 * @param[in] y         The second Jacobian to compare against.
 * @param[in] test_eps  Tolerance of equality.
 * @param[in] msg       Debug message header.
 *
 * @return A boolean for if x and y are close to the same value.
 */
bool compare_jacobian(
    const Eigen::Ref<const Eigen::MatrixXd>& x,
    const Eigen::Ref<const Eigen::MatrixXd>& y,
    const double test_eps = 1e-4,
    const std::string& msg = "compare_jacobian ");

/**
 * @brief Compare if two Hessians are close enough.
 *
 * @param[in] x         The first Hessian to compare.
 * @param[in] y         The second Hessian to compare against.
 * @param[in] test_eps  Tolerance of equality.
 * @param[in] msg       Debug message header.
 *
 * @return A boolean for if x and y are close to the same value.
 */
bool compare_hessian(
    const Eigen::Ref<const Eigen::MatrixXd>& x,
    const Eigen::Ref<const Eigen::MatrixXd>& y,
    const double test_eps = 1e-4,
    const std::string& msg = "compare_hessian ");

/// @brief Flatten the matrix rowwise
Eigen::VectorXd flatten(const Eigen::Ref<const Eigen::MatrixXd>& X);

/// @brief Unflatten rowwise
Eigen::MatrixXd unflatten(const Eigen::Ref<const Eigen::VectorXd>& x, int dim);

} // namespace fd
