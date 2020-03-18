#include<reg52.h>  

sbit LeftF=P1^0;  //左轮前进 //
sbit LeftB=P1^1;  //左轮后退 //
				  //0为真	 //
sbit RightF=P1^2; //右轮前进 //
sbit RightB=P1^3; //右轮后退 //

void run(void);
void stop(void);
void ConfigUART(unsigned int baud);

void main()
{
    EA = 1;   //使能总中断
    ConfigUART(9600);  //配置波特率为9600
    while(1);
}

void ConfigUART(unsigned int baud)
{
    SCON  = 0x50;  //配置串口为模式1
    TMOD &= 0x0F;  //清零T1的控制位
    TMOD |= 0x20;  //配置T1为模式2
    TH1 = 256 - (11059200/12/32)/baud;  //计算T1重载值
    TL1 = TH1;     //初值等于重载值
    ET1 = 0;       //禁止T1中断
    ES  = 1;       //使能串口中断
    TR1 = 1;       //启动T1
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