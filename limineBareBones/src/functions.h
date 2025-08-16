#ifndef FUNCTIONS_H 
#define FUNCTIONS_H

#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include "functions.h"


void write_string(const char *string, const uint8_t char_font[0x7F][8], uint32_t color, struct limine_framebuffer *fb, uint32_t x, uint32_t y);
void write_char(const char character, const uint8_t char_font[0x7F][8], uint32_t color, struct limine_framebuffer *fb, uint32_t x, uint32_t y);
void put_pixel(struct limine_framebuffer *fb, size_t x, size_t y, uint32_t color);

#endif
