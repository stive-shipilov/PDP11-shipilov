#pragma once
#include "common.h"

void do_halt();
void do_add();
void do_move();
void do_movb();
void do_unknown();
void do_sob();
void do_clr();
void do_br();
void do_beq();
void do_tst();
void do_tstb();
void do_bpl();
void do_jsr();
void do_rts();

void set_N(byte N_val);
void set_Z(byte Z_val);
void set_C(byte C_val);