#include <stdio.h>
#include <stdlib.h>

#include "memory_funcs.h"
#include "mods.h"

Arg ss, dd;
byte rl;
word nn, xx;


Arg get_mr(word w)
{
    Arg res;    

    int r = w & 7;
    int m = (w >> 3) & 7; 

    switch (m) {
        case 0:
            res.adr = r;
            res.val = reg[r];
            printf("R%d ", r);
            break;

        case 1:
            res.adr = reg[r];
            res.val = w_read(res.adr);  
            printf("(R%d) ", r);
            break;

        case 2:
            res.adr = reg[r];          
            res.val = w_read(res.adr);  
            reg[r] += 2;
            
            if (r == 7)
                printf("#%o ", res.val);
            else
                printf("(R%d)+ ", r);
            break;

        default:
            printf("Mode %d not implemented yet!\n", m);
            exit(1);
    }

    return res;
}

byte get_rl(word w)
{
    byte res; 

    res = w & 7;
    printf("R%d ", res);
    return res;
}

word get_nn(word w)
{
    word res; 

    res = w & 077;

    printf("%06o ", pc - 2*res);
    return res;

}

byte get_xx(word w)
{
    byte res; 

    res = w & 0377;
    printf("%06o ", pc + 2*res);
    return res;

}

