#pragma once
#include <stdint.h>

#define IDT_ENTRIES 256

struct idt_entry_t {
    uint16_t offset_low;    // Lower 16 bits of handler function address
    uint16_t selector;      // Kernel segment selector
    uint8_t  ist;           // IST (Interrupt Stack Table), usually 0
    uint8_t  type_attr;     // Type and attributes
    uint16_t offset_mid;    // Middle bits of handler address
    uint32_t offset_high;   // High bits of handler address
    uint32_t zero;          // Reserved
} __attribute__((packed));

struct idt_ptr_t {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

void idt_init(void);
