#include <arm_neon.h>

void PackMatrix(double *des, double *src, int m, int n, int alpha)
{
    double *des_cur = des, *src_cur = src;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            *(des_cur + j) = *(src_cur + i + alpha * j);
        }
        des_cur += n;
    }
}

void Matrix1x8(int k, double *a, const double *b, double *c)
{
    // 所以应该是a的一行 x b的八列

    float64x2_t resi0 = {0}; // (row, 0)
    float64x2_t resi1 = {0}; // (row, 1)
    float64x2_t resi2 = {0}; // (row, 2)
    float64x2_t resi3 = {0}; // (row, 3)
    float64x2_t resi4 = {0};
    float64x2_t resi5 = {0};
    float64x2_t resi6 = {0};
    float64x2_t resi7 = {0};

    double *a_cur = a;
    const double *b_i0_cur = b, *b_i1_cur = b + 1 * k, *b_i2_cur = b + 2 * k, *b_i3_cur = b + 3 * k,
                 *b_i4_cur = b + 4 * k, *b_i5_cur = b + 5 * k, *b_i6_cur = b + 6 * k, *b_i7_cur = b + 7 * k;

    for (int i = 0; i < k; i += 2)
    {
        float64x2_t a_reg = vld1q_f64(a_cur);       // 一次横着加载两个数
        float64x2_t b_i0_reg = vld1q_f64(b_i0_cur), // 一次竖着加载两个数
            b_i1_reg = vld1q_f64(b_i1_cur),
                    b_i2_reg = vld1q_f64(b_i2_cur),
                    b_i3_reg = vld1q_f64(b_i3_cur),
                    b_i4_reg = vld1q_f64(b_i4_cur),
                    b_i5_reg = vld1q_f64(b_i5_cur),
                    b_i6_reg = vld1q_f64(b_i6_cur),
                    b_i7_reg = vld1q_f64(b_i7_cur);

        resi0 = vmlaq_f64(resi0, a_reg, b_i0_reg);
        resi1 = vmlaq_f64(resi1, a_reg, b_i1_reg);
        resi2 = vmlaq_f64(resi2, a_reg, b_i2_reg);
        resi3 = vmlaq_f64(resi3, a_reg, b_i3_reg);
        resi4 = vmlaq_f64(resi4, a_reg, b_i4_reg);
        resi5 = vmlaq_f64(resi5, a_reg, b_i5_reg);
        resi6 = vmlaq_f64(resi6, a_reg, b_i6_reg);
        resi7 = vmlaq_f64(resi7, a_reg, b_i7_reg);

        a_cur += 2;
        b_i0_cur += 2;
        b_i1_cur += 2;
        b_i2_cur += 2;
        b_i3_cur += 2;
        b_i4_cur += 2;
        b_i5_cur += 2;
        b_i6_cur += 2;
        b_i7_cur += 2;
    }

    *(c) = resi0[0] + resi0[1];
    *(c + 1) = resi1[0] + resi1[1];
    *(c + 2) = resi2[0] + resi2[1];
    *(c + 3) = resi3[0] + resi3[1];
    *(c + 4) = resi4[0] + resi4[1];
    *(c + 5) = resi5[0] + resi5[1];
    *(c + 6) = resi6[0] + resi6[1];
    *(c + 7) = resi7[0] + resi7[1];
}

void func(double *old_a, double *b, double *c, double *mid_res, double *res)
{
    int m, q, n, k;
    double a[7200];
    PackMatrix(a, old_a, 60, 120, 60);
    double *a_cur = a;
    // double mid_res[3600];

    for (m = 0; m < 60; m++)
    {
        /* ---------------计算前两个矩阵相乘----------------*/
        double mid_res[60];
        double *mid_res_cur = mid_res;
        for (q = 0; q + 8 < 60; q += 8, mid_res_cur += 8)
        {
            double tmp_value = 0.0;
            // 一次计算出8个数字即m*8个
            // ------- 这里由于要写回结果，所以最后一个位置得是原始的指针而非地址加和的结果
            Matrix1x8(120, a_cur, b + 120 * q, mid_res_cur);
        }
        for (; q < 60; q++, mid_res_cur++)
        {
            double tmp_value = 0.0;
            // 一个一个算
            for (k = 0; k < 120; k++)
            { // 中间数
                tmp_value += *(a_cur + k) * *(b + k + q * 120);
            }
            *(mid_res_cur) = tmp_value;
        }
        /* ---------------计算后两个矩阵相乘----------------*/
        mid_res_cur = mid_res;
        for (n = 0; n < 60; n++)
        {
            double tmp_value = 0.0;
            for (q = 0; q < 60; q++)
            { // 中间数
                tmp_value += *(mid_res_cur + q) * c[q + n * 60];
            }
            res[m + n * 60] = tmp_value;
        }
        a_cur += 120;
    }
}
