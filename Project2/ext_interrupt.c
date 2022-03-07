#include<LPC21XX.h>
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

__irq void IRQ_handler()
{

 IO0PIN = 0X00;
 timer0_delay(2);
 IO0PIN = 0X01;
 EXTINT |= (0x01);
 VICVectAddr = 0;
}

int main()
{  
IO0DIR= 0X00000001;	 // led p0.0
PINSEL0 =0X0C;  // p0.1 3rd alternate function   
//EXTMODE = 0x01;	 // select edge  triggered 
//EXTPOLAR =0x00;// &=~(0X01);	  // falling edge
//VICSoftInt &= ~(1<<14); // 14 bit is external interrupt negation to Select IRQ mode
VICIntSelect = 0X00000000;
VICVectAddr0 = (unsigned int) IRQ_handler;  // type casting to unsigned int and assignment 
VICVectCntl0 =  (1<<5)|14;  
VICIntEnable  = (1<<14);// enable the external int0
EXTINT &= ~(0x01);
  while(1)
  {	 IO0PIN = 0X01;
  }
}

