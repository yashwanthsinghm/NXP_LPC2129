#include<LPC21XX.h>
void uart_init();
void delay(unsigned long int x);
unsigned char msg[]="hello yash";


int main()
{	int i;
uart_init();
for(i=0;msg[i]!='\0';i++)
{
U1THR =msg[i];
while((U1LSR&0x40)==0)
{}
delay(0x1000);
}
while(1)
{}

}
void uart_init()
{	   PINSEL0 = 0x00050000;  //0101
	   U1LCR = 0X83;//8 for enabling 3 for 8 bit data
	   U1DLM = 0X00;// 
	   U1DLL = 0X061;// decimal value= 97.5 for 9600 baud rate 
	   U1LCR = 0X03;  // disable for 8bit
}	  

void delay(unsigned long int x)
{
unsigned long int i;
for(i=0;i<x;i++);
} 
