#include<LPC21XX.h>
#define RS 0X01000000
#define RW 0X02
#define EN 0X02000000
void delay(unsigned long int x);
void lcdwrt(unsigned char y);

unsigned char cmd[5]={0x38,0x0E,0x06,0x01,0x80};
unsigned char msg1[]="hello yashwanth";

int main()
{
int i;
IO0DIR =0X000000FF;
IO1DIR =0X03000000;
IO1CLR=RS;
for(i=0;i<5;i++)
lcdwrt(cmd[i]);
IO1SET=RS;
for(i=0;msg1[i]!='\0';i++)
lcdwrt(msg1[i]);
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

void delay(unsigned long int x){
unsigned long int i;
for(i=0;i<x;i++);
}