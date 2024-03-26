#pragma once

#include "memory_funcs.h"

typedef struct {
    word val;
    adress adr;    
} Arg;

extern Arg ss, dd;

Arg get_mr(word w);
