#include<reg52.h>  

sbit LeftF=P1^0;  //����ǰ�� //
sbit LeftB=P1^1;  //���ֺ��� //
				  //0Ϊ��	 //
sbit RightF=P1^2; //����ǰ�� //
sbit RightB=P1^3; //���ֺ��� //

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