#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include "functions.h"

void put_pixel(struct limine_framebuffer *fb, size_t x, size_t y, uint32_t color){
  //out of bounds check
  if(x >= fb->width || y >= fb->height){
    return;
  } volatile uint32_t *pixel = (volatile uint32_t*)fb->address + (y * (fb->pitch / 4) + x);
  *pixel = color;
}

void write_char(const char character, const uint8_t char_font[0x7F][8], uint32_t color, struct limine_framebuffer *fb, uint32_t x, uint32_t y){
  for(size_t col = 0; col < 8; col++){
      for(size_t row = 0; row < 8; row++){
        if(char_font[character][row] & (1 << (col))){
          put_pixel(fb, x + col, y + row, color);
      }  
    }
  }
}

void write_string(const char *string, const uint8_t char_font[0x7F][8], uint32_t color, struct limine_framebuffer *fb, uint32_t x, uint32_t y){
  size_t char_col; //char collumn to keep track of when new line is needed without directly using i and affecting the loop
  for (size_t i = 0; string[i] != '\0'; i++){
  char_col++;
  //wrap text
  if(char_col>128){
      char_col=0;
      y+=10;
  }
  //TODO: maybe optimize this so there arent two similar if statements back to back
  //handle newline
  if(string[i] == '\n'){
      char_col=0;
      y+=10;
      continue;
  }
  write_char(string[i], char_font, color, fb, x + char_col*10, y);
  } 
}
