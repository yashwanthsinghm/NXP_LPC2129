#include<lpc21xx.h>

void timer0_init();
/*void isr(void){
  VICIntEnable = 0x00000000;
IO0PIN = IO0PIN^0x000000FF;
T0IR = 0X00;
 VICIntEnable = 0x00000010;
} */

int main()
{	   
IO0DIR=0X000000FF;
timer0_init();
//VICVectAddr0 = (unsigned) isr;
//VICIntSelect =0x00000000;
//VICIntEnable = 0x00000010;

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
 T0MR0 = 0xF4240;	//1sec
 T0TCR = 0X01;


 }
   

