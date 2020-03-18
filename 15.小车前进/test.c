#include<reg52.h>  

sbit LeftF=P1^0;  //左轮前进 //
sbit LeftB=P1^1;  //左轮后退 //
				  //0为真	 //
sbit RightF=P1^2; //右轮前进 //
sbit RightB=P1^3; //右轮后退 //

void run(void)
{
    LeftF=0;
	LeftB=1;
	RightF=0;
	RightB=1;
}

void main(void)
{
	run();	  
	while(1);  
}