#pragma once
#include <stdint.h>
//all of these are for 64bit
#define GDT_ENTRIES 3
struct __attribute__((packed)) gdt_seg {
    uint16_t limit_lo;      // bytes 0..1: limit[0..15]
    uint16_t base_lo;       // bytes 2..3: base[0..15]
    uint8_t  base_mid;      // byte  4   : base[16..23]
    uint8_t  access;        // byte  5   : type | S | DPL | P
    uint8_t  limit_hi_flags;// byte  6   : [G D/B L AVL]<<4 | limit[16..19]
    uint8_t  base_hi;       // byte  7   : base[24..31]
};
//for the gdtr
struct __attribute__((packed)) gdt_ptr{
  uint16_t limit;
  uint64_t base;
};

void gdt_init(void);
