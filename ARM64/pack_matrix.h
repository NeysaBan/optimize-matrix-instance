
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

void func(double *old_a, double *b, double *c, double *mid_res, double *res)
{
    int m, q, n, k;
    double a[7200];
    PackMatrix(a, old_a, 60, 120, 60);
    double *a_cur = a;
    for (m = 0; m < 60; m++)
    {
        /* ---------------计算前两个矩阵相乘----------------*/
        double mid_res[60];
        double *mid_res_cur = mid_res;
        for (q = 0; q < 60; q++, mid_res_cur++)
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