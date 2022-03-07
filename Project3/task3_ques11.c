#include<LPC21XX.h>
#define RS 0X01000000
#define RW 0X02
#define EN 0X02000000



void delay(unsigned long int x);
void lcdwrt(unsigned char y);
void timer0_delay(unsigned int x);
void convert_print(int x);

unsigned char cmd[5]={0x38,0x0E,0x06,0x01,0x80};

int main()
{
int i;
IO0DIR =0X000000FF;
IO1DIR =0X43000000;
IO1CLR=RS;
for(i=0;i<5;i++)
lcdwrt(cmd[i]);
IO1SET=RS;
 while(1)
 {
if(!((IO0PIN>>8 & 0X01)))
         {
		 for(i=0;i<60;i++)	
         convert_print(i);
          timer0_delay(1);
         }
if(!((IO0PIN>>9 & 0X01)))
         {for(i=59;i>0;i--)	
         convert_print(i);
          timer0_delay(1);
         }
if(!((IO0PIN>>10 & 0X01)))
         {
		 convert_print(0);
          timer0_delay(1);
         }
if(!((IO0PIN>>11 & 0X01)))
         {
		 for(i=0;i<60;i++)	
         convert_print(i);
          timer0_delay(1);
         }
		 }
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





void convert_print(int x)
{

int flag=0,sum=0,num,digit;
if(x%10==0)
flag=2;
if(x==0)
flag=1;
num =x;
 sum=0;
while(num>0){
digit =num%10;
sum = sum*10+digit;
num = num/10;
}
num=sum; 
while(num>0 || flag==1){
digit =num%10;
 lcdwrt(48+digit);
num = num/10;
 if(num==0)
 flag--;
}
timer0_delay(1);
IO1CLR=RS;
lcdwrt(0x01);
IO1SET=RS;
}
