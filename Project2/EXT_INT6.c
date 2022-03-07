#include<lpc21xx.h>



void delay(int x)
{
	T0TCR=0X02;
	T0PR=30;
	T0MCR=0X03;
	T0MR0=x;
	T0TCR=0X01;
	while(T0IR!=0X01);
	T0IR=0X01;
}



__irq void eint0(void)
{
	IO0SET=0X00000008;
	delay(20000);
	IO0CLR=0X00000008;
	delay(20000);

	EXTINT|=0X01;
	VICVectAddr=0x00;
}


int main ()
{
	
	
	VICVectAddr0= (unsigned int)eint0;
	
	VICVectCntl0=0x0000002E;
	VICIntEnable=0X00004000;
	PINSEL0=0X0000000C;
	EXTINT&=~0X01;
	EXTMODE=0X00;

	IO0DIR=0X0000000C;
	IO0PIN=0X0000000C;

	while(1)
	IO0CLR = 0X04;
}


