#include "idt.h"
//#include "../kernel/string.h"

/*This function is being used to set idt (for interrupts)
 *Your mouse will ONLY WORK WITH THIS DOCUMENT :P
 *This IS NOT KIDDING, it's being linked with Assembly !
 */
void set_idt_gate(int n, u32 handler){
    idt[n].low_offset = low_16(handler);
    idt[n].selector = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = high_16(handler);
}

void set_idt(){
    idt_reg.base = (u32) &idt;      /*Convert idt address to u32 type, then give
                                     *give value to idt base;   */
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) -1;
    
    /* Only load &idt_reg, loading &idt is a mistake !! */
    asm volatile("lidtl (%0)": /*No output */ :/*Input: */ "r" (&idt_reg));
}
