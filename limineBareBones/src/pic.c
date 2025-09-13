#include <stdint.h>

#define irq_master 0x21
#define irq_slave 0xA1

inline void outb(uint16_t p, uint8_t v){
  __asm__ volatile("outb %0,%1"::"a"(v),"Nd"(p)); 
}
inline uint8_t inb(uint16_t p){
  uint8_t v;
  __asm__ volatile("inb %1,%0":"=a"(v):"Nd"(p)); 
  return v; 
}
inline void io_wait(void){ 
  outb(0x80, 0); 
}

void pic_remap(void){
 // uint8_t a1 = inb(0x21), a2 = inb(0xA1);        // save masks

  outb(0x20, 0x11); /* write ICW1 to PICM, we are gonna write commands to PICM */
  outb(0xA0, 0x11); /* write ICW1 to PICS, we are gonna write commands to PICS */
  
  outb(0x21, 0x20); /* remap PICM to 0x20 (32 decimal) */
  outb(0xA1, 0x28); /* remap PICS to 0x28 (40 decimal) */
  
  outb(0x21, 0x04); /* IRQ2 -> connection to slave */ 
  outb(0xA1, 0x02);
  
  outb(0x21, 0x01); /* write ICW4 to PICM, we are gonna write commands to PICM */
  outb(0xA1, 0x01); /* write ICW4 to PICS, we are gonna write commands to PICS */

  //outb(0x21, a1);       /*restore masks*/
  //outb(0xA1, a2); 
  outb(0x21, 0xFF); //0xFF is al
  outb(0xA1, 0xFF);
}

void enable_irq(uint8_t irq_num){
  uint8_t mask;
  if (irq_num < 8){//master
    mask = inb(irq_master); //read current mask
    mask &= ~(1 << irq_num); //unmask needed bit
    outb(irq_master, mask);

  }
  if (irq_num >= 8){
    mask = inb(irq_slave);
    mask &= ~(1 << irq_num);
    outb(irq_slave, mask);
  }
}




