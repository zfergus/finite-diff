#include <iostream>

#include <Eigen/Core>
#include <catch2/catch.hpp>

#include <finitediff.hpp>

using namespace fd;

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

    AccuracyOrder accuracy = GENERATE(SECOND, FOURTH, SIXTH, EIGHTH);

    Eigen::MatrixXd fjac;
    finite_jacobian(x, f, fjac, accuracy);

    CHECK(compare_jacobian(jac, fjac));
}

TEST_CASE("Test finite difference jacobian of trig", "[jacobian]")
{
    int n = GENERATE(1, 2, 4, 10, 100);

    const auto f = [&](const Eigen::VectorXd x) -> Eigen::VectorXd {
        return x.array().sin();
    };

    Eigen::VectorXd x = Eigen::VectorXd::Random(n);

    Eigen::MatrixXd jac = x.array().cos().matrix().asDiagonal();

    AccuracyOrder accuracy = GENERATE(SECOND, FOURTH, SIXTH, EIGHTH);

    Eigen::MatrixXd fjac;
    finite_jacobian(x, f, fjac, accuracy);

    CHECK(compare_jacobian(jac, fjac));
}
