#ifndef IDT_H
#define IDT_H

#include "types.h"

/*Select code segments in 0x08 */
#define KERNEL_CS 0x08

/*Every interrupt handlers are defined like below */
typedef struct{
   u16 low_offset;
   u16 selector;            /* kernel segment selector */
   u8 always0;
   /* Bit 7: "Interrupt present"
    * Bit 6-5: Level of caller
    * Bit 4: Set to 0-> Interrupt Gates
    * Bit 3-0: bits 1110 = "32 bit interrupt gate" */
   u8 flags;
   u16 high_offset; /* handler function address */
}__attribute__((packed)) idt_gate_t;

typedef struct{
   u16 limit;
   u32 base;
}__attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];    /* IDT ENTRIES is defined in line 8 */
idt_register_t idt_reg;
/*There will be 256 idt_entries, being stored in idt_gate */

/*Protected API for idt.c */
void set_idt_gate(int n, u32 handler);
void set_idt();
#endif
