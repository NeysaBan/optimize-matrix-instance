#include <arm_neon.h>

void func(double *old_a, double *old_b, double *old_c, double *old_mid_res, double *res)
{
    int i, k, i_0;
    for (i = 0; i < 60; i++)
    {
        // NOTE 在这打包a
        float64_t a[60];
        for (int x = 0; x < 60; x++)
        {
            a[x] = *(old_a + 60 * x + i);
        }
        float64_t b[60];
        for (k = 0; k < 60; k++)
        {
            int mul_k = k * 60;
            for (int x = 0; x < 60; x++)
            {
                b[x] = *(old_b + mul_k + x);
            }

            float64_t tmp_value = {0};
            float64x2_t a_reg, b_reg;
            float64_t *b_cur = b, *a_cur = a;
            for (i_0 = 0; i_0 < 120; i_0 += 2, a_cur += 2, b_cur += 2)
            {
                a_reg = vld1q_f64(a_cur);
                b_reg = vld1q_f64(b_cur);
                vfmaq_n_f64(b_reg, a_reg, tmp_value);
            }
            // vst1_f64(old_mid_res + i + mul_k, tmp_value[0]);
            old_mid_res[i + mul_k] = tmp_value;
        }
        // NOTE 在这打包mid_res
        float64_t mid_res[60];
        for (int x = 0; x < 60; x++)
        {
            mid_res[x] = *(old_mid_res + 60 * x + i);
        }
        for (k = 0; k < 60; k++)
        {
            int mul_k = k * 60;
            float64_t c[60];
            for (int x = 0; x < 60; x++)
            {
                c[x] = *(old_c + mul_k + x);
            }
            float64_t tmp_value = {0};
            float64x2_t c_reg, mid_res_reg;
            float64_t *mid_res_cur = mid_res, *c_cur = c;
            for (i_0 = 0; i_0 < 60; i_0 += 2, c_cur += 2, mid_res_cur += 2)
            {
                c_reg = vld1q_f64(c_cur);
                mid_res_reg = vld1q_f64(mid_res_cur);
                vfmaq_n_f64(c_reg, mid_res_reg, tmp_value);
            }
            // vst1_f64(res + i + mul_k, tmp_value);
            res[i + mul_k] = tmp_value;
        }
    }
}