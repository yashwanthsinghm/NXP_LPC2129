#include<LPC21XX.h>
 void timer0_delay(unsigned int x){   
 T0TCR = 0x02; /// timer select 
 T0PR  =30;  //divide by 16
 T0MCR =0x03; //  stop,reset,interrupt     
 T0MR0 = x;// x=1 then 1sec
 T0TCR = 0X01;	   // enable the timer
while(T0IR!=0x01)  // wait until the IR flag is 1
  {}			  
  T0IR=0X01	;	   // clear the flag
}

__irq void IRQ_handler(void)
{

 //IO0PIN = 0X00|0x04;
 IO0CLR =0X00000001;
 timer0_delay(1000000);
 //IO0PIN = 0X01|0x04;
 IO0SET =0X00000001;
 timer0_delay(2000);
 EXTINT |= 0x01;
 VICVectAddr = 0x00;
}

int main()
{  
 // p0.1 3rd alternate function   
	 // select edge  triggered 

//EXTPOLAR =0x00;// &=~(0X01);	  // falling edge
//VICSoftInt &= ~(1<<14); // 14 bit is external interrupt negation to Select IRQ mode

VICVectAddr0 = (unsigned int) IRQ_handler;  // type casting to unsigned int and assignment 
VICVectCntl0=0x0000002E;
//VICVectCntl0 =  (1<<5)|14;  
//VICIntEnable  = (1<<14);// enable the external int0
VICIntEnable = 0x00004000;
//VICIntSelect = 0X00000000;
PINSEL0 =0X0000000C; 
EXTINT &=~(0x01);
EXTMODE = 0x00;

IO0DIR= 0X00000005;	 // led p0.0
IO0PIN = 0X00000005;
//IO0SET =0X01;
  while(1)
  {	 /* IO0PIN = (IO0PIN ^ 0X04)|0x01;
      timer0_delay(1);	  */
	  IO0CLR  = 0X04;
	  timer0_delay(250000); 
	  IO0SET  = 0X04;
	  timer0_delay(250000);
 
  }
}

