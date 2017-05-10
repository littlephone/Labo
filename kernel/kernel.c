#include"../drivers/screen.h"
#include "../include/isr.h"
#include "../include/timer.h"
#include "../drivers/keyboard.h"
#include "../include/changelog.h"

void main() {
	/*
         We attempted to use the old school
         methods to print our string :) */
        /*This code is already very old , since the commented
        /*code is being authored at 2017.04. Please refer to 17.4.X version ...
         */
        clear_screen();      //There is still bios thing remaining, so we clear
                             //them off first before continue

//------Show acknowledge HERE :) 
        printk_at("Labo Trial System 17.5.13\n",1,1);
        credits();
        changShow();
//------ Ends HERE
        isr_init();
        irq_init();
	printk("$");

}
