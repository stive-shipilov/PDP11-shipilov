#pragma once

#include "common.h"

byte b_read(adress adr);
void b_write(adress adr, byte val);
word w_read(adress adr);
void w_write(adress adr, word val);
void reg_dump();