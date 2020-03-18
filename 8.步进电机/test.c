#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

void StartMotor(ulong angle);

ulong beats = 0;

void main()
{	
	EA = 1;
	TMOD = 0x01;
	TH0 = 0xF8;
	TL0 = 0xCD;
	ET0 = 1;
	TR0 = 1;
	StartMotor(360); 	
	while(1);
}

void StartMotor(ulong angle)
{	
	EA = 0;
	beats = angle/360*4096;
	EA = 1;
}

void itrptT0() interrupt 1
{
	code uchar stpMotor[]={
	0x0E,0x0C,0x0D,0x09,0x0B,0x03,0x07,0x06};
	uchar tmp;
	static uchar index = 0;
	TH0 = 0xF8;
	TL0 = 0xCD;
	if(beats)
	{
		tmp = P1;
		tmp = tmp & 0xF0;
		tmp = tmp | stpMotor[index]; 
		P1 = tmp;
		index++;
		index = index & 0x07;
		beats--;
	}
	else
	{
		P1 = P1 | 0x0F;
	}
}