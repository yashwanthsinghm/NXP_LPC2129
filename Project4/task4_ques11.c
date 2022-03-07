#include<LPC21XX.h>
#include<string.h>

void timer0_delay(unsigned int x);
void delay(unsigned long int x);
void uart_write(char c);
char uart_read(void);
void uart_init(void);
void uart_nextline(void);



  int main()
  {		int i,j;
	   char a[11]=""; 
	   uart_init();
	   for(i=0;i<9;i++)
	   {
	   a[i]=uart_read();
	   }
	   a[9]='\0';
	   for(i=0;a[i]!='\0';i++)
	   uart_write(a[i]);
	   uart_nextline();
   for(i=0,j=8;j>i;i++,j--)
	   {
	   if(a[i]!=a[j])
	   {
	   a[i]=a[i]+a[j];
	   a[j]=a[i]-a[j];
	   a[i]=a[i]-a[j];
	   }
	   }  
	   a[9]='\0';
	   for(i=0;a[i]!='\0';i++)
	   uart_write(a[i]);




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
