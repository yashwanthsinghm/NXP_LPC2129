 #include<LPC21XX.h>
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
int main()
{
 IO0DIR = 0X0000003C;
 IO0PIN = 0X3C;
 while(1)
 {
  if(!(IO0PIN&0X01))
  {
    IO0PIN=~(0X04);
	timer0_delay(1);//1 second delay
  }
  if(!((IO0PIN&0X01)&&(IO0PIN&0X02)))
  {
  IO0PIN =~(0X08);
  timer0_delay(1);
  }
  if(!(IO0PIN&0X02))
  {
  IO0PIN =~(0X10);
  timer0_delay(1);
  }

 }
}