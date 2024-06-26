#pragma once

#include "memory_funcs.h"


typedef struct {
    word val;
    adress adr;    
} Arg;

extern Arg ss, dd;
extern word r;
extern word nn, xx;

Arg get_mr(word w);
word get_nn(word w);
byte get_r(word w);
byte get_xx(word w);