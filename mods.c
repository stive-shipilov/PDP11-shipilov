#include <stdio.h>
#include <stdlib.h>

#include "memory_funcs.h"
#include "mods.h"

Arg ss, dd;
word r;
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

            if(byte_flag == BYTE && r != 6 && r != 7)
                reg[r] += 1;
            else
                reg[r] += 2;          
            
            if (r == 7)
                printf("#%06o ", res.val);
            else
                printf("(R%d)+ ", r);
            break;
        case 3:
            res.adr = reg[r];
            res.adr = w_read(res.adr);

            if(r == 7)
                printf("@#%06o ", res.adr);
            else
                printf("@(R%d)+ ", r);

            res.val = w_read(res.adr);
            reg[r] += 2;
            break;
        case 6:
            word x = 0x0000;
            x = w_read(pc);             
            pc += 2;
            res.adr = (reg[r] + x) & 0xFFFF;   
            res.val = w_read(res.adr);

            if (r == 7)
                printf("%06o ", res.adr);
            else
                printf("%06o(R%d) ", x, r);
            break;

        default:
            printf("Mode %d not implemented yet!\n", m);
            exit(1);
    }

    return res;
}

byte get_r(word w)
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



