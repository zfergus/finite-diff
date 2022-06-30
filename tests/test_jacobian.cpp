#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

#include <Eigen/Core>

#include <finitediff.hpp>

using namespace fd;

TEST_CASE("Test finite difference jacobian of linear", "[jacobian]")
{
    int n = GENERATE(1, 2, 4, 10, 100);

    // f(x) = Ax
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(n, n);

    const auto f = [&](const Eigen::VectorXd& x) -> Eigen::VectorXd {
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

    const auto f = [&](const Eigen::VectorXd& x) -> Eigen::VectorXd {
        return x.array().sin();
    };

    Eigen::VectorXd x = Eigen::VectorXd::Random(n);

    Eigen::MatrixXd jac = x.array().cos().matrix().asDiagonal();

    AccuracyOrder accuracy = GENERATE(SECOND, FOURTH, SIXTH, EIGHTH);

    Eigen::MatrixXd fjac;
    finite_jacobian(x, f, fjac, accuracy);

    CHECK(compare_jacobian(jac, fjac));
}
