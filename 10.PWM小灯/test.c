#include <reg52.h>
#define uchar unsigned char

sbit PWMout = P1^7;

uchar HighRH = 0;
uchar HighRL = 0;
uchar LowRH = 0;
uchar LowRL = 0;

void CfgPWM(unsigned int fr, uchar dc);
void ClsPWM();

void main()
{
    unsigned int i;    
    EA = 1;
	while(1)
	{
		CfgPWM(100, 5);
        for (i=0; i<40000; i++);
        ClsPWM();
        CfgPWM(100, 15);
        for (i=0; i<40000; i++);
        ClsPWM();
        CfgPWM(100, 25);
        for (i=0; i<40000; i++);
        ClsPWM();
        CfgPWM(100, 35);
        for (i=0; i<40000; i++);
        ClsPWM();
        CfgPWM(100, 45);
        for (i=0; i<40000; i++);
        ClsPWM();
        CfgPWM(100,55);
        for (i=0; i<40000; i++);
        ClsPWM();
        CfgPWM(100, 65);
        for (i=0; i<40000; i++);
        ClsPWM();
        for (i=0; i<40000; i++);
	}
}

void CfgPWM(unsigned int fr, uchar dc)
{
	unsigned long tmp;
	unsigned int high,low;
	tmp = 11059200/12/fr;
	high = (tmp*dc)/100;
	low = tmp - high;
	high = 65536 - high + 12;
	low = 65536 - low + 12;
	HighRH = (uchar)(high >> 8);
	HighRL = (uchar)high;
	LowRH = (uchar)(low >> 8);
	LowRL = (uchar)low;
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TH0 = HighRH;
	TL0 = HighRL;
	ET0 = 1;
	TR0 = 1;
	PWMout = 1;	
}

void ClsPWM()
{
	TR0 = 0;
	ET0 = 0;
	PWMout = 1;
}

void InterruptTimer0() interrupt 1
{
	if(PWMout == 1)
	{
		TH0 = LowRH;
		TL0 = LowRL;
		PWMout = 0;
	}
	else
	{
		TH0 = HighRH;
		TL0 = HighRL;
		PWMout = 1;
	}
}