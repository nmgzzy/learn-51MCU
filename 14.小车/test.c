#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit lf = P1^0; //cheng
sbit lb = P1^1; //huang
sbit rf = P1^2; //zong
sbit rb = P1^3; //hong
uchar *PWMout0;
uchar *PWMout1;
uchar LHighRH = 0;
uchar LHighRL = 0;
uchar LLowRH = 0;
uchar LLowRL = 0;
uchar RHighRH = 0;
uchar RHighRL = 0;
uchar RLowRH = 0;
uchar RLowRL = 0;

void CfgLeftPWM(uint fr, uchar dc);
void ClsPWM();
void stop();
void fd_f();
void fd_s();
void left();
void right();
void left_fd();
void right_fd();
void back_f();
void back_s();
void left_bk();
void right_bk();

void main()
{
	EA = 1;
	while(1)
	{
		//switch()
		//case
	}
}

void InterruptTime0() interrupt 1		
{
	if(*PWMout0 == 1)
	{
		TH0 = LLowRH;
		TL0 = LLowRL;
		*PWMout0 = 0;
	}
	else
	{
		TH0 = LHighRH;
		TL0 = LHighRL;
		*PWMout0 = 1;
	}	 
}

void InterruptTime1() interrupt 3		
{
	if(*PWMout1 == 1)
	{
		TH1 = RLowRH;
		TL1 = RLowRL;
		*PWMout1 = 0;
	}
	else
	{
		TH1 = RHighRH;
		TL1 = RHighRL;
		*PWMout1 = 1;
	}	 
}

void CfgLeftPWM(uint fr, uchar dc)
{
	unsigned long tmp;
	unsigned int high,low;
	tmp = 11059200/12/fr;
	high = (tmp*dc)/100;
	low = tmp - high;
	high = 65536 - high + 12;
	low = 65536 - low + 12;
	LHighRH = (uchar)(high >> 8);
	LHighRL = (uchar)high;
	LLowRH = (uchar)(low >> 8);
	LLowRL = (uchar)low;
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TH0 = LHighRH;
	TL0 = LHighRL;
	ET0 = 1;
	TR0 = 1;
}

void CfgRightPWM(uint fr, uchar dc)
{
	unsigned long tmp;
	unsigned int high,low;
	tmp = 11059200/12/fr;
	high = (tmp*dc)/100;
	low = tmp - high;
	high = 65536 - high + 12;
	low = 65536 - low + 12;
	RHighRH = (uchar)(high >> 8);
	RHighRL = (uchar)high;
	RLowRH = (uchar)(low >> 8);
	RLowRL = (uchar)low;
	TMOD &= 0x0F;
	TMOD |= 0x10;
	TH1 = RHighRH;
	TL1 = RHighRL;
	ET1 = 1;
	TR1 = 1;	
}

void ClsPWM()
{
	TR0 = 0;
	ET0 = 0;
	TR1 = 0;
	ET1 = 0;
	*PWMout0 = 1;
	*PWMout1 = 1;
}

void stop()
{
	ClsPWM();
	lf = 1;
	rf = 1;
	lb = 1;
	rb = 1;
}

void fd_f()
{
	ClsPWM();
	lb = 1;
	rb = 1;
	lf = 0;
	rf = 0;
}

void fd_s()
{
	ClsPWM();
	lb = 1;
	rb = 1;
	CfgLeftPWM(100,35);
	CfgRightPWM(100,35);
	lf = 1;
	PWMout0 = lf;
	rf = 1;
	PWMout1 = &rf;
}

void left()
{
	ClsPWM();
	lb = 1;
	rb = 1;
	lf = 1;
	CfgRightPWM(100,35);
	rf = 1;
	PWMout1 = &rf;
}

void right()
{
	ClsPWM();
	lb = 1;
	rb = 1;
	rf = 1;
	CfgLeftPWM(100,35);
	lf = 1;
	PWMout0 = &lf;
}

void left_fd()
{}

void right_fd()
{}

void back_f()
{ 
	ClsPWM();
	lf = 1;
	rf = 1;
	lb = 0;
	rb = 0;
}

void back_s()
{
	ClsPWM();
	lf = 1;
	rf = 1;
	CfgLeftPWM(100,35);
	CfgRightPWM(100,35);
	lb = 1;
	PWMout0 = &lb;
	rb = 1;
	PWMout1 = &rb;
}

void left_bk()
{}

void right_bk()
{}