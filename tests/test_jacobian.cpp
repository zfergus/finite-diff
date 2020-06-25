#include <iostream>

#include <Eigen/Core>
#include <catch2/catch.hpp>

#include <finitediff.hpp>

TEST_CASE("Test finite difference jacobian of linear", "[jacobian]")
{
    int n = GENERATE(1, 2, 4, 10, 100);

    // f(x) = Ax
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(n, n);

    const auto f = [&](const Eigen::VectorXd x) -> Eigen::VectorXd {
        return A * x;
    };

    Eigen::VectorXd x = Eigen::VectorXd::Random(n);

    Eigen::MatrixXd jac = A;

    fd::AccuracyOrder accuracy = fd::AccuracyOrder(GENERATE(range(0, 4)));

    Eigen::MatrixXd fjac;
    fd::finite_jacobian(x, f, fjac, accuracy);

    CHECK(fd::compare_jacobian(jac, fjac));
}

TEST_CASE("Test finite difference jacobian of trig", "[jacobian]")
{
    int n = GENERATE(1, 2, 4, 10, 100);

    const auto f = [&](const Eigen::VectorXd x) -> Eigen::VectorXd {
        return x.array().sin();
    };

    Eigen::VectorXd x = Eigen::VectorXd::Random(n);

    Eigen::MatrixXd jac = x.array().cos().matrix().asDiagonal();

    fd::AccuracyOrder accuracy = fd::AccuracyOrder(GENERATE(range(0, 4)));

    Eigen::MatrixXd fjac;
    fd::finite_jacobian(x, f, fjac, accuracy);

    CHECK(fd::compare_jacobian(jac, fjac));
}
