#include<LPC21XX.h>
#include<string.h>

void timer0_delay(unsigned int x);
void delay(unsigned long int x);
void uart_write(char c);
char uart_read(void);
void uart_init(void);
void uart_nextline(void);

int main()
{ char c;
uart_init();
  IO0DIR = 0X00000F00;
  IO0PIN = 0X00000F00;
  while(1)
  {
  c =uart_read();
  switch(c)
  {
     case 'A': IO0CLR = (0X00000100);
	          break;
     case 'B': IO0CLR = (0X00000200);
	          break;
     case 'C': IO0CLR = (0X00000400);
	          break;
     case 'D': IO0CLR = (0X00000800);
	          break;
     case 'a': IO0PIN = IO0PIN|0X100;
	          break;
     case 'b': IO0PIN = IO0PIN|0X200;
	          break;
     case 'c': IO0PIN = IO0PIN|0X400;
	          break;
     case 'd': IO0PIN = IO0PIN|0X800;
	          break;
	default :
	          break;
  }
  }
}




void uart_write(char c)
 {
 U0THR =c;
while((U0LSR&0x40)==0)
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
while((U0LSR&0X01)==0);
c=U0RBR;
U0THR =c;
while((U0LSR&0x40)==0);
return c;
}


 void delay(unsigned long int x){
unsigned long int i;
for(i=0;i<x;i++);
}



void uart_init(void)
{	   PINSEL0 = 0x00000005;  //0101
	   U0LCR = 0X83;//8 for enabling 3 for 8 bit data
	   U0DLM = 0X00;// 
	   U0DLL = 0X061;// decimal value= 97.5 for 9600 baud rate 
	   U0LCR = 0X03;  // disable for 8bit
}

 void timer0_delay(unsigned int x){   
 T0TCR = 0x02;  
 T0PR  =0x0F;
 T0MCR =0x07; //       
 T0MR0 = 0xF4240*x;
 T0TCR = 0X01;
while(T0IR!=0x01)
  {}
  T0IR=0X01	;

	}
