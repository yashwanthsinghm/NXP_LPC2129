#include<LPC21XX.h>


// uart initialing
void delay(unsigned long int x);
void uart_init(void);
void uart_write(char c);
void uart_nextline(void);


   struct RTC_struct{
  int sec;
  int min;
  int hour;
  int dom;
  int dow;
  int doy;
  int month;
  int year;
    };

 //RTC initialization
void RTC_init(struct RTC_struct t);
void alarm_set(struct RTC_struct t);
//conversation
void conversion(int val);

//global variables
  int second=0,alarm=0;




__irq void RTC_ISR()
{
 if(ILR & 0X01==0X01)
    {     	   second=1;
	            ILR |=0X01;
	}

 else{
   alarm=1;
 ILR |= 0X02;
 }
	VICVectAddr =0X00;
}








// main function



int main()
{
int k;
struct RTC_struct timer={00,45,1,8,3,342,12,2020},alarm1={06,45,1,8,3,342,12,2020};
 IO0DIR =0X00000008;
 

 RTC_init(timer);
 alarm_set(alarm1);
 uart_init();
 VICIntSelect =	 0X00;//IRQ
 VICIntEnable =	 0X00002000;
 VICVectAddr0 =	(unsigned) RTC_ISR;
 VICVectCntl0 =	0X00000020|13;//13 for RTC 
 
 while(1)
 {
 if(alarm==1 )
 {   for(k=0;k<5;k++)
 {
 	IO0SET = 0X08;
	delay(0x1000000);
	IO0CLR = 0X08;
	delay(0x100000);
	}
	alarm=0;
 }
 else if(second==1)
 {
//int  val1 = SEC;
 conversion((int) DOM);
 uart_write('-');
 conversion((int) MONTH);
 uart_write('-');
 conversion((int) YEAR);
 uart_write(':');
 conversion((int) MIN);
 uart_write(':');
 conversion((int) SEC);



  uart_nextline();

 second =0;
 }
  
 }

}













//// function defination


void conversion(int val)
{
 char ascii[10]={'\0'};
 int digit,i=0,j;
 while(val>0)
 {
  digit = val%10;
  ascii[i] = digit+0x30;
  val =val/10;
  i++;
 }
 for(j=0;j<i;j++)
    uart_write(ascii[i-j-1]);
 
}




void alarm_set(struct RTC_struct t)
{

ALSEC = t.sec;         
ALMIN =  t.min; //masked no use       
ALHOUR = t.min;   //masked no use      
ALDOM = t.dom;    //masked no use      
ALDOW = t.dow;    //masked no use     
ALDOY = t.doy;   //masked no use       
ALMON = t.month;     //masked no use     
ALYEAR = t.year;	//masked no use 
}




void RTC_init(struct RTC_struct t)
{
ILR = 0X00;
CCR = 0x02;
AMR = 0xFE;
PREINT = 0x1C8; //PCLK/32768 -1
PREFRAC = 	0X61C0;//pclk-((preint)+1)*32768
SEC = t.sec;
MIN = 	t.min;
HOUR = 	t.hour;
DOM =  t.dom;
DOW = 	t.dow;
DOY = 	t.doy;
MONTH  = t.month;
YEAR = 	 t.year;
CCR = 0X01;
ILR = 0X03;
CIIR = 0X00000001;
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



