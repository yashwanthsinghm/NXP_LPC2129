#include<lpc21xx.h>
#define RS 0X01000000;
#define EN 0X02000000;
int i=0,c=0;
unsigned int cmd[]={0X38,0X0F,0X06,0X01,0X80};

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

void lcdwrite (int x)
{
	IO0PIN=x<<8;
		IO1SET=EN;
		delay(500);
		
		IO1CLR=EN;
		delay(500);
}
void uart0_init()
{
	PINSEL0 = 0X00000005;
	//VICIntEnable= 1<<5;
	IO0DIR=0X00;
	U0LCR = 0X83;
	U0DLL = 0X61;
	U0DLM = 0X00;
	U0LCR = 0X03;
}
__irq void U0ISR(void)
{
	U0IIR=0X04;
	c=U0RBR;
	i=1;
	U0IER=0X01;
	VICVectAddr=0x00;
}
void uart0_write(int x)
{
		U0THR = x ;
		while(U0LSR&0X40);
	
}


int main ()
{
	
	uart0_init();
	VICVectAddr0= (unsigned int)U0ISR;
	VICIntEnable=0X00000040;
	VICVectCntl0=0x00000026;
	U0IER=0x01;
	
	IO0DIR=0X0000ff00;
	IO1DIR=0X03000000;
	IO1CLR=RS;
	for(i=0;i<5;i++)
	lcdwrite(cmd[i]);
	IO1SET=RS;
	
	while(1)
	{
			if(i==1)
			{
				//uart0_write(c);
				lcdwrite(c);
				i=0;
			}
	}
}


