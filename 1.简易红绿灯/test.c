#include<reg52.h>

#define uchar unsigned char
#define ulong unsigned long
#define uint unsigned int

sbit LED1 = P1^0;
sbit LED2 = P1^1;
sbit LED3 = P1^2;
sbit LED4 = P1^3;
sbit LED5 = P1^4;
sbit LED6 = P1^5;
sbit LED7 = P1^6;
sbit LED8 = P1^7;

void delay( long n )
{
	ulong i=0;
	for(i=0; i<n; i++);
}

void flicker3()
{
	uint i;
	for(i=0; i<3; i++)
	{
		LED3=1;
		delay(20000);
		LED3=0;
		delay(20000);
	}
}

void flicker6()
{
	uint i;
	for(i=0; i<3; i++)
	{
		LED6=1;
		delay(20000);
		LED6=0;
		delay(20000);
	}
}

void main()
{
	while(1)
	{
		LED8=0;		
		LED3=0;
		delay(150000);
		flicker3();
		LED3=1;
		LED4=0;
		delay(30000);
		LED4=1;
		LED8=1;
		LED6=0;
		LED5=0;
		delay(150000);
		flicker6();
		LED6=1;
		LED7=0;
		delay(30000);
		LED7=1;
		LED5=1;
		LED6=1;
	}
}
