#ifndef _STRING_H_
#define _STRING_H_

char * strcpy(const char *str1, const char *str2){
	if(str1 == "" && str2 == "") return 0;
	char *newstr = str1;
	while((*newstr++ = *str2++)!= '\0');
	return newstr;
	
}

int strcmp(const char *str1,const char *str2){
	int result=0;
	while(*str1 != '\0' && *str2 !='\0'){
	  if(*str1 == *str2){+
	   *str1++;
	   *str2++;
          } else break;
	}
	result = str1 -str2;
	if (result >0) return 1;
	else if (result == 0 ) return 0;
	else return -1;
}

int strlen(const char *str){
	int count=0;
	for(;*str != '\0';*str++) count++;
	return count;
}

void memcpy(char *dest, char *src, int nbytes){
       int i;
       for(i=0;i<nbytes;i++){
         *(dest+i) = *(src +i);
       }
}

void Int2ASCII(int n, char str[]){
 /*      asm("movl $0, %%ax\n\t"
             "movl 0xA, %%bx\n"
             "CHANGE: \n\t"
             "xorl %%dx, %%dx\n\t"
             "divl %%bx \n\t"
             "addl %48, %%dx\n\t"
                 "decl %%si\n\t"
                 "movl %%dl,[%%si]\n\t"
                 "cmpl 0, %%ax\n\t"
                 "jel exit\n\t"
                 "jmp CHANGE\n"
                 "exit:"
                 "mov %%edx, $1" 
                 :/*output "=r"(str[i]): /*input "r"(n));
           ) */
       int i, j, sign=n;
       if (sign <0) n= -n;
       i=0;
       do {
          str[i++]= n % 10 +'0';
          n= n/10;
       } while (n > 0);
       if (sign <0) str[i++]= '-';
       str[i]= '\0';
       
       for(int i =0, j = strlen(str)-1; i<j; i++,j--){
            char temp;
            temp = str[i];
            str[i]=str[j];
            str[j]=temp;
       }
}

#endif
