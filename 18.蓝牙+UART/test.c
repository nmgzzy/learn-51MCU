#include<reg52.h>  

sbit LeftF=P1^0;  //����ǰ�� //
sbit LeftB=P1^1;  //���ֺ��� //
				  //0Ϊ��	 //
sbit RightF=P1^2; //����ǰ�� //
sbit RightB=P1^3; //���ֺ��� //

void run(void);
void stop(void);
void ConfigUART(unsigned int baud);

void main()
{
    EA = 1;   //ʹ�����ж�
    ConfigUART(9600);  //���ò�����Ϊ9600
    while(1);
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

void run(void)
{
    LeftF=0;
	LeftB=1;
	RightF=0;
	RightB=1;
}

void stop(void)
{
    LeftF=1;
	LeftB=1;
	RightF=1;
	RightB=1;
}

void InterruptUART() interrupt 4
{
	if(RI)
	{
		RI = 0;
		if(SBUF==1)
		{
			run();
		}
		else if(SBUF==0)
		{
			stop();
		}
	}
	if(TI)
	{
		TI = 0;
	}
}