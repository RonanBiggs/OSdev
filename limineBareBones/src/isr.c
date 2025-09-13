#include <limine.h>
#include "functions.h"
#include "font.h"
#include <stdint.h>
#include <stdio.h>
#include "serial.h"
void isr_handler(uint64_t* regs) {
    uint64_t int_no = regs[15]; // Assuming correct stack layout
    // Add custom handlers or halt
    serial_write("isr yay");
    while (1) __asm__ volatile("hlt");
}
