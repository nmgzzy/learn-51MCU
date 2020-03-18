#include <reg52.h>

sbit out = P0^1;

unsigned int rad = 0;
unsigned char T0RH = 0;  //T0����ֵ�ĸ��ֽ�
unsigned char T0RL = 0;  //T0����ֵ�ĵ��ֽ�
bit flag1s = 0;

void ConfigTimer0();
void ConfigUART(unsigned int baud);
void action1s();
unsigned char keysta = 1;

void main()
{
	bit keybk=1;
	EA = 1;   //ʹ�����ж�
    ConfigTimer0();   //����T0��ʱ1ms
    ConfigUART(9600);  //���ò�����Ϊ9600
	while(1)
	{
		if(flag1s)
		{
			action1s();
		}
		if(keysta != keybk)
		{
			if(keybk == 0)
			{
				rad++;
			}
			keybk=keysta;
		}	
	}
}

void action1s()
{
	flag1s = 0;
	SBUF = rad;
	rad = 0;
}

void ConfigTimer0()
{
    T0RH = 0xFE;
    T0RL = 0x8F;
    TMOD &= 0xF0;   //����T0�Ŀ���λ
    TMOD |= 0x01;   //����T0Ϊģʽ1
    TH0 = T0RH;     //����T0����ֵ
    TL0 = T0RL;
    ET0 = 1;        //ʹ��T0�ж�
    TR0 = 1;        //����T0
}

void ConfigUART(unsigned int baud)
{
    SCON  = 0x50;  //���ô���Ϊģʽ1
    TMOD &= 0x0F;  //����T1�Ŀ���λ
    TMOD |= 0x20;  //����T1Ϊģʽ2
    TH1 = 256 - (11059200/12/32)/baud;  //����T1����ֵ
    TL1 = TH1;     //��ֵ��������ֵ
    ET1 = 0;       //��ֹT1�ж�
    ES  = 1;       //ʹ�ܴ����ж�
    TR1 = 1;       //����T1
}

void InterruptTimer0() interrupt 1
{
	static unsigned int cnt=0;
	static unsigned char keybf = 0xff;
    TH0 = T0RH;  //���¼�������ֵ
    TL0 = T0RL;
    keybf = (keybf<<1)|out;
	if(keybf == 0x00)
	{
		keysta = 0;
	}
	else if(keybf == 0xff)
	{
		keysta = 1;
	}
	cnt++;
	if(cnt>=2500) 
	{
		cnt=0;
		flag1s=1;
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