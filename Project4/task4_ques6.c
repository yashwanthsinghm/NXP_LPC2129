#include<LPC21XX.h>
#include<string.h>

void timer0_delay(unsigned int x);
void delay(unsigned long int x);
void uart_init(void);
void uart_write(char c);
char uart_read(void);
void uart_init(void);
void uart_nextline(void);

unsigned char msg[]="welcome yashwanth";
unsigned char msg1[]="wrong password reenter";
 int i,flag=1,j;	

int main()
{
 
char pass1[11]="";
char pass2[11]="";
IO0DIR =0X00000200;
uart_init();
IO0CLR = 0X200;
while(1)
{

if(flag==1){
          flag=0;
       for(i=0;i<10;i++)
           pass1[i]=uart_read();
       uart_nextline();
       pass1[10]='\0';
       j=0;
       while(j<3)
          {
           for(i=0;i<10;i++)
           pass2[i]=uart_read();
           pass2[10]='\0';
           uart_nextline();
           if(!(strcmp(pass1,pass2)))
             {
              for(i=0;msg[i]!=0;i++)
              uart_write(msg[i]);
              break;
             }
         else
            {
            for(i=0;msg1[i]!=0;i++)
                uart_write(msg1[i]);
            j++;
            uart_nextline();
			if(j==3)
			  IO0CLR = 0X200;
			else
			   IO0SET = 0X200; 
            }

           }
        		
}

else 
{
    if(!((IO0PIN>>8 & 0X01)))
        {
         flag=1;
         timer0_delay(1);
        }

}
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