#include<LPC21XX.h>
 void timer0_delay(unsigned int x){   
 T0TCR = 0x02; /// timer select 
 T0PR  =0x0F;  //divide by 16
 T0MCR =0x03; //  stop,reset,interrupt  //timer should not stop    
 T0MR0 = 0xFA120*x;// x=1 then HALF sec
 T0TCR = 0X01;	   // enable the timer
while(T0IR!=0x01)  // wait until the IR flag is 1
  {}			  
  T0IR=0X01	;	   // clear the flag
}

__irq void IRQ_handler1()
{

 IO0PIN = 0X00|0X10|0X04;
 timer0_delay(2);
 IO0PIN = 0X01|0X10|0X04;
 timer0_delay(2);
 EXTINT |= (0x01);
 VICVectAddr = 0;
}

__irq void IRQ_handler2()
{

 IO0PIN = 0X00|0X04|0X01;
 timer0_delay(1);
 IO0PIN = 0X010|0X04|0X01;
 timer0_delay(1);
 EXTINT |= (0x02);
 VICVectAddr = 0;
}

int main()
{  
IO0DIR= 0X00000015;	 // led p0.0
PINSEL0 =0XCC;  // p0.1 3rd alternate function   
//EXTMODE = 0x01;	 // select edge  triggered 
//EXTPOLAR =0x00;// &=~(0X01);	  // falling edge
//VICSoftInt &= ~(1<<14); // 14 bit is external interrupt negation to Select IRQ mode
VICIntSelect = 0X00000000;
VICVectAddr0 = (unsigned int) IRQ_handler1;  // type casting to unsigned int and assignment 
VICVectCntl0 =  (1<<5)|14;  
VICVectAddr1 = (unsigned int) IRQ_handler2;  // type casting to unsigned int and assignment 
VICVectCntl1 =  (1<<5)|15;
VICIntEnable  = (1<<14)|(1<<15);// enable the external int0
EXTINT &= ~(0x03);
IO0SET =0X15;
  while(1)
  {	 IO0SET =  0X04;
      timer0_delay(2);
	  IO0CLR =  0X04;
	  timer0_delay(2);
  }
}

