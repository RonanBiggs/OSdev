//this file sets up com for debug messages. no other uses atm
#include <stdint.h>
#define COM1         0x3F8
#define RX           0    // +0
#define TX           0    // +0
#define IER          1
#define FCR          2
#define LCR          3
#define MCR          4
#define LSR          5
#define DLL          0    // when DLAB=1
#define DLM          1    // when DLAB=1

static int serial_initialized = 0;


static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void serial_init(void) {
    outb(COM1 + IER, 0x00);         // Disable interrupts
    outb(COM1 + LCR, 0x80);         // Enable DLAB
    outb(COM1 + DLL, 0x01);         // Divisor low  (115200 baud => divisor 1)
    outb(COM1 + DLM, 0x00);         // Divisor high
    outb(COM1 + LCR, 0x03);         // 8 bits, no parity, 1 stop (8N1)
    outb(COM1 + FCR, 0xC7);         // Enable FIFO, clear, 14-byte threshold
    outb(COM1 + MCR, 0x0B);         // IRQs disabled, RTS/DSR set
    serial_initialized = 1;
}

static int tx_ready(void) {
    // Bit 5 (0x20) of LSR = THRE (Transmit Holding Register Empty)
    return inb(COM1 + LSR) & 0x20;
}

void serial_putc(char c) {
    if (!serial_initialized) serial_init();
    while (!tx_ready()) { /* spin */ }
    outb(COM1 + TX, (unsigned char)c);
}

void serial_write(const char* s) {
    for (; *s; ++s) {
        if (*s == '\n') serial_putc('\r');
        serial_putc(*s);
    }
}
 void serial_write_hex64(uint64_t val) {
    char buf[17];
    const char* digits = "0123456789ABCDEF";
    buf[16] = '\0';
    for (int i = 15; i >= 0; i--) {
        buf[i] = digits[val & 0xF];
        val >>= 4;
    }
    serial_write(buf);
}
