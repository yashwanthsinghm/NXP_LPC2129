	 #include<LPC21XX.h>
	 int main()
	 {
	 PINSEL0 = 0X00000002; //second alternative function
	 IO0DIR =  0X00000001; // output
     PWMTCR = 0X02;		 // reset and disable
	 PWMPR = 0X0F;		 // no division
	 PWMMR0 = 1000000;	 // 10 power 6
	 PWMMR1 =  500000;	 // 50% duty cycle
	 PWMMCR = 0X02;		// only reset no interrupt
	 PWMLER = 0X01;		// pwm 1
	 PWMPCR = 0X01<<9;  // enable the pwm
	 PWMTCR = 0X09;  	// enable the counter and counters
	 while(1);
	 return 0;
	 }