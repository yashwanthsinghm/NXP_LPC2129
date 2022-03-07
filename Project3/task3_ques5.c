#include<lpc21xx.h>

void pwm_init(void);
void timer0_init(void);
void uart_init(void);
void uart_write(char c);
void uart_nextline(void);
char uart_read(void);
void delay(unsigned long int x);
//void timer0_delay(unsigned int x);

int rising1,falling1,rising2;
int i=0;

__irq void isr_handler(void)
{   
    if(i==0)
    { 
	  rising1=T0CR0;
	  T0CCR=0X06;
	}
	else if(i==1)
	{
	falling1=T0CR0;
	T0CCR=0x05;
	}
	else if(i==2)
	{
	rising2 = T0CR0;
	}
	i++;
	T0IR |=0x10;
	VICVectAddr = 0x00;	

}

int main()
{
timer0_init();
pwm_init();
uart_init();
IO0DIR = 0X00000080;
VICVectAddr0 = (unsigned int) isr_handler;
VICVectCntl0 = 1<<5|4;
VICIntSelect = 0x00000000;
VICIntEnable = 1<<4;
while(1)
{
 if(i==2)
 {
 int freq =15000000/(((rising1-rising2)/240000)*15000);
 int duty_cycle=((rising1+5-falling1)/(rising1-rising2))*100; 
  while(freq>0)
  {
  int digit = freq%10;
  uart_write(digit+'0');
  freq = freq/10;
  }
  //uart_write('a');
    while(duty_cycle>0)
  {
  int digit = duty_cycle%10;
  uart_write(digit+0x30);
  duty_cycle = duty_cycle/10;
  }	 
 }

}
}



void timer0_init()
{
 PINSEL0 |=0X00000020;	//pin 0.2 second alternative function
 T0TCR=0X02;
 T0CCR=0X05;
 T0PR=0X00;
 T0TCR=0X01;

}

void pwm_init(void)
{
     PINSEL0 |= 0X00008000; //second alternative function
	 IO0DIR =  0X00000080; // output
     PWMTCR = 0X02;		 // reset and disable
	 PWMPR = 0X0F;		 // no division
	 PWMMR0 = 15000;	 // 10 power 6
	 PWMMR2 =  7500;	 // 50% duty cycle
	 PWMMCR = 0X02;		// only reset no interrupt
	 PWMLER = 0X05;		// pwm 2
	 PWMPCR = 0X01<<10;  // enable the pwm 2
	 PWMTCR = 0X09;  	// enable the counter and counters
	
}


void uart_init()
{	   PINSEL0 |= 0x00000005;  //0101
	   U0LCR = 0X83;//8 for enabling 3 for 8 bit data
	   U0DLM = 0X00;// 
	   U0DLL = 0X061;// decimal value= 97.5 for 9600 baud rate 
	   U0LCR = 0X03;  // disable for 8bit
}



void uart_write(char c)
 {
 U0THR =c;
while((U0LSR&0x40)==0)
{}
delay(0x1000);
 }

 void uart_nextline(void)
 {
  uart_write(0x0D);
  uart_write(0x0A);
 }



char uart_read(void)
{
char c;
while((U0LSR&0X01)==0);
c=U0RBR;
U0THR =c;
while((U0LSR&0x40)==0);
return c;
}


 void delay(unsigned long int x){
unsigned long int i;
for(i=0;i<x;i++);
}

  /*
 void timer0_delay(unsigned int x){   
 T0TCR = 0x02;  
 T0PR  =0x0F;
 T0MCR =0x03; //       
 T0MR0 = 0xF4240*x;
 T0TCR = 0X01;
while(T0IR!=0x01)
  {}
  T0IR=0X01	;

	}	  

   */