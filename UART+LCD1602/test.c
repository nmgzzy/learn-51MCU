#include<reg52.h>  
#define LCD1602_DB  P0

sbit LCD1602_RS = P2^6;
sbit LCD1602_RW = P3^6;
sbit LCD1602_E  = P2^7;
char RxdByte = 0;

void InitLcd1602();
void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str);
void ConfigUART(unsigned int baud);

void main()
{
	EA=1;
	ConfigUART(38400);
	InitLcd1602();
	LcdShowStr(0, 0, "L:");
	LcdShowStr(8, 0, "R:");
	LcdShowStr(0, 1, "M:");
	while(1);		
}

void LcdWaitReady()
{
	unsigned char sta;

	LCD1602_DB = 0xFF;
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	do	{
		LCD1602_E = 1;
		sta = LCD1602_DB;
		LCD1602_E = 0;
	}while(sta & 0x80);
}

void LcdWriteCmd(unsigned char cmd)
{
	LcdWaitReady();
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_E = 1;
	LCD1602_E = 0;
}
void LcdWriteDat(unsigned char dat)
{
	LcdWaitReady();
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_E = 1;
	LCD1602_E = 0;
}
void LcdSetCursor(unsigned char x, unsigned char y)
{
	unsigned char addr;
	if(y == 0)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	LcdWriteCmd(addr | 0x80);
}
void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str)
{
	LcdSetCursor(x, y);
	while(*str != '\0')
	{
		LcdWriteDat(*str++);   
	}
}
void InitLcd1602()
{
	LcdWriteCmd(0x38);
	LcdWriteCmd(0x0C);
	LcdWriteCmd(0x06);
	LcdWriteCmd(0x01);
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

void InterruptUART() interrupt 4
{
	static char Dat[5]=0;
	static char cnt = 0;
	if(RI)
	{
		RI = 0;
		RxdByte = SBUF;
		SBUF = RxdByte;
		Dat[cnt++]=RxdByte;
		if(cnt>=4)
		{
			cnt = 0;
		//	LcdShowStr(2, 0, "    ");
		//	LcdShowStr(2, 0, Dat);
		}		
		
	}
	if(TI)
	{
		TI = 0;
	}
}
