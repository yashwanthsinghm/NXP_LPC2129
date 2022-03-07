 #include<LPC21XX.h>
void delay(unsigned long int x){
unsigned long  int i,j;
for(i=0;i<x;i++)
{
for(j=0;j<x;j++);
}

}
int main(){
int flag=0x02,temp=0x1E;
IO0DIR = 0X0000001E;
while(1){
if(!(IO0PIN&0X01))
{  
//IO0PIN=0X00; 
IO0PIN=~(flag);
temp=~(flag);
flag=flag<<1;
//flag=flag+0x02;	
delay(3000);	  
}
else
IO0PIN=temp;

}
 
}