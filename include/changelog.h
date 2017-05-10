#ifndef CHANGELOG_H_
#define CHANGELOG_H_

void credits(){
	printk("**Credits**\n");
	printk("Without Nicolas Huang, this project will not be made possible."
               "\n\nThanks for all the help and encouragements!");
	printk("\n\n");
}
void changShow(){
	printk("\n");
	printk("==Changelog=="
	       " \n Credits \n Change Wordings to credits "
               "to give credits to addressee properly (05-09)\n"
               " Use a more structured way to display credits (05-12)\n"
               "\n Keyboard\n"
               " You can now type words below :) (05-09) \n"
               " Add - The ability to access to backspace (05-11) \n"
               " Add - Dollar Sign to make commands more clear (05-10)\n\n"
               " Interrupt \n Repair IRQ Services (05-02)\n");
}

#endif
