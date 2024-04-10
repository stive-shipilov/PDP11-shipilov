#include "common.h"

byte N, Z, C;

void set_N(word n_val)
{
    N = 0;
    if(n_val < 0)
        N = 1;
}

void set_Z(word z_val)
{
    Z = 0;
    if(z_val == 0)
        Z = 1;
}

void set_C(word c_val)
{
    C = 0x0001 & (c_val >> 16);
}