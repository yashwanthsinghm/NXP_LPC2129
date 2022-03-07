#include<LPC21xx.h>
#pragma pack(push,1)
typedef struct ss
{
 int v1;
 char v2;
}ST1;
#pragma pack(pop)
typedef struct ss1
{
 //char vv1;
 int vv2;
 char vv2;
}ST2;
int main()
{
	 ST1 s1;
	 ST2 s2;
	 s1.v1=10;
	 s2.vv1=10;
}
