#include <reg52.h>
#include "config.h"
#define LCD1602_DB P0

void main()
{
	InitLcd1602();
	InitADC(); //Init ADC sfr
	while (1)
	{
		ShowResult(0); //Show Channel0
		ShowResult(1); //Show Channel1
		ShowResult(2); //Show Channel2
		ShowResult(3); //Show Channel3
		ShowResult(4); //Show Channel4
		ShowResult(5); //Show Channel5
		ShowResult(6); //Show Channel6
		ShowResult(7); //Show Channel7
	}	
}