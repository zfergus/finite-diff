#include <iostream>

#include <Eigen/Core>
#include <catch2/catch.hpp>

#include <finitediff.hpp>
#include <spdlog/spdlog.h>

using namespace fd;

TEST_CASE("Test finite difference hessian of quadratic", "[hessian]")
{
    AccuracyOrder accuracy = GENERATE(SECOND, FOURTH, SIXTH, EIGHTH);

    int n = GENERATE(1, 2, 4, 10, 25);

    // f(x) = xᵀAx + bᵀx
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(n, n);
    Eigen::VectorXd b = Eigen::VectorXd::Random(n);

    const auto f = [&](const Eigen::VectorXd x) -> double {
        return (x.transpose() * A * x + b.transpose() * x)(0);
    };

    Eigen::VectorXd x = Eigen::VectorXd::Random(n);

    Eigen::MatrixXd hess = A + A.transpose();

    Eigen::MatrixXd fhess;
    finite_hessian(x, f, fhess, accuracy);

    CAPTURE(n);
    CHECK(compare_hessian(hess, fhess));
}

TEST_CASE("Test finite difference hessian of Rosenbrock", "[hessian]")
{
    AccuracyOrder accuracy = GENERATE(SECOND, FOURTH, SIXTH, EIGHTH);
    const auto f = [](const Eigen::VectorXd x) {
        double t1 = 1 - x[0];
        double t2 = (x[1] - x[0] * x[0]);
        return t1 * t1 + 100 * t2 * t2;
    };

    Eigen::VectorXd x = Eigen::Vector2d::Random();

    Eigen::MatrixXd hess(2, 2);
    hess(0, 0) = 1200 * x[0] * x[0] - 400 * x[1] + 2;
    hess(0, 1) = -400 * x[0];
    hess(1, 0) = -400 * x[0];
    hess(1, 1) = 200;

    Eigen::MatrixXd fhess;
    finite_hessian(x, f, fhess, accuracy);

    CHECK(compare_hessian(hess, fhess));
}

TEST_CASE("Test finite difference hessian of trig", "[hessian]")
{
    AccuracyOrder accuracy = GENERATE(SECOND, FOURTH, SIXTH, EIGHTH);
    int n = GENERATE(1, 2, 4, 10, 25);

    const auto f = [&](const Eigen::VectorXd x) -> double {
        return x.array().sin().matrix().squaredNorm();
    };

    Eigen::VectorXd x = Eigen::VectorXd::Random(n);

    Eigen::ArrayXd sin_x = x.array().sin(), cos_x = x.array().cos();
    Eigen::MatrixXd hess = Eigen::MatrixXd::Zero(n, n);
    hess.diagonal() = 2 * (cos_x * cos_x) - 2 * (sin_x * sin_x);

    Eigen::MatrixXd fhess;
    finite_hessian(x, f, fhess, accuracy);

    CHECK(compare_hessian(hess, fhess));
}
