#include<LPC21XX.h>
void uart_init();
void delay(unsigned long int x);
unsigned char msg[]="hello yash";


int main()
{	int i;
uart_init();
for(i=0;msg[i]!='\0';i++)
{
U0THR =msg[i];
while((U0LSR&0x40)==0)
{}
delay(0x1000);
}
while(1)
{}

}
void uart_init()
{	   PINSEL0 = 0x00000005;  //0101
	   U0LCR = 0X83;//8 for enabling 3 for 8 bit data
	   U0DLM = 0X00;// 
	   U0DLL = 0X061;// decimal value= 97.5 for 9600 baud rate 
	   U0LCR = 0X03;  // disable for 8bit
}	  

void delay(unsigned long int x)
{
unsigned long int i;
for(i=0;i<x;i++);
} 
