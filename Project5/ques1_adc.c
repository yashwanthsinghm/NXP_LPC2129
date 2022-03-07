#include<LPC21XX.h>
#include<stdio.h>

#define RS 0X01000000
#define RW 0X02
#define EN 0X0200

void lcdwrt(unsigned char y);
void delay(unsigned long int x);

void uart_init(void);
void uart_write(char c);
char uart_read(void);
void uart_init(void);
void uart_nextline(void);

void conversion(int val);


unsigned char cmd[5]={0x38,0x0E,0x06,0x01,0x80};
unsigned char msg1[]="YASHWANTH SINGH";

int main()
{  
//int i,digit;
int val1=0,i,k;
float val2;
unsigned char str[20]={'\0'};
uart_init();
  PINSEL1 = 0X01000000;	 //p0.28 is adc1
  //IO0DIR = 0X000000FF;
 //ADCR = 0X00210702;
  ADCR = 0X00210202;
 //lcd 

  IO0DIR =0X0000003FC;
IO1DIR =0X03000000;
IO1CLR=RS;
for(i=0;i<5;i++)
lcdwrt(cmd[i]);
IO1SET=RS;
IO1CLR=RS;
lcdwrt(0X01);
IO1SET=RS;
for(i=0;msg1[i]!='\0';i++)
lcdwrt(msg1[i]);
return 0;
///lcd

  while(1)
  {
  if(ADDR&0X80000000)
   val1 = ADDR;
  val1=val1>>6;
  val1=val1&0x3FF;
   val2 = (float)(val1)*0.0032258;
  sprintf(str,"voltage is %.2f",val2);
  for(k=0;str[k]!='\0';k++)
		{
		uart_write(str[k]);
		lcdwrt(str[k]);
		}
  //conversion(val1);
  uart_nextline();
  delay(100000);	
		 }
   
}



 void conversion(int val)
{
 unsigned char ascii[10]={'\0'};
 int digit,i=0,j;
 while(val>0)
 {
  digit = val%10;
  ascii[i] = digit+0x30;
  val =val/10;
  i++;
 }
 for(j=0;j<i;j++){
    uart_write(ascii[i-j-1]);
//	lcdwrt('a');
	}
 
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








void uart_init(void)
{	   PINSEL0 = 0x00000005;  //0101
	   U0LCR = 0X83;//8 for enabling 3 for 8 bit data
	   U0DLM = 0X00;// 
	   U0DLL = 0X061;// decimal value= 97.5 for 9600 baud rate 
	   U0LCR = 0X03;  // disable for 8bit
}


void lcdwrt(unsigned char y)
{
unsigned int x =y;
x=x<<2&0x3FC;
IO0PIN=x;
IO1SET=EN;
delay(0x5000);
IO1CLR=EN;
delay(0x5000);
}

void delay(unsigned long int x){
unsigned long int i;
for(i=0;i<x;i++);
}

