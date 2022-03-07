#include<LPC21XX.h>
#include<string.h>
#define RS 0X01000000
#define RW 0X02
#define EN 0X02000000

void timer0_delay(unsigned int x);
void delay(unsigned long int x);
void uart_write(char c);
char uart_read(void);
void uart_init(void);
void uart_nextline(void);
void delay(unsigned long int x);
void lcdwrt(unsigned char y);

unsigned char cmd[5]={0x38,0x0E,0x06,0x01,0x80};

 unsigned char k;
 int temp;

__irq void isr_handler(void)
{ 
//while((U1IIR&0x01));

    if((U1IIR&0x04)==0x04)
       k = U1RBR;
	   U1IIR=0X04;
	   temp=1;
       U1THR = k;
       while(U1LSR!=0X40);	
	   U1IER = 0x01;
VICVectAddr = 0x00;	 

}




int main()
{	 int i;
IO0DIR =0X000000FF;
IO1DIR =0X03000000;
IO1CLR=RS;
for(i=0;i<5;i++)
lcdwrt(cmd[i]);
IO1SET=RS;
	 uart_init();
   VICVectAddr0 = (unsigned int)isr_handler;	
	VICVectCntl0 = 0x00000027;		//7th bit for uart 1 and 2 for enabling
	VICIntEnable = 0x00000080;	  // to enable the uart1 interrupt	 
	//VICIntSelect = 0x00000000;	  //   selecting uart1 interrupt as irq default its irq	
	U1IER=0X01;   
	 while(1)
	 {
	 if(temp==1) {
	 uart_write(k);
	 lcdwrt(k);
	 temp=0;  
	 }
	 }

}


void uart_write(char c)
 {
 U1THR =c;
while((U1LSR&0x40)==0)
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
while((U1LSR&0X01)==0);
c=U1RBR;
U1THR =c;
while((U1LSR&0x40)==0);
return c;
}


 void delay(unsigned long int x){
unsigned long int i;
for(i=0;i<x;i++);
}



void uart_init(void)
{	   PINSEL0 = 0x00050000;  //0101
	   U1LCR = 0X83;//8 for enabling 3 for 8 bit data
	   U1DLM = 0X00;// 
	   U1DLL = 0X061;// decimal value= 97.5 for 9600 baud rate 
	   U1LCR = 0X03;  // disable for 8bit
	  // U1IER = 0x00000001;
}

void lcdwrt(unsigned char y)
{
IO0PIN=y;
IO1SET=EN;
delay(0x5000);
IO1CLR=EN;
delay(0x5000);
}		 

