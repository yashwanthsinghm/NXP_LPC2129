#include<LPC21XX.h>
int main()
{
  int i=0,j=0,k=0;
 IO0DIR = 0X00000001;
 T0TCR = 0x02;  //disable
 T0PR  = 0x0F; //divide by 15
 //T0MCR = 0x0C9;//  
 T0MCR = 0X03;      
 T0MR0 = 0xF4240;//1 second delay
 //T0MR1 = 0X1E8480;
 //T0MR2 = 0X2D0600;
  T0TCR = 0X01;

  while(1)
  {
  if(T0IR==0X01 && i<10)
  {	 
	IO0PIN = IO0PIN ^ 0X01;
	T0IR=0X01;
	i++;
  }
   if(T0IR==0X01 && j<8 && i==10)
  {	 if(j%2==0)
	  IO0PIN = IO0PIN ^ 0X01;
	T0IR=0X01;
	j++;
  }
    if(T0IR==0X01 && k<3 && j==8)
  {
	IO0PIN = 0X01;
	T0IR=0X01;
	k++;
  }
   if(k==3)
   IO0PIN =0X00;
  
  }



}
