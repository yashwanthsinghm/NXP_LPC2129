#include<LPC21XX.h>
#define RS 0X01000000
#define EN 0X02000000
void delay(unsigned long int x);
void lcdwrt(unsigned char y);
void uart_init(void);

unsigned char cmd[5]={0x38,0x0E,0x06,0x01,0x80};
unsigned char msg1[]="hello yashwanth";





int main()
{
int i;
char c;
uart_init();
IO0DIR =0X000000FF;
IO1DIR =0X03000000;
IO1CLR=RS;
for(i=0;i<5;i++)
lcdwrt(cmd[i]);
IO1SET=RS;
while(1){
while((U1LSR&0X01)==0)
{}
c=U1RBR;
U1THR =c;
while((U1LSR&0x40)==0)
{}
/*IO1SET=RS;
lcdwrt(0x01);
IO1SET=RS;	*/
lcdwrt(c);
}
}

void uart_init()
{	   PINSEL0 = 0x00050000;  //0101
	   U1LCR = 0X83;//8 for enabling 3 for 8 bit data
	   U1DLM = 0X00;// 
	   U1DLL = 0X061;// decimal value= 97.5 for 9600 baud rate 
	   U1LCR = 0X03;  // disable for 8bit
}







void lcdwrt(unsigned char y)
{
IO0PIN=y;
IO1SET=EN;
delay(0x5000);
IO1CLR=EN;
delay(0x5000);
}

void delay(unsigned long int x){
unsigned long int i;
for(i=0;i<x;i++);
}
