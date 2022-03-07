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
int data=0x00;
IO0DIR = 0X0000001E;
IO0PIN = 0X1E;
 while(1)
 {
  if(!(IO0PIN & 0X01))
  {		//curr=data<<1;
	  IO0PIN = ~data;
	  data=data+0x02;
	  timer0_delay(1);

  }
 }

}
