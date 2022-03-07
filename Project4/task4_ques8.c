#include<LPC21XX.h>
#include<string.h>

void timer0_delay(unsigned int x);
void delay(unsigned long int x);
void uart_write(char c);
char uart_read(void);
void uart_init(void);
void uart_nextline(void);



  int main()
  {		
	   char d=0;
	   uart_init();
      while(1)
	  { int i=0,j=0,digit;	
	   char arr[3]={'\0'};
	   char temp1,temp2;
	     d=uart_read();
	     temp1 =  ((0x0F&d)>0x09) ? (0x0F&d|0x40)-0x09 : 0x0F&d|0x30;
		 temp2 = ((0x0F&(d>>4))>0x09) ? (0x0F&(d>>4)|0x40)-0x09 : 0x0F&(d>>4)|0x30;	
		 uart_write(' ');
		 uart_write(temp2);
		 uart_write(temp1);
		 uart_write(' ');
          while(d>0)
		  {	 
		     digit =d%10;
			 arr[i]=digit+'0';
			 d = d/10;
			 i++;
		  }
		  for(j=i-1;j>=0;j--)
		  uart_write(arr[j]);

	   	uart_nextline();
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



char uart_read(void)
{
char c;
while((U0LSR&0X01)==0);
c=U0RBR;
U0THR =c;
while((U0LSR&0x40)==0);
return c;
}


 void delay(unsigned long int x){
unsigned long int i;
for(i=0;i<x;i++);
}



void uart_init(void)
{	   PINSEL0 = 0x00000005;  //0101
	   U0LCR = 0X83;//8 for enabling 3 for 8 bit data
	   U0DLM = 0X00;// 
	   U0DLL = 0X061;// decimal value= 97.5 for 9600 baud rate 
	   U0LCR = 0X03;  // disable for 8bit
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
