#include <iostream>

#include <Eigen/Core>
#include <catch2/catch.hpp>

#include <finitediff.hpp>

TEST_CASE("Test finite difference gradient of quadratic", "[gradient]")
{
    int n = GENERATE(1, 2, 4, 10, 100);

    // f(x) = xᵀAx + bᵀx
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(n, n);
    Eigen::VectorXd b = Eigen::VectorXd::Random(n);

    const auto f = [&](const Eigen::VectorXd x) -> double {
        return (x.transpose() * A * x + b.transpose() * x)(0);
    };

    Eigen::VectorXd x = Eigen::VectorXd::Random(n);

    Eigen::VectorXd grad = A * x + A.transpose() * x + b;

    fd::AccuracyOrder accuracy = fd::AccuracyOrder(GENERATE(range(0, 4)));

    Eigen::VectorXd fgrad;
    fd::finite_gradient(x, f, fgrad, accuracy);

    CHECK(fd::compare_gradient(grad, fgrad));
}

TEST_CASE("Test finite difference gradient of Rosenbrock", "[gradient]")
{
    const auto f = [](const Eigen::VectorXd x) {
        double t1 = 1 - x[0];
        double t2 = (x[1] - x[0] * x[0]);
        return t1 * t1 + 100 * t2 * t2;
    };

    const auto fdiff = [](const Eigen::VectorXd x) {
        return Eigen::Vector2d(
            -2 * (1 - x[0]) + 200 * (x[1] - x[0] * x[0]) * (-2 * x[0]),
            200 * (x[1] - x[0] * x[0]));
    };

    Eigen::VectorXd x = Eigen::Vector2d::Random();

    Eigen::VectorXd grad = fdiff(x);

    fd::AccuracyOrder accuracy = fd::AccuracyOrder(GENERATE(range(0, 4)));

    Eigen::VectorXd fgrad;
    fd::finite_gradient(x, f, fgrad, accuracy);

    CHECK(fd::compare_gradient(grad, fgrad));
}

TEST_CASE("Test finite difference gradient of trig", "[gradient]")
{
    int n = GENERATE(1, 2, 4, 10, 100);

    const auto f = [&](const Eigen::VectorXd x) -> double {
        return x.array().sin().matrix().squaredNorm();
    };

    Eigen::VectorXd x = Eigen::VectorXd::Random(n);

    Eigen::VectorXd grad = 2 * x.array().sin() * x.array().cos();

    fd::AccuracyOrder accuracy = fd::AccuracyOrder(GENERATE(range(0, 4)));

    Eigen::VectorXd fgrad;
    fd::finite_gradient(x, f, fgrad, accuracy);

    CHECK(fd::compare_gradient(grad, fgrad));
}
