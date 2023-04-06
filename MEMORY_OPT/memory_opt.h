void func(double *a, double *b, double *c, double *mid_res, double *res)
{
    int m, q, n, k;
    for (m = 0; m < 60; m++)
    {
        for (q = 0; q < 60; q++)
        {
            double tmp_value = 0.0;
            for (k = 0; k < 120; k++)
            { // 中间数
                tmp_value += a[m + 60 * k] * b[k + q * 120];
            }
            mid_res[m + 60 * q] = tmp_value;
        }
        for (n = 0; n < 60; n++)
        {
            double tmp_value = 0.0;
            for (q = 0; q < 60; q++)
            { // 中间数
                tmp_value += mid_res[m + 60 * q] * c[q + n * 60];
            }
            res[m + n * 60] = tmp_value;
        }
    }
}