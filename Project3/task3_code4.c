#include<LPC21XX.h>
void timer0_delay(unsigned int x);
int main()
{
 PINSEL0 = 0X00000002; //second alternative function
	 IO0DIR =  0X00000001; // output
     PWMTCR = 0X02;		 // reset and disable
	 PWMPR = 0X0F;		 // no division
	// PWMMR0 = 1000000;	 // 10 power 6
	// PWMMR1 =  500000;	 // 50% duty cycle

	  	PWMMR0 = 1000;	 // 10 power 6
     PWMMR1 =  500;	 // 50% duty cycle

	 PWMMCR = 0X02;		// only reset no interrupt
	 PWMLER = 0X01;		// pwm 1
	 PWMPCR = 0X01<<9;  // enable the pwm
	 PWMTCR = 0X09;  	// enable the counter and counters
	  while(1)
	  {
	   if(!(IO0PIN & 0X02))
         {	
	 PWMMR1 =  250;	 // 25% duty cycle
	 PWMMCR = 0X02;		// only reset no interrupt
	 PWMLER = 0X02;		// pwm 1
	 PWMPCR = 0X01<<9;  // enable the pwm
	 PWMTCR = 0X09; 
      timer0_delay(1);    
	  }
	  	  else if(!(IO0PIN & 0X04))
         {	
	 PWMMR1 =  500;	 // 25% duty cycle
	 PWMMCR = 0X02;		// only reset no interrupt
	 PWMLER = 0X02;		// pwm 1
	 PWMPCR = 0X01<<9;  // enable the pwm
	 PWMTCR = 0X09; 
      timer0_delay(1);    
	  }
	  	  	  else if(!(IO0PIN & 0X08))
         {	
	 PWMMR1 =  750;	 // 25% duty cycle
	 PWMMCR = 0X02;		// only reset no interrupt
	 PWMLER = 0X02;		// pwm 1
	 PWMPCR = 0X01<<9;  // enable the pwm
	 PWMTCR = 0X09; 
      timer0_delay(1);    
	  }
	  	  	  	  else if(!(IO0PIN & 0X10))
         {	
	 PWMMR1 =  1000;	 // 25% duty cycle
	 PWMMCR = 0X02;		// only reset no interrupt
	 PWMLER = 0X02;		// pwm 1
	 PWMPCR = 0X01<<9;  // enable the pwm
	 PWMTCR = 0X09; 
      timer0_delay(1);    
	  }
	  }
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