#ifndef KERNEL_H_
#define KERNEL_H_

void input(char *input){
	if(strcmp(input, "halt")==0){
            printk("The system will halt now! ");
            asm("hlt");
        }
}

#endif
