#include "gdt.h"
#include <stdint.h>
//TODO: through idt and gdt use of xdt_ptr and xdtr is inconsistent
struct gdt_seg gdt[GDT_ENTRIES];
struct gdt_ptr gdtr;

//these shits not consistently used
enum { GDT_NULL=0, GDT_KCODE=1, GDT_KDATA=2 };
#define KERNEL_CS ((GDT_KCODE<<3)|0)
#define KERNEL_DS ((GDT_KDATA<<3)|0)
void gdt_init(){
  gdtr.limit = sizeof(gdt) - 1;
  gdtr.base = (uint64_t)&gdt;
  //null descriptor
  gdt[0] = (struct gdt_seg){
    .limit_lo = (uint16_t)0x0,
    .base_lo = (uint16_t)0x0,
    .base_mid = (uint8_t)0x0,
    .access = (uint8_t)0x0,
    .limit_hi_flags = (uint8_t)0x0,
    .base_hi = (uint8_t)0x0
  }; 
//kernel code descriptor
  gdt[1] = (struct gdt_seg){
    .limit_lo = (uint16_t)0x0,
    .base_lo = (uint16_t)0x0,
    .base_mid = (uint8_t)0x0,
    .access = (uint8_t)0x9A,
    .limit_hi_flags = (uint8_t)0xAF,
    .base_hi = (uint8_t)0x0
  };
//kernel data descriptor
   gdt[2] = (struct gdt_seg){
    .limit_lo = (uint16_t)0x0,
    .base_lo = (uint16_t)0x0,
    .base_mid = (uint8_t)0x0,
    .access = (uint8_t)0x92,
    .limit_hi_flags = (uint8_t)0xCF,
    .base_hi = (uint8_t)0x0
  }; 
   
    
    asm volatile("lgdt %0" : : "m"(gdtr));
  //idk what this next asm is
    // Reload CS via far return, then load data segs.
    __asm__ volatile (
        "pushq %[cs];"
        "lea  1f(%%rip), %%rax;"
        "pushq %%rax;"
        "lretq;"
        "1: mov %[ds], %%ax;"
        "mov %%ax, %%ds; mov %%ax, %%es; mov %%ax, %%ss; mov %%ax, %%fs; mov %%ax, %%gs;"
        : : [cs]"i"(KERNEL_CS), [ds]"i"(KERNEL_DS) : "rax", "memory"
    );
}

