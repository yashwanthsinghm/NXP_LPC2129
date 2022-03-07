#include<LPC21XX.h>
#include<string.h>
#define RS 0X01000000
#define RW 0X02
#define EN 0X02000000

void timer0_delay(unsigned int x);
void uart_write(char c);
char uart_read(void);
void uart_init(void);
void uart_nextline(void);
void delay(unsigned long int x);





  int main()
  {	int i,j;
  uart_init();
  for(i=0;i<10;i++)
  {
  for(j=0;j<10;j++)
  {
	uart_write(i+'0');
	uart_write(j+'0');
	uart_nextline();
	timer0_delay(1);
  }
  }



  }







void uart_write(char c)
 {
 U1THR =c;
while((U1LSR&0x40)==0)
{}
delay(0x1000);
 }

 void uart_nextline(void)
 {
  uart_write(0x0D);
  uart_write(0x0A);
 }



char uart_read(void)
{
char c;
while((U1LSR&0X01)==0);
c=U1RBR;
U1THR =c;
while((U1LSR&0x40)==0);
return c;
}


void uart_init(void)
{	   PINSEL0 = 0x00050000;  //0101
	   U1LCR = 0X83;//8 for enabling 3 for 8 bit data
	   U1DLM = 0X00;// 
	   U1DLL = 0X061;// decimal value= 97.5 for 9600 baud rate 
	   U1LCR = 0X03;  // disable for 8bit
	  // U1IER = 0x00000001;
}
 void delay(unsigned long int x){
unsigned long int i;
for(i=0;i<x;i++);
}

 void timer0_delay(unsigned int x){   
 T0TCR = 0x02; /// timer select 
 T0PR  =0x0F;  //divide by 16
 T0MCR =0x07; //  stop,reset,interrupt     
 T0MR0 = 0xF4240*x;// x=1 then 1sec
 T0TCR = 0X01;	   // enable the timer
while(T0IR!=0x01)  // wait until the IR flag is 1
  {}			  
  T0IR=0X01	;	   // clear the flag
}