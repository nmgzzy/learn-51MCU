#include <reg52.h>

sbit out = P0^1;

unsigned int rad = 0;
unsigned char T0RH = 0;  //T0重载值的高字节
unsigned char T0RL = 0;  //T0重载值的低字节
bit flag1s = 0;

void ConfigTimer0();
void ConfigUART(unsigned int baud);
void action1s();
unsigned char keysta = 1;

void main()
{
	bit keybk=1;
	EA = 1;   //使能总中断
    ConfigTimer0();   //配置T0定时1ms
    ConfigUART(9600);  //配置波特率为9600
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
    TMOD &= 0xF0;   //清零T0的控制位
    TMOD |= 0x01;   //配置T0为模式1
    TH0 = T0RH;     //加载T0重载值
    TL0 = T0RL;
    ET0 = 1;        //使能T0中断
    TR0 = 1;        //启动T0
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

void InterruptTimer0() interrupt 1
{
	static unsigned int cnt=0;
	static unsigned char keybf = 0xff;
    TH0 = T0RH;  //重新加载重载值
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