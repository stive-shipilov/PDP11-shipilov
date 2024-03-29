#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "memory_funcs.h"


void test_mem()
{
    adress a;
    byte b0, b1, bres;
    word w, wres;
    // пишем байт, читаем байт по четному адресу
    fprintf(stderr, "Пишем и читаем байт по четному адресу\n");
    a = 0;
    b0 = 0x77;
    b_write(a, b0);
    bres = b_read(a);
    fprintf(stderr, "a=%06o b0=%x bres=%x\n", a, b0, bres);
    assert(b0 == bres);

    // пишем байт, читаем байт по НЕчетному адресу
    fprintf(stderr, "Пишем и читаем байт по НЕчетному адресу\n");
    a = 1;
    b0 = 0xdf;
    b_write(a, b0);
    bres = b_read(a);
    fprintf(stderr, "a=%06o b0=%x bres=%x\n", a, b0, bres);
    assert(b0 == bres);

    // пишем слово, читаем слово
    fprintf(stderr, "Пишем и читаем слово\n");
    a = 2;        // другой адрес
    w = 0xabcd;
    w_write(a, w);
    wres = w_read(a);
    fprintf(stderr, "a=%06o w=%04x wres=%04x\n", a, w, wres);
    assert(w == wres);

    // Прочитаем записанное слово по байту
    fprintf(stderr, "Прочитаем записанное слово по байту\n");
    byte b1res, b2res;
    a = 4;
    w = 0x7891;
    b1res = 0x91;
    b2res = 0x78;
    w_write(a, w);
    fprintf(stderr, "a=%06o w1=%02x wres1=%02x\n", a, b1res, b_read(a));
    fprintf(stderr, "a=%06o w2=%02x wres2=%02x\n", a+1, b2res, b_read(a+1));
    assert(b1res == b_read(a));
    assert(b2res == b_read(a+1));

    // пишем 2 байта, читаем 1 слово
    fprintf(stderr, "Пишем 2 байта, читаем слово\n");
    a = 4;      
    w = 0xdcba;
    b0 = 0xba;
    b1 = 0xdc;
    b_write(a, b0);
    b_write(a+1, b1);
    wres = w_read(a);
    fprintf(stderr, "a=%06o b1=%02x b0=%02x wres=%x\n", a, b1, b0, wres);
    assert(w == wres);
}