	 #include<LPC21XX.h>
	 int main()
	 {
	 PINSEL0 = 0X000000A; //second alternative function
	 IO0DIR =  0X00000003; // output
     PWMTCR = 0X02;		 // reset and disable
	 PWMPR = 0X0F;		 // no division
	 PWMMR0 = 1000000;	 // 10 power 6
	 PWMMR1 =  500000;
	 PWMMR3 =  100000;	 // 50% duty cycle
	 PWMMCR = 0X02||0X01<<11;		// only reset no interrupt
	 PWMLER = 0X03;		// pwm 1 ,pwm2
	 PWMPCR = 0X01<<9|0X01<<11;  // enable the pwm
	 PWMTCR = 0X09;  	// enable the counter and counters
	 while(1);
	 return 0;
	 }