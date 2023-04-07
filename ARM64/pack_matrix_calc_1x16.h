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

void Matrix1x16(int k, double *a, const double *b, double *c)
{
    // 所以应该是a的一行 x b的八列
    float64_t resi0 = {0}; // (row, 0)
    float64_t resi1 = {0}; // (row, 1)
    float64_t resi2 = {0}; // (row, 2)
    float64_t resi3 = {0}; // (row, 3)
    float64_t resi4 = {0};
    float64_t resi5 = {0};
    float64_t resi6 = {0};
    float64_t resi7 = {0};
    float64_t resi8 = {0};
    float64_t resi9 = {0};
    float64_t resi10 = {0};
    float64_t resi11 = {0};
    float64_t resi12 = {0};
    float64_t resi13 = {0};
    float64_t resi14 = {0};
    float64_t resi15 = {0};

    double *a_cur = a;
    const double *b_i0_cur = b, *b_i1_cur = b + 1 * k, *b_i2_cur = b + 2 * k, *b_i3_cur = b + 3 * k,
                 *b_i4_cur = b + 4 * k, *b_i5_cur = b + 5 * k, *b_i6_cur = b + 6 * k, *b_i7_cur = b + 7 * k,
                 *b_i8_cur = b + 8 * k, *b_i9_cur = b + 9 * k, *b_i10_cur = b + 10 * k, *b_i11_cur = b + 11 * k,
                 *b_i12_cur = b + 12 * k, *b_i13_cur = b + 13 * k, *b_i14_cur = b + 14 * k, *b_i15_cur = b + 15 * k;

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
                    b_i7_reg = vld1q_f64(b_i7_cur),
                    b_i8_reg = vld1q_f64(b_i8_cur),
                    b_i9_reg = vld1q_f64(b_i9_cur),
                    b_i10_reg = vld1q_f64(b_i10_cur),
                    b_i11_reg = vld1q_f64(b_i11_cur),
                    b_i12_reg = vld1q_f64(b_i12_cur),
                    b_i13_reg = vld1q_f64(b_i13_cur),
                    b_i14_reg = vld1q_f64(b_i14_cur),
                    b_i15_reg = vld1q_f64(b_i15_cur);

        resi0 += (a_reg[0] * b_i0_reg[0] + a_reg[1] * b_i0_reg[1]);
        resi1 += (a_reg[0] * b_i1_reg[0] + a_reg[1] * b_i1_reg[1]);
        resi2 += (a_reg[0] * b_i2_reg[0] + a_reg[1] * b_i2_reg[1]);
        resi3 += (a_reg[0] * b_i3_reg[0] + a_reg[1] * b_i3_reg[1]);
        resi4 += (a_reg[0] * b_i4_reg[0] + a_reg[1] * b_i4_reg[1]);
        resi5 += (a_reg[0] * b_i5_reg[0] + a_reg[1] * b_i5_reg[1]);
        resi6 += (a_reg[0] * b_i6_reg[0] + a_reg[1] * b_i6_reg[1]);
        resi7 += (a_reg[0] * b_i7_reg[0] + a_reg[1] * b_i7_reg[1]);
        resi8 += (a_reg[0] * b_i8_reg[0] + a_reg[1] * b_i8_reg[1]);
        resi9 += (a_reg[0] * b_i9_reg[0] + a_reg[1] * b_i9_reg[1]);
        resi10 += (a_reg[0] * b_i10_reg[0] + a_reg[1] * b_i10_reg[1]);
        resi11 += (a_reg[0] * b_i11_reg[0] + a_reg[1] * b_i11_reg[1]);
        resi12 += (a_reg[0] * b_i12_reg[0] + a_reg[1] * b_i12_reg[1]);
        resi13 += (a_reg[0] * b_i13_reg[0] + a_reg[1] * b_i13_reg[1]);
        resi14 += (a_reg[0] * b_i14_reg[0] + a_reg[1] * b_i14_reg[1]);
        resi15 += (a_reg[0] * b_i15_reg[0] + a_reg[1] * b_i15_reg[1]);

        a_cur += 2;
        b_i0_cur += 2;
        b_i1_cur += 2;
        b_i2_cur += 2;
        b_i3_cur += 2;
        b_i4_cur += 2;
        b_i5_cur += 2;
        b_i6_cur += 2;
        b_i7_cur += 2;
        b_i8_cur += 2;
        b_i9_cur += 2;
        b_i10_cur += 2;
        b_i11_cur += 2;
        b_i12_cur += 2;
        b_i13_cur += 2;
        b_i14_cur += 2;
        b_i15_cur += 2;
    }

    *(c) = resi0;
    *(c + 1) = resi1;
    *(c + 2) = resi2;
    *(c + 3) = resi3;
    *(c + 4) = resi4;
    *(c + 5) = resi5;
    *(c + 6) = resi6;
    *(c + 7) = resi7;
    *(c + 8) = resi8;
    *(c + 9) = resi9;
    *(c + 10) = resi10;
    *(c + 11) = resi11;
    *(c + 12) = resi12;
    *(c + 13) = resi13;
    *(c + 14) = resi14;
    *(c + 15) = resi15;
}

void Matrix1x8(int k, double *a, const double *b, double *c)
{
    // 所以应该是a的一行 x b的八列
    float64_t resi0 = {0}; // (row, 0)
    float64_t resi1 = {0}; // (row, 1)
    float64_t resi2 = {0}; // (row, 2)
    float64_t resi3 = {0}; // (row, 3)
    float64_t resi4 = {0};
    float64_t resi5 = {0};
    float64_t resi6 = {0};
    float64_t resi7 = {0};

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

        resi0 += (a_reg[0] * b_i0_reg[0] + a_reg[1] * b_i0_reg[1]);
        resi1 += (a_reg[0] * b_i1_reg[0] + a_reg[1] * b_i1_reg[1]);
        resi2 += (a_reg[0] * b_i2_reg[0] + a_reg[1] * b_i2_reg[1]);
        resi3 += (a_reg[0] * b_i3_reg[0] + a_reg[1] * b_i3_reg[1]);
        resi4 += (a_reg[0] * b_i4_reg[0] + a_reg[1] * b_i4_reg[1]);
        resi5 += (a_reg[0] * b_i5_reg[0] + a_reg[1] * b_i5_reg[1]);
        resi6 += (a_reg[0] * b_i6_reg[0] + a_reg[1] * b_i6_reg[1]);
        resi7 += (a_reg[0] * b_i7_reg[0] + a_reg[1] * b_i7_reg[1]);

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

    *(c) = resi0;
    *(c + 1) = resi1;
    *(c + 2) = resi2;
    *(c + 3) = resi3;
    *(c + 4) = resi4;
    *(c + 5) = resi5;
    *(c + 6) = resi6;
    *(c + 7) = resi7;
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
        for (q = 0; q + 16 < 60; q += 16, mid_res_cur += 16)
        {
            Matrix1x16(120, a_cur, b + 120 * q, mid_res_cur);
        }
        for (; q + 8 < 60; q += 8, mid_res_cur += 8)
        {
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
