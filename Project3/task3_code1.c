#include<LPC21XX.h>
 void timer0_delay(unsigned int x);
int main()
{
IO0DIR =0X00000001;
while(1)
{
IO0PIN = IO0PIN^0X01;
timer0_delay(0.5);
}

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