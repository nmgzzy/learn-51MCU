#include <reg52.h>
#define uchar unsigned char

code unsigned char digseg[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
                         //   0    1    2    3    4    5    6    7    8    9    A    b    C    d    E    F
code unsigned char segsel[]={0xfe,0xfd,0xfb,0xf7};
                        //สýย๋นÜถฮัก 

sbit CE573=P2^5;
void delay(int n)
{
	int i;
	for(i=0; i<n; i++);
}
void main()
{
	int i,j;	
	while(1)
	{
		CE573=1;
		for(i=0; i<16; i++)
		{
			for(j=0; j<4; j++)
			{
				P2=segsel[j];
				P0=digseg[i];
				delay(1000);
			}
			delay(40000);
		}
	}
}

