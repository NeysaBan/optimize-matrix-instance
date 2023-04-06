#include <mmintrin.h>
#include <xmmintrin.h> // SSE
#include <pmmintrin.h> // SSE2
#include <emmintrin.h> // SSE3

void func(double *a, double *b, double *c, double *mid_res, double *res)
{
    int i, k, i_0;
    double Vx_0;
    for (i = 0; i < 60; i++)
    {
        float mid_res[60];
        float *mid_res_cur = mid_res;
        for (k = 0; k < 60; k++)
        {
            int mul_k = k * 60, mul_k1 = mul_k << 1;
            __m128d tmp_value;
            __m128d a_reg, b_reg;
            tmp_value = _mm_setzero_pd();
            for (i_0 = 0; i_0 < 120; i_0 += 2)
            {
                a_reg = _mm_set_pd(a[60 * i_0 + i], a[60 * (i_0 + 1) + i]);
                b_reg = _mm_set_pd(b[mul_k1 + i_0], b[mul_k1 + i_0 + 1]);
                tmp_value += a_reg * b_reg;
            }
            mid_res[i + mul_k] = tmp_value[0] + tmp_value[1];
            (*mid_res_cur++) = tmp_value[0] + tmp_value[1];
        }
        for (k = 0; k < 60; k++)
        {
            int mul_k = k * 60;
            // double tmp_value = 0.0;
            __m128d tmp_value;
            __m128d c_reg, mid_res_reg;
            mid_res_cur = mid_res;
            tmp_value = _mm_setzero_pd();
            for (i_0 = 0; i_0 < 60; i_0 += 2)
            {
                c_reg = _mm_set_pd(c[mul_k + i_0], c[mul_k + i_0 + 1]);
                mid_res_reg = _mm_set_pd(*mid_res_cur, *(mid_res_cur + 1));
                tmp_value += c_reg * mid_res_reg;
                mid_res_cur += 2;
            }
            res[i + mul_k] = tmp_value[0] + tmp_value[1];
        }
    }
}