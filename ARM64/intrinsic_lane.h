#include <arm_neon.h>

void func(double *a, double *b, double *c, double *mid_res, double *res)
{
    int i, k, i_0;
    for (i = 0; i < 60; i++)
    {
        // NOTE 在这打包a
        for (k = 0; k < 60; k++)
        {
            int mul_k = k * 60, mul_k1 = mul_k << 1;
            float64x1_t tmp_value = {0};
            float64x2_t a_reg, b_reg;
            for (i_0 = 0; i_0 < 120; i_0 += 2)
            {
                vld1q_lane_f64(a + 60 * i_0 + i, a_reg, 0);
                vld1q_lane_f64(a + 60 * (i_0 + 1) + i, a_reg, 1);
                vld1q_lane_f64(b + mul_k1 + i_0, b_reg, 0);
                vld1q_lane_f64(b + mul_k1 + i_0 + 1, b_reg, 1);
                vfmaq_lane_f64(b_reg, a_reg, tmp_value, 0); // 乘加
            }
            vst1_f64(mid_res + i + mul_k, tmp_value);
        }
        // NOTE 在这打包mid_res
        for (k = 0; k < 60; k++)
        {
            int mul_k = k * 60;
            float64x1_t tmp_value = {0};
            float64x2_t c_reg, mid_res_reg;
            for (i_0 = 0; i_0 < 60; i_0 += 2)
            {
                vld1q_lane_f64(c + mul_k + i_0, c_reg, 0);
                vld1q_lane_f64(c + mul_k + i_0 + 1, c_reg, 1);
                vld1q_lane_f64(mid_res + 60 * i_0 + i, mid_res_reg, 0);
                vld1q_lane_f64(mid_res + 60 * (i_0 + 1) + i, mid_res_reg, 1);
                vfmaq_lane_f64(c_reg, mid_res_reg, tmp_value, 0); // 乘加
            }
            vst1_f64(res + i + mul_k, tmp_value);
        }
    }
}