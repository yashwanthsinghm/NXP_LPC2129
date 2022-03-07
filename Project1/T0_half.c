#include<lpc21xx.h>

void timer0_init();


int main()
{	   
IO0DIR=0X000000FF;
timer0_init();


		while(1)
		{ 
	 while(T0IR==0x01) {
	 IO0PIN=0X000000FF^IO0PIN;
      T0IR = 0X01;		
	  	}
		}
	
}
 

 void timer0_init(){   
 T0TCR = 0x02;  
       
 T0PR  =0x0F;
                
 T0MCR =0x03;        
 T0MR0 = 0x7A120;
 T0TCR = 0X01;


 }
   

