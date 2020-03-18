#include <reg52.h>  

sbit start = P0^1;
sbit receive = P3^2;
bit F20us = 0;
unsigned int cnt = 0;
unsigned char cm = 0;

void send();
void delayms(unsigned int ms);
void ConfigT0();
void ConfigUART(unsigned int baud);

void main()
{
    EA = 1;
    ConfigT0();
    ConfigUART(9600);
    while(1)
    {
        send();
        while(receive == 0);
        TR0 = 1;
        while(receive == 1);
		TR0 = 0;
        cm = cnt/58;
        SBUF = cm;
        delayms(1000);
    }
}

void ConfigUART(unsigned int baud)
{
    SCON  = 0x50;
    TMOD &= 0x0F;
    TMOD |= 0x20;
    TH1 = 256 - (11059200/12/32)/baud;
    TL1 = TH1;
    ET1 = 0;
    ES  = 1;
    TR1 = 1;
}

void ConfigT0()
{
    TMOD &= 0xF0;
    TMOD |= 0x02;
    TH1 = 0xFF;
    TL1 = 0xFF;
    ET0 = 1;
}

void send()
{
    start = 0;
    F20us = 0;
    start = 1;
    TR0 = 1;
    while(F20us==0);
    F20us = 0;
    TR0 = 0;
    cnt = 0;
    start = 0;
}

void interruptT0() interrupt 1
{
    cnt++;
    if (cnt>=20)
    {
        F20us = 1;
    }
    if (cnt>=30000)
    {
        TR0 = 0;
    }

}

void delayms(unsigned int ms)
{
    unsigned char i=100,j;
    for(;ms;ms--)
    {
        while(--i)
        {
            j=10;
            while(--j);
        }
    }
}

void InterruptUART() interrupt 4
{
	if(RI)
	{
		RI = 0;
	}
	if(TI)
	{
		TI = 0;
	}
}