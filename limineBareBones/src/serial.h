
#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

void serial_write(const char* s); 

void serial_write_hex64(uint64_t val);
#endif

