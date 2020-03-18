#include <reg52.h>
#define uchar unsigned char

void main()
{
	uchar cnt=0;
	uchar ct=0;
	TMOD = 0x01;
	TH0 = 0xB8;
	TL0 = 0x00;
	TR0=1;
	while(1)
	{
		if(TF0 == 1)
		{
			TF0 = 0;
			TH0 = 0xB8;
			TL0 = 0x00;
			ct++;
			if(ct==50)
			{
				P1=~(0x01<<cnt);
				cnt++;
				if(cnt>=8)
				{
					cnt=0;
				}
				ct=0;
			}
		}
	}
}

