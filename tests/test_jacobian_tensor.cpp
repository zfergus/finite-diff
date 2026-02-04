#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

#include <Eigen/Core>

#include <finitediff.hpp>

using namespace fd;

TEST_CASE("finite_jacobian_tensor layouts", "[jacobian_tensor]")
{
    int n = GENERATE(1, 2, 4, 10);

    const int p = 2;
    const int q = 3;

    // Construct a tensor T_k (p x q) for each input component k such that
    // f(x) = sum_k x_k * T_k. The analytic derivative w.r.t x_k is T_k.
    std::vector<Eigen::MatrixXd> T;
    T.reserve(n);
    for (int k = 0; k < n; ++k) {
        T.emplace_back(Eigen::MatrixXd::Random(p, q));
    }

    const auto f = [&](const Eigen::VectorXd& x) -> Eigen::MatrixXd {
        Eigen::MatrixXd R = Eigen::MatrixXd::Zero(p, q);
        for (int k = 0; k < n; ++k) {
            R += x[k] * T[k];
        }
        return R;
    };

    Eigen::VectorXd x = Eigen::VectorXd::Random(n);

    // Analytic Jacobians for the two storage conventions
    Eigen::MatrixXd jac_odd = Eigen::MatrixXd::Zero(p * q, n);
    Eigen::MatrixXd jac_even = Eigen::MatrixXd::Zero(p, q * n);
    for (int k = 0; k < n; ++k) {
        jac_odd.col(k) = T[k].reshaped();
        jac_even.middleCols(q * k, q) = T[k];
    }

    AccuracyOrder accuracy = GENERATE(SECOND, FOURTH, SIXTH, EIGHTH);

    Eigen::MatrixXd fjac_odd;
    finite_jacobian_tensor<3>(x, f, fjac_odd, accuracy);
    CHECK(compare_jacobian(jac_odd, fjac_odd));

    Eigen::MatrixXd fjac_even;
    finite_jacobian_tensor<4>(x, f, fjac_even, accuracy);
    CHECK(compare_jacobian(jac_even, fjac_even));
}
