
void func(double *a, double *b, double *c, double *mid_res, double *res)
{
    int i, k, i_0;
    double Vx_0;
    for (i = 0; i < 60; i++)
    {
        for (k = 0; k < 60; k++)
        {
            mid_res[i + 60 * k] = 0.0;
            for (i_0 = 0; i_0 < 120; i_0++)
            {
                Vx_0 = mid_res[60 * k + i];
                Vx_0 +=
                    a[60 * i_0 + i] * b[120 * k + i_0];
                mid_res[i + 60 * k] = Vx_0;
            }
        }
        for (k = 0; k < 60; k++)
        {
            res[i + 60 * k] = 0.0;
            for (i_0 = 0; i_0 < 60; i_0++)
            {
                Vx_0 = res[60 * k + i];
                Vx_0 +=
                    mid_res[60 * i_0 + i] * c[60 * k + i_0];
                res[i + 60 * k] = Vx_0;
            }
        }
    }
}