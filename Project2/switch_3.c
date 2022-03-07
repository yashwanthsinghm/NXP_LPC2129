 #include<LPC21XX.h>
 void timer0_delay(unsigned int x){   
 T0TCR = 0x02;  
 T0PR  =0x0F;
 T0MCR =0x07; //       
 T0MR0 = 0xF4240*x;
 T0TCR = 0X01;
}

int main()
{
int j=0;
IO0DIR = 0X00000002;
IO0PIN = 0X02;
while(1)
{
if(!(IO0PIN&0X01))
{
   j++;
   if(j==4)
   break;
  IO0PIN = ~(0X02);
  timer0_delay(j);
  while(T0IR!=0x01)
  {}
  T0IR=0X01;
  IO0PIN = 0X02;

}
}

}
