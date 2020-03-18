#include <reg52.h>

sbit key1 = P3^2;
sbit key2 = P3^3;
sbit key3 = P3^4;
sbit key4 = P3^5;
sbit led1 = P1^0;
sbit led2 = P1^1;
sbit led3 = P1^2;
sbit led4 = P1^3;
sbit CE573= P2^5;
code unsigned char digseg[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
                         //   0    1    2    3    4    5    6    7    8    9 
code unsigned char segsel[]={0xfe,0xfd,0xfb,0xf7};
                        //ÊýÂë¹Ü¶ÎÑ¡ 
unsigned char LedBuff[4]={0xFF, 0xFF, 0xFF, 0xFF};
unsigned char cnt=0;
unsigned char keysta=1;

void main()
{
	bit keybk=1;
	unsigned char buff[4];
	char j;
	TMOD = 0x01;
	TH0 = 0xF8;
	TL0 = 0xCD;
	TR0 = 1;
	EA = 1;
	ET0 = 1;
	CE573=1;
	LedBuff[0] = digseg[0];
	while(1)
	{
		if(keysta != keybk)
		{
			if(keybk == 0)
			{
				cnt++;
				buff[0] = cnt%10;
				buff[1] = cnt/10%10;
				buff[2] = cnt/100%10;
				buff[3] = cnt/1000%10;
				for(j=3; j>=1; j--)
				{
					if(buff[j]==0)
					{
						LedBuff[j]=0xff;
					}
					else
					{
						break;
					}
				}
				for( ; j>=0; j--)
				{
					LedBuff[j]=	digseg[buff[j]];
				}
			}
			keybk=keysta;
		}	
	}
}

void InterruptTime0() interrupt 1		
{
	static unsigned char i = 0;
	static unsigned char keybf = 0xff;
	TH0 = 0xF8;
	TL0 = 0xCD;
	keybf=(keybf<<1)|key1;
	if(keybf == 0x00)
	{
		keysta = 0;
	}
	else if(keybf == 0xff)
	{
		keysta = 1;
	}
	else
	{}
	P0 = 0xFF;
    switch(i)
	{
		case 0: P2=segsel[3]; P0=LedBuff[0]; i++;break;
		case 1: P2=segsel[2]; P0=LedBuff[1]; i++;break;
	 	case 2: P2=segsel[1]; P0=LedBuff[2]; i++;break;
		case 3: P2=segsel[0]; P0=LedBuff[3]; i=0;break;
		default:break;
	}
}