#include "reg52.h"
#include "intrins.h"
#define FOSC 18432000L
#define BAUD 9600

/*Declare SFR associated with the ADC */
sfr ADC_CONTR = 0xBC; //ADC control register
sfr ADC_RES = 0xBD; //ADC high 8-bit result register
sfr ADC_LOW2 = 0xBE; //ADC low 2-bit result register
sfr P1ASF = 0x9D; //P1 secondary function control register
/*Define ADC operation const for ADC_CONTR*/

/*----------------------------
Send ADC result to UART
----------------------------*/
void ShowResult(uint8 ch)
{
	SendData(ch); //Show Channel NO.
	SendData(GetADCResult(ch)); //Show ADC high 8-bit result
	//if you want show 10-bit result, uncomment next line
	// SendData(ADC_LOW2); //Show ADC low 2-bit result
}
/*----------------------------
Get ADC result
----------------------------*/
BYTE GetADCResult(BYTE ch)
{
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
	_nop_(); //Must wait before inquiry
	_nop_();
	_nop_();
	_nop_();
	while (!(ADC_CONTR & ADC_FLAG)); //Wait complete flag
	ADC_CONTR &= ~ADC_FLAG; //Close ADC
	return ADC_RES; //Return ADC result
}

/*----------------------------
Initial ADC sfr
----------------------------*/
void InitADC()
{
	P1ASF = 0xff; //Open 8 channels ADC function
	ADC_RES = 0; //Clear previous result
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
	Delay(2); //ADC power-on and delay
}
/*----------------------------
Send one byte data to PC
Input: dat (UART data)
Output:-
----------------------------*/
void SendData(BYTE dat)
{
	
}
/*----------------------------
Software delay function
----------------------------*/
void Delay(uint16 n)
{
	uint16 x;
	while (n--)
	{
		x = 5000;
		while (x--);
	}
}