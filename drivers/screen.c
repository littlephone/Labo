#include "screen.h"
#include "ports.h"
//#include "../kernel/string.h"

/* private function declaration */
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char colorattr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);


void printk_at(char *message, int col, int row){
	int offset;
	if(col >=0 && row >=0)
	   offset= get_offset(col, row);
	else{
           /*User will supply the col and row number
            *IF col, row are negative, use current offset */
	   offset= get_offset(col,row);
	   row = get_offset_row(offset);
	   col = get_offset_col(offset);
	}
	for(int i=0; message[i]!='\0';){
	   offset = print_char(message[i], col, row, WHITE_ON_BLACK);
	   i++;      /*Calculate the position of next char*/
	   row = get_offset_row(offset);
	   col = get_offset_col(offset);
	}
}

void printk(char *message){
	printk_at(message, -1, -1);
}

void clear_screen(){
    int dip_size= MAX_COLS * MAX_ROWS;     
    int i;
    char *screen = VIDEO_ADDR;
    /* Delete all the contents on screen recursively */
    for(int i=0; i< dip_size; i++){
       screen[i*2] = ' ';
       screen[i*2+1]= WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0,0));
}

void printk_backspace(){
	int offset = get_cursor_offset()-2;
        int row = get_offset_row(offset);
        int col = get_offset_col(offset);
        print_char(0x0, col, row, WHITE_ON_BLACK);
        set_cursor_offset(offset);
}

/* -----------------Private functions starts below------------------
 * These functions are only being used to AID THE PUBIC FUNCTIONS */

/* The VGA cells will take two bytes.
/* One for Character, One for attribute */
int print_char(char c, int col, int row, char colorattr){
    unsigned char *videomem = (unsigned char *) VIDEO_ADDR;
    if(!colorattr) colorattr = WHITE_ON_BLACK;
    /*Run following if error happens, print a red E */
    if (col >= MAX_COLS || row >= MAX_ROWS){
       /*Dealing with print space errors */
       videomem[2*(MAX_ROWS)*(MAX_COLS)-4] = 'E';
       videomem[2*(MAX_ROWS)*(MAX_COLS)-3]= RED_ON_WHITE;
       return get_offset(col, row);
    }
    int offset; 
    if(col >=0 && row >=0) offset=get_offset(col,row);
    else offset= get_cursor_offset(); 
    if(c== '\n'){
      row = get_offset_row(offset);
      offset=get_offset(0, row+1);
    } else {
      videomem[offset]= c;
      videomem[offset +1] = colorattr;
      offset = offset +2;
    }
    /*1. After every print, let's see if the offset has left the screen :( */
    if(offset >= MAX_ROWS * MAX_COLS *2){
      int i; 
      for(i=1; i<MAX_ROWS;i++){
         /* memcopy should REPLACE HERE 
          * 2. Here we will copy every line to 1 line above*/
         memcpy(get_offset(0,i-1) + VIDEO_ADDR,
                  get_offset(0, i) + VIDEO_ADDR, 
                  MAX_COLS * 2);
      }
      /* 3. Then we empty the last line*/
      char *last_line = get_offset(0, MAX_ROWS-1)+VIDEO_ADDR;
      for(i=0; i< MAX_COLS *2 ;i++) last_line[i] =0;
      /* 4. Subtract the offset back one line to prevent error happens :I*/
         offset-= 2*MAX_COLS;
    }
    set_cursor_offset(offset);
    return offset;
}


int get_cursor_offset(){
    port_byte_out(REG_SCREEN_CTRL,14);
    /*Move 8 bit to left to get the higher byte */
    int offset = port_byte_in(REG_SCREEN_DATA) << 8 ;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset *2; /* Current offset == Position x size of char */
}

void set_cursor_offset(int offset){
    /* Instead of getting cursor, we are writing our 
     * cursor to specific values :) */
    offset = offset /2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));    
}


int get_offset(int col, int row){
    return 2*(row*MAX_COLS+col); /* Data Structure offset */
}

int get_offset_row(int offset){
    return offset / (2* MAX_COLS);
}

int get_offset_col(int offset){
    int getrow= get_offset_row(offset);
    return (offset - (getrow)*2*MAX_COLS)/2;
}
