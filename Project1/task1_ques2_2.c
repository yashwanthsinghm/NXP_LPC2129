#include<lpc21xx.h>

void timer0_init();

int main()
{
   unsigned long int x,flag=0,j=0;	   
   IO0DIR=0X000000FF;
   timer0_init();
	  x=0x7F;
      while(1)
		{ 
	 if(T0IR==0x01 && j<2 ) {
	 T0IR = 0X01;
	 IO0PIN=~x;/// due to led are active low(on board)
	 x=x>>1|0x80;
     flag = flag+1;
     if(flag==8)
	     {
		 x=0x7F;
		 flag=0;
		 j++;
		 }	
		 }
	}
	
}
 

 void timer0_init(){   
 T0TCR = 0x02;  
 T0PR  =0x0F;
 T0MCR =0x03;        
 T0MR0 = 0xF4240;
 T0TCR = 0X01;


 }