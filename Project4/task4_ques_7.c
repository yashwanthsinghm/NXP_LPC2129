#include<LPC21XX.h>
#include<string.h>

void timer0_delay(unsigned int x);
void delay(unsigned long int x);
void uart_write(char c);
char uart_read(void);
void uart_init(void);
void uart_nextline(void);

int main()
{   int i,temp,digit;
char res[3];
int num1=0,num2=0,sign,result;
uart_init();
while(1)
{
num1=0;num2=0;result=0;sign=0;
res[0]='\0';
res[1]='\0';
res[2]='\0';
for(i=0;i<3;i++)
{
 temp = uart_read();
 digit = temp - 48;
 num1 =num1*10+digit;
 }
 sign = uart_read();
for(i=0;i<3;i++)
{
 temp = uart_read();
 digit = temp - 48;
 num2 =num2*10+digit;
 }
   switch(sign)
   {
     case '+' : result = num1+num2;
	          break;
	 case '-' :	result = num1-num2;
	          break;
	case '*' : result = num1 * num2;
	          break;
    case '/' : result = num1 / num2;
	          break;
	default : break;
   }
   if(uart_read() == '=')
   {
   uart_nextline();
	i=2;
   while(result>0)
   {
   digit = result%10;
  res[i]= digit+'0';
   result = result/10;
   i--;
   }
   for(i=0;i<3;i++)
   uart_write(res[i]);
   }
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
