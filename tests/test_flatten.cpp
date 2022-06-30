#include <catch2/catch_test_macros.hpp>

#include <finitediff.hpp>

using namespace fd;

TEST_CASE("Flatten and unflatten", "[utils]")
{
    Eigen::MatrixXd X = Eigen::MatrixXd::Random(1000, 3);
    Eigen::MatrixXd R = unflatten(flatten(X), X.cols());
    CHECK(X == R);
}
