#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"
//#include "../kernel/string.h"   
//TODO: FIX THIS INCLUSION

#define PIC_EOI 0x20
isr_t interrupt_handlers[256];

/*This all can't be done in loop cause we are getting addr of function names
 *However, Control+V helps :) */
void isr_init(){
   set_idt_gate(0, (u32)isr0);
   set_idt_gate(1, (u32)isr1);
   set_idt_gate(2, (u32)isr2);
   set_idt_gate(3, (u32)isr3);
   set_idt_gate(4, (u32)isr4);
   set_idt_gate(5, (u32)isr5);
   set_idt_gate(6, (u32)isr6);
   set_idt_gate(7, (u32)isr7);
   set_idt_gate(8, (u32)isr8);
   set_idt_gate(9, (u32)isr9);
   set_idt_gate(10, (u32)isr10);
   set_idt_gate(11, (u32)isr11);
   set_idt_gate(12, (u32)isr12);
   set_idt_gate(13, (u32)isr13);
   set_idt_gate(14, (u32)isr14);
   set_idt_gate(15, (u32)isr15);
   set_idt_gate(16, (u32)isr16);
   set_idt_gate(17, (u32)isr17);
   set_idt_gate(18, (u32)isr18);
   set_idt_gate(19, (u32)isr19);
   set_idt_gate(20, (u32)isr20);
   set_idt_gate(21, (u32)isr21);
   set_idt_gate(22, (u32)isr22);
   set_idt_gate(23, (u32)isr23);
   set_idt_gate(24, (u32)isr24);
   set_idt_gate(25, (u32)isr25);
   set_idt_gate(26, (u32)isr26);
   set_idt_gate(27, (u32)isr27);
   set_idt_gate(28, (u32)isr28);
   set_idt_gate(29, (u32)isr29);
   set_idt_gate(30, (u32)isr30);
   set_idt_gate(31, (u32)isr31);

   //2.Remapping PIC: See Wikibooks: X86 Assm/ Programmable Interrupt Controller */
   port_byte_out(0x20, 0x11);   /* Use Command 0x20 to restart PIC1 */
   port_byte_out(0xA0, 0x11);   /* Use Command 0xA0 to restart PIC2 */
   port_byte_out(0x21, 0x20);   /* PIC1 data address (0x21) to 0x20 i.e. 32 */
   port_byte_out(0xA1, 0x28);   /* PIC2 data address (0xA1) to 0x28 i.e. 40 */
   port_byte_out(0x21, 0x04);   /*Cascading */
   port_byte_out(0xA1, 0x02);
   port_byte_out(0x21, 0x01);
   port_byte_out(0xA1, 0x01);
   port_byte_out(0x21, 0x0);
   port_byte_out(0xA1, 0x0);

   //3. Install IRQs
   set_idt_gate(32, (u32)irq0);
   set_idt_gate(33, (u32)irq1);
   set_idt_gate(34, (u32)irq2);
   set_idt_gate(35, (u32)irq3);
   set_idt_gate(36, (u32)irq4);
   set_idt_gate(37, (u32)irq5);
   set_idt_gate(38, (u32)irq6);
   set_idt_gate(39, (u32)irq7);
   set_idt_gate(40, (u32)irq8);
   set_idt_gate(41, (u32)irq9);
   set_idt_gate(42, (u32)irq10);
   set_idt_gate(43, (u32)irq11);
   set_idt_gate(44, (u32)irq12);
   set_idt_gate(45, (u32)irq13);
   set_idt_gate(46, (u32)irq14);
   set_idt_gate(47, (u32)irq15);

   set_idt(); //See idt.c, We set and load idt there
}

/*Print message according to definition */
char *exception_message[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


void isr_handler(registers_t reg){
    printk("ERROR ");
    char interrupt[3];
    Int2ASCII(reg.int_no, interrupt);
    printk(interrupt); 
    printk(":\n");
    printk(exception_message[reg.int_no]);
    printk("\n");
}

void register_interrupt_handler(u8 n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t reg){
    /*1.We send End Of Interrupt to the PICS *
     *otherwise they won't send interrupts again*/
    if(reg.int_no >=40) port_byte_out(0xA0, PIC_EOI); /*PIC1 Slave*/
    port_byte_out(0x20, PIC_EOI);
    //2.Then handle the interrupt 
    if(interrupt_handlers[reg.int_no]!=0){
        isr_t handler = interrupt_handlers[reg.int_no];
        handler(reg);
    }
    
}

void irq_init(){
     asm volatile("sti");
     init_timer(50);
     init_keyboard();
}