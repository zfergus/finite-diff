#include <catch2/catch_test_macros.hpp>

#include <Eigen/Core>

#include <finitediff.hpp>

using namespace fd;

TEST_CASE("compare_jacobian returns false for different sizes", "[compare]")
{
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(2, 3);
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(3, 2);

    CHECK_FALSE(compare_jacobian(A, B));
}
