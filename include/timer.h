#ifndef TIMER_H_
#define TIMER_H_

#include "../drivers/screen.h"
#include "../kernel/string.h"
#include "isr.h"

u32 tick = 0;

static void timer_callback(registers_t regs){
   tick++;
   /* printk("Tick: ");
   char tick_ascii[256];
   Int2ASCII(tick, tick_ascii);
   printk(tick_ascii);
   printk("\n"); */
}

void init_timer(u32 freq){
   /*Install clock interrupt */
   register_interrupt_handler(IRQ0, timer_callback);
   /* Get the PIT value: hardware clock at 11931080 HZ */
   u32 divisor = 1193180 /freq;
   u8 low = (u8) (divisor & 0xFF);
   u8 high = (u8)((divisor >>8 ) & 0xFF);
   
   //Send the command
   port_byte_out(0x43, 0x36);     /*Command port */
   port_byte_out(0x40, low);
   port_byte_out(0x40, high);
}

#endif
