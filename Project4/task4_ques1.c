#include<LPC21XX.h>
void uart_init(void);
void delay(unsigned long int x);
void timer0_delay(unsigned int x);
unsigned char msg[]="hello yash";


int main()
{	
char c='a';
IO0DIR =0X00000000;
uart_init();
while(1)
{  
if(!((IO0PIN>>8 & 0X01))){
 
U0THR =c;
while((U0LSR&0x40)==0)
{}
/*
if(j>9)
{
j=0;
k=k+1;
}*/
timer0_delay(1);
c++;
}

}


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
