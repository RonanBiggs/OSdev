#include "serial.h"
#include "idt.h"
//TODO: macros for kernel code (0x08) and kernel data segments
extern void isr_stub_table(); // Provided by your assembly

struct idt_entry_t idt[IDT_ENTRIES];
struct idt_ptr_t idt_ptr;

extern void isr0(); // Declare stubs you'll define in assembly
extern void isr1(); // ...
extern void isr2(); // ...
//extern void isr3(); // ...
//extern void isr4(); // ...
//extern void isr5(); // ...
//extern void isr6(); // ...
//extern void isr7(); // ...
//extern void isr8(); // ...
//extern void isr9(); // ...
//extern void isr10(); // ...
//extern void isr11(); // ...
//extern void isr12(); // ...
//extern void isr13(); // ...
//extern void isr14(); // ...
//extern void isr15(); // ...
//extern void isr16(); // ...
//extern void isr17(); // ...
//extern void isr18(); // ...
//extern void isr19(); // ...
//extern void isr20(); // ...
//extern void isr21(); // ...
//extern void isr22(); // ...
//extern void isr23(); // ...
//extern void isr24(); // ...
//extern void isr25(); // ...
//extern void isr26(); // ...
//extern void isr27(); // ...
//extern void isr28(); // ...
//extern void isr29(); // ...
//extern void isr30(); // ...
//extern void isr31(); // ...

static void set_idt_gate(int n, uint64_t handler) {
    idt[n].offset_low  = handler & 0xFFFF;
    idt[n].selector    = 0x08; // Kernel code segment
    idt[n].ist         = 0;
    idt[n].type_attr   = 0x8E; // Interrupt gate maybe should be 0xE but idk
    idt[n].offset_mid  = (handler >> 16) & 0xFFFF;
    idt[n].offset_high = (handler >> 32) & 0xFFFFFFFF;
    idt[n].zero        = 0;
}

void idt_init(void) {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint64_t)&idt;
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt[i].offset_low  = 0;
        idt[i].selector    = 0x08;//TODO why is it default to kernel code segment
        idt[i].ist         = 0;
        idt[i].type_attr   = 0;
        idt[i].offset_mid  = 0;
        idt[i].offset_high = 0;
        idt[i].zero        = 0;
    }
    //set_idt_gate(0, (uint64_t)isr0);
    uint64_t handler = (uint64_t)isr0;
    idt[0] = (struct idt_entry_t){
        .offset_low  = (uint16_t)(handler        & 0xFFFF),
        .selector    = 0x08,                 // kernel CS, default for limine is 0x28
        .ist         = 0 & 0x7,              // IST index (0 if unused)
        .type_attr   = 0x8E,                 // P=1, DPL=0, type=interrupt
        .offset_mid  = (uint16_t)((handler >> 16) & 0xFFFF),
        .offset_high = (uint32_t)((handler >> 32) & 0xFFFFFFFF),
        .zero        = 0
    };

  
   // serial_write_hex64(*(uint64_t *)&idt[0]);
   // serial_write_hex64(*(uint64_t *)&idt[0]+1);
//    set_idt_gate( 2, (uint64_t)isr2);
//    set_idt_gate( 3, (uint64_t)isr3);
//    set_idt_gate( 4, (uint64_t)isr4);
//    set_idt_gate( 5, (uint64_t)isr5);
//    set_idt_gate( 6, (uint64_t)isr6);
//    set_idt_gate( 7, (uint64_t)isr7);
//    set_idt_gate( 8, (uint64_t)isr8);
//    set_idt_gate( 9, (uint64_t)isr9);
//    set_idt_gate(10, (uint64_t)isr10);
//    set_idt_gate(11, (uint64_t)isr11);
//    set_idt_gate(12, (uint64_t)isr12);
//    set_idt_gate(13, (uint64_t)isr13);
//    set_idt_gate(14, (uint64_t)isr14);
//    set_idt_gate(15, (uint64_t)isr15);
//    set_idt_gate(16, (uint64_t)isr16);
//    set_idt_gate(17, (uint64_t)isr17);
//    set_idt_gate(18, (uint64_t)isr18);
//    set_idt_gate(19, (uint64_t)isr19);
//    set_idt_gate(20, (uint64_t)isr20);
//    set_idt_gate(21, (uint64_t)isr21);
//    set_idt_gate(22, (uint64_t)isr22);
//    set_idt_gate(23, (uint64_t)isr23);
//    set_idt_gate(24, (uint64_t)isr24);
//    set_idt_gate(25, (uint64_t)isr25);
//    set_idt_gate(26, (uint64_t)isr26);
//    set_idt_gate(27, (uint64_t)isr27);
//    set_idt_gate(28, (uint64_t)isr28);
//    set_idt_gate(29, (uint64_t)isr29);
//    set_idt_gate(30, (uint64_t)isr30);
//    set_idt_gate(31, (uint64_t)isr31);
    // ... up to isr31
    asm volatile("lidt %0" : : "m"(idt_ptr));

}
