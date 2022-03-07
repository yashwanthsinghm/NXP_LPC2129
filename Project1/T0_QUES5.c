#include<LPC21XX.h>
 int main()
 {
   int i=0;
   IO0DIR = 0X00000003;
   T0TCR  = 0X02;
    T0PR  = 0x0F;
   T0MCR  = 0X03;
  
   T0MR0  = 0XF4240;
   T0TCR  = 0X00000001;
   IO0PIN = 0X00000001;
   while(1)
   { 
     while(i<10)
	 { 
    if(T0IR==0X01)
	{
	 
	 IO0PIN = IO0PIN ^ 0X00000003;
	 T0IR = 0X01;
	 i++;
	}

	}
		if(i==10)
	{
	    IO0PIN = 0X00000003;
	    break;
	}
   }

 }
