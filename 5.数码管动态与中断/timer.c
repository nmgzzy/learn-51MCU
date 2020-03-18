#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

code unsigned char digseg[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
                         //     0    1    2    3    4    5    6    7    8    9  
code unsigned char segsel[4]={0xfe,0xfd,0xfb,0xf7};
                        //ÊýÂë¹Ü¶ÎÑ¡ 
unsigned char LedBuff[4]={0xFF, 0xFF, 0xFF, 0xFF};
sbit CE573=P2^5;
unsigned char flag1s = 0;

void main()
{
	unsigned long sec = 0;
	TMOD = 0x01;
	TH0 = 0xFC;
	TL0 = 0x66;
	TR0 = 1;
	EA = 1;
	ET0 = 1;
	while(1)
	{	
		if(flag1s == 1)		  
		{
			flag1s = 0;
			sec++;
			if(sec/10==0)
			{
				LedBuff[0] = digseg[sec%10];
				LedBuff[1] = 0xff;
				LedBuff[2] = 0xff;
				LedBuff[3] = 0xff;
			}
			else if(sec/100==0)
			{
				LedBuff[0] = digseg[sec%10];
				LedBuff[1] = digseg[sec/10%10];
				LedBuff[2] = 0xff;
				LedBuff[3] = 0xff;
			}
			else if(sec/100==0)
			{
				LedBuff[0] = digseg[sec%10];
				LedBuff[1] = digseg[sec/10%10];
				LedBuff[2] = digseg[sec/100%10];
				LedBuff[3] = 0xff;
			}
			else
			{
				LedBuff[0] = digseg[sec%10];
				LedBuff[1] = digseg[sec/10%10];
				LedBuff[2] = digseg[sec/100%10];
				LedBuff[3] = digseg[sec/1000%10];
			}
		}			
	}
}

void InterruptTime0() interrupt 1		
{
	 static uchar i = 0;
	 static uint cnt = 0;
	 TH0 = 0xFC;
	 TL0 = 0x66;
	 cnt++;
	 if(cnt >= 1000)
	 {
	 	cnt = 0;
		flag1s = 1;
	 }
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