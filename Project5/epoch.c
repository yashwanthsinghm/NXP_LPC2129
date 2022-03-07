#include <stdio.h>
#include <time.h>
#include<lpc21xx.h>


void uart_print(char *str);
char uart_read(void);
void uart_init(void);
void uart_nextline(void);
void uart_write(char c);
		char buf[100];
int main(void) {
    struct tm t;
	int sec,min,hour,day,mon,year;
	int Temp1=0,Temp2=0,Temp3=0,Temp4=0,Temp5=0,Temp6=0;
    time_t t_of_day;
	 uart_init();
    t.tm_year = 2019-1900;  // Year - 1900
    t.tm_mon = 7;           // Month, where 0 = jan
    t.tm_mday = 8;          // Day of the month
    t.tm_hour = 16;
    t.tm_min = 11;
    t.tm_sec = 42;
    t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day = mktime(&t);


		
    sprintf(buf,"seconds since the Epoch: %ld\n ", (long) t_of_day);
	uart_print(buf);
 	
	//	t_of_day = 1607520013; // 2020-12-9 13:20:13
	
	// new
	  sec = t_of_day% 60;
	  t_of_day = t_of_day/60;
	  min = t_of_day% 60;
	  t_of_day = t_of_day /60;
	  hour = t_of_day%24;
	  t_of_day = t_of_day/24;


	     Temp1 = (int) ((4 * t_of_day + 102032) / 146097 + 15);
    Temp2 = (unsigned int) (t_of_day + 2442113 + Temp1 - (Temp1 / 4));
    Temp3 = (20 * Temp2 - 2442) / 7305;
    Temp4 = Temp2 - 365 * Temp3 - (Temp3 / 4);
    Temp5 = Temp4 * 1000 / 30601;
    Temp6 = Temp4 - Temp5 * 30 - Temp5 * 601 / 1000;

    //January and February are counted as months 13 and 14 of the previous year
    if(Temp5 <= 13)
    {
       Temp3 =Temp3-4716;
       Temp5 =Temp5-1;
    }
    else
    {
       Temp3 =Temp3-4715;
       Temp5 =Temp5-13;
    }

    //Retrieve year, month and day
    year = Temp3%100 +2000;
    mon = Temp5;
    day = Temp6;
   
   
       sprintf(buf," sec = %d min =%d hour = %d month = %d day = %d year = %d ",sec,min,hour,mon,day,year);
	uart_print(buf);	  
	
	
	
	// 
	while(1);
}


void uart_print(char *str)
{

 int i;
 for(i=0;str[i]!='\0';i++)
 uart_write(str[i]);
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




  void uart_write(char c)
 {
 U0THR =c;
while((U0LSR&0x40)==0)
{}

 }
