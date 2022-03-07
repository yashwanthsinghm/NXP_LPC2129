#include<LPC21XX.h>
int main(){

IO0DIR = 0X000000FF;
while(1){


if(IO0PIN&0X100)
IO0PIN=0X00;
else
IO0PIN=0XFF;  
}
}
