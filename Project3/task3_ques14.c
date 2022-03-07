#include<LPC21XX.h>
#include<string.h>
#define RS 0X01000000
#define RW 0X02
#define EN 0X02000000
void delay(unsigned long int x);
void lcdwrt(unsigned char y);
void timer0_delay(unsigned int x);

unsigned char cmd[5]={0x38,0x0E,0x06,0x01,0x80};
unsigned char msg1[]="itriangle Bangalore                ";
//unsigned char msg2[]="itriangle";

int main()
{
int i,j,len;
for(len = 0;msg1[len]!='\0';len++);
IO0DIR =0X000000FF;
IO1DIR =0X43000000;
IO1CLR=RS;
for(i=0;i<5;i++)
lcdwrt(cmd[i]);
IO1SET=RS;


 while(1)
 {
for(i=0;i<len;i++)
{
int space,upper,lower; 
if(i<15){
space = 15-i;
lower=0;
}
else
{
space=0;
lower=i-15;
}
upper = 15-space+i+1;
IO1CLR=RS;
lcdwrt(0xc0+space);
IO1SET=RS;
 for(j=lower;j<upper;j++)
 lcdwrt(msg1[j]);
timer0_delay(1);
}
}
delay(5000000);
IO1CLR=RS;
lcdwrt(0x01);
IO1SET=RS;


return 0;
}
void lcdwrt(unsigned char y)
{
IO0PIN=y;
IO1SET=EN;
delay(0x5000);
IO1CLR=EN;
delay(0x5000);
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
void delay(unsigned long int x){
unsigned long int i;
for(i=0;i<x;i++);
}
