#include <reg52.h>

#define uint unsigned int
#define uchar unsigned char

void delay(int n);

sbit D0 = P1^0;
sbit D1 = P1^1;
sbit D2 = P1^2;
sbit D3 = P1^3;
sbit D4 = P1^4;
sbit D5 = P1^5;
sbit D6 = P1^6;
sbit D7 = P1^7;

void main()
{
	uchar i=0;
	while(1)
	{
		if(P3^3 == 1)
			P1=0xFF;
		else
			P1=0x00;
	}
}

void delay(int n)
 {
 	int i;
 	for (i = 0; i < n; i++);
 }