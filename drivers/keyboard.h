#include "ports.h"
#include "../include/isr.h"
#include "screen.h"
#include "../kernel/string.h"
#include "../kernel/strmod.h"
#include "../kernel/kernel.h"

//Let's keep definition of frequently used keys here...
#define backspace 0x0e
#define enter 0x1c
#define control 0x1d
#define alt 0x38
#define leftshift 0x2a
#define rightshift 0x36

static char BUF[256];
static int keyset;

//We organize all keys here, using switch cases is such a mess.  :(
const char *scanp[] = { "err", "esc", "1", "2", "3", "4", "5", "6", 
                        "7", "8", "9", "0", "-", "=", "backspace", 
                        "tab", "q", "w", "e", "r", "t", "y", "u", "i", 
                        "o", "p", "[", "]", "enter", "leftcontrol", 
                        "a", "s", "d", "f", "g", "h", "j", "k", "l",
                        ";", "'", "`", "leftshift",  "\\", "z", "x",
                        "c", "v", "b", "n", "m", ",", ".", "/", "rightshift",
                        "*", "leftalt", "Space" };

const char sc_ascii[] = {'?',  '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?',
                         '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
                         'o', 'p', '[', ']', '?', '?', 
                         'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
                         ';', '\'', '`', '?', '\\', 'z','x', 
                         'c', 'v', 'b', 'n', 'm', ',', '.', '/', '?', 
                         '*', '?', ' ' }; 

const char sc_capital[] = {'?', '?', '!', '@', '#', '$', '%', '^',
                           '&', '*', '(', ')', '_', '+', '?',
                           '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U','I', 
                           'O', 'P', '{', '}', '?', '?', 
                           'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
                           ':', '"', '~', '?', '|', 'Z', 'X',
                           'C', 'V', 'B', 'N', 'M', '<', '>', '?', '?',
                           '*', '?', ' ' };

static void keyboard_interrupt(registers_t regs)
{
    //We can receive keyboard signal from port 0x60
    unsigned char scancode = port_byte_in(0x60);
    //We can design keyset like ALT-SHIFT etc. here
    if(scancode == leftshift || scancode == rightshift){
       keyset =1;
       //return null;
    }
    if(scancode == backspace) {
         bkspace(BUF);
         printk_backspace();
    } else if (scancode == enter) {
         printk("\n");
	 input(BUF);
         BUF[0] = '\0';
    } else{
         /*if(keyset == 0){
         char character = sc_ascii[(int)scancode];
         } */
         //We first test the original one, just don't mess up with these...
         print_letter(scancode);
         keyset =0;
    }
}

void init_keyboard(){
     register_interrupt_handler(IRQ1, keyboard_interrupt);
}


void print_letter(unsigned char code){
    char * ascii;
    int shiftpressed;
    //Int2ASCII(shiftpressed, ascii);
    //printk(shiftpressed);
    switch (code) {
       case 0x2: 
          printk("1");
          break;
       case 0x3:
          printk("2");
          break;
       case 0x4:
          printk("3");
          break;
       case 0x5:
          printk("4");
          break;
       case 0x6:
          printk("5");
          break;
       case 0x7:
          printk("6");
          break;   
       case 0x8:
          printk("7");
          break;
       case 0x9:
          printk("8");
          break;
       case 0xA:
          printk("9");
          break;
       case 0xB:
          printk("0");
          break;
       case 0xC:
          printk("-");
          break;
       case 0xD:
          printk("=");
          break;
       case 0xE:
          printk("Bakspc");
          break;
       
       case 0xF:
          printk("        ");
          break;
       case 0x10:
          printk("q");
          break;
       case 0x11:
          printk("w");
          break;
       case 0x12:
          printk("e");
          break;
       case 0x13:
          printk("r");
          break;
       case 0x14:
          printk("t");
          break;
       case 0x15:
          printk("y");
          break;
       case 0x16:
          printk("u");
          break;
       case 0x17:
          printk("i");
          break;
       case 0x18:
          printk("o");
          break;
       case 0x19:
          printk("p");
          break;
       case 0x1A:
          printk("[");
          break;
       case 0x1B:
          printk("]");
          break;
       case 0x1C:
          printk("\n");
          break;
       case 0x1D:
          printk("control");
          break;
       case 0x1e:
          printk("a");
          break;
       case 0x1f:
          printk("s");
          break;
       case 0x20:
          printk("d");
          break;
       case 0x21:
          printk("f");
          break;
       case 0x22:
          printk("g");
          break;
       case 0x23:
          printk("h");
          break;
       case 0x24:
          printk("j");
          break;
       case 0x25:
          printk("k");
          break;
       case 0x26:
          printk("l");
          break;
       case 0x27:
          printk(";");
          break;
       case 0x28:
          printk("'");
          break;
       case 0x29:
          printk("`");
          break;
       case 0x2A:
          //printk("Left Shift")
          //shiftpressed =1;
          break;
       case 0x2B:
          printk("\\");
          break;
       case 0x2c:
          printk("z");
          break;
       case 0x2d:
          printk("x");
          break;
       case 0x2e:
          printk("c");
          break;
       case 0x2f:
          printk("v");
          break;
       case 0x30:
          printk("b");
          break;
       case 0x31:
          printk("n");
          break;
       case 0x32:
          printk("m");
          break;
       case 0x33:
          printk(",");
          break;
       case 0x34:
          printk(".");
          break; 
       case 0x35:
          printk("/");
          break;
       case 0x36:
          //Not a thing to be print if Right Shift is clicked
          break;
       case 0x39:
          printk(" ");
          break;
     /*  default:
          if (code <= 0x7f){
              char *coding;
              printk("Unknown code down\n");  
              printk("Your code is:");
              Int2ASCII(code, coding); 
              printk(coding); 
          } */
    }

}
