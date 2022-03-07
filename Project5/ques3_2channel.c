	 #include<LPC21XX.h>

void delay(unsigned long int x);
void uart_init(void);
void uart_write(char c);
char uart_read(void);
void uart_init(void);
void uart_nextline(void);
void adc_printer(void);



 int val;
   char arr[4];
int main()
{  

uart_init();
  PINSEL1 = 0X01400000;	 //p0.28 is adc1
  IO0DIR = 0X000000FF;
 //ADCR = 0X00210702;
   //3 for adc 0 and adc 1 p0.27,p0.28
  while(1)
  {
		 ADCR = 0X00210202;
	  	adc_printer();
		ADCR = 0X00210201;
		adc_printer();
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


  void adc_printer()
  {
	int val,i,digit;
      if(ADDR&0X80000000)
   val = ADDR;
   val=val>>6;
   val=val&0x3FF;
   for(i=0;i<4;i++)
   {  digit=0;
   digit = val%10;
   arr[3-i]=0x30+digit;
   val=val/10;
   }
   for(i=0;i<4;i++)
	  uart_write(arr[i]); 
	uart_nextline();
	  	uart_nextline();
	delay(500);//00000);
  }