#include <eigen3/Eigen/Dense>

void func(double *_a, double *b, double *c, double *mid_res, double *res)
{
    Eigen::MatrixXd Mat11(60, 120);
    Eigen::MatrixXd Mat12(120, 60);
    for (int m = 0; m < 60; m++)
    {
        for (int k = 0; k < 120; k++)
        {
            Mat11(m, k) = a[m + 60 * k];
            Mat12(k, m) = b[k + m * 120];
        }
    }

    Eigen::MatrixXd mid_res(60, 60);
    std::cout << "" << std::endl;
    start_t = std::chrono::high_resolution_clock::now();
    mid_res = Mat11 * Mat12; // 3.35ms
    end_t = std::chrono::high_resolution_clock::now();
    fp_ms = end_t - start_t;
    std::cout << "Mat11 * Mat12 : " << fp_ms.count() << " ms, " << std::endl;

    Eigen::MatrixXd Mat22(60, 60);
    for (int q = 0; q < 60; q++)
    {
        for (int n = 0; n < 60; n++)
        {
            Mat22(q, n) = c[q + n * 60];
        }
    }

    Eigen::MatrixXd eigen_res(60, 60);
    start_t = std::chrono::high_resolution_clock::now();
    eigen_res = mid_res * Mat22;
    std::cout << "Mat21 * Mat22 : " << fp_ms.count() << " ms, " << std::endl;

    for (int m = 0; m < 60; m++)
    {
        for (int n = 0; n < 60; n++)
        {
            res_write_back[m + n * 60] = eigen_res(m, n);
        }
    }
}