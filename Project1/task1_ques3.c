#include<lpc21xx.h>

void timer0_init();


int main()
{
unsigned long int x;	   
IO0DIR=0X000000F;
timer0_init();
	   
	   x=0x0F;

		while(1)
		{ 
	 while(T0IR==0x01) {

	 IO0PIN=~x;/// due to led are active low(on board)
	 x=	x+1;
      T0IR = 0X01;

	  	
	  	}
		}
	
}
void timer0_init()
{   
 T0TCR = 0x02;  
 T0PR  =0x0F;
 T0MCR =0x03;        
 T0MR0 = 0x1E8480;
 T0TCR = 0X01;
}

   