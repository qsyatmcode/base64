﻿#ifndef BASE64_ALPHABET_H
#define BASE64_ALPHABET_H

enum characters {
    ALBT_A,
    ALBT_B,
    ALBT_C,
    ALBT_D,
    ALBT_E,
    ALBT_F,
    ALBT_G,
    ALBT_H,
    ALBT_I,
    ALBT_J,
    ALBT_K,
    ALBT_L,
    ALBT_M,
    ALBT_N,
    ALBT_O,
    ALBT_P,
    ALBT_Q,
    ALBT_R,
    ALBT_S,
    ALBT_T,
    ALBT_U,
    ALBT_V,
    ALBT_W,
    ALBT_X,
    ALBT_Y,
    ALBT_Z,
    ALBT_a,
    ALBT_b,
    ALBT_c,
    ALBT_d,
    ALBT_e,
    ALBT_f,
    ALBT_g,
    ALBT_h,
    ALBT_i,
    ALBT_j,
    ALBT_k,
    ALBT_l,
    ALBT_m,
    ALBT_n,
    ALBT_o,
    ALBT_p,
    ALBT_q,
    ALBT_r,
    ALBT_s,
    ALBT_t,
    ALBT_u,
    ALBT_v,
    ALBT_w,
    ALBT_x,
    ALBT_y,
    ALBT_z,
    ALBT_0,
    ALBT_1,
    ALBT_2,
    ALBT_3,
    ALBT_4,
    ALBT_5,
    ALBT_6,
    ALBT_7,
    ALBT_8,
    ALBT_9,
    ALBT_PLUS,
    ALBT_SLASH,
    ALBT_PADDING,
};

extern const char alphabet_encode[65];
extern const char alphabet_decode[128];

#endif //BASE64_ALPHABET_H
