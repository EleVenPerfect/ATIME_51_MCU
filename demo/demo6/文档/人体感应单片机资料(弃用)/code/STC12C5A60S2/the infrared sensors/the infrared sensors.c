
/*********************************************************************************************
The name of the program£º <Pyroelectric sensor module> ¡¡¡¡ ¡¡
Date£º¡¡ 2012 04 09
hardware£ºmcu(stc12c5a60s2),Operational Amplifier(lm324),Pyroelectric sensor module,etc
								
/*********************************************************************************************/

#include<stc12c5a60s2.h>  
#define uchar unsigned char
#define uint unsigned int
/*********************************************************************************************/
void Delay_us(unsigned int x)
{
	while(x--);
}
/*********************************************************************************************/
void delay(int x)
{
	uchar i,j;
	for(i=0;i<x;i++)
		for(j=0;j<110;j++);
}
/*********************************************************************************************/
void ADC_one()       //Only channel P1.0
{
	P1ASF=0x1f;   
	ADC_CONTR=0x00; 
	AUXR1=0x00;		
	ADC_CONTR=0x80;
	Delay_us(2);
	ADC_CONTR=0x88;     
	Delay_us(2);
	while(ADC_CONTR==0x88); 
	ADC_CONTR=0;     
}
/*********************************************************************************************/

void main()
{	
	while(1)
	{
		float num=0; 
		uint resl=0;
		ADC_one();            
		resl=ADC_RES;
		resl=(resl<<2)+ADC_RESL;
		num=resl/1024.0*5;    
		num=num*1000;

		if(num>2700) 
		{
			P2=0XEF;//Light-emitting diode is lit
		}
		else 
			P2=0XFF;	//Light-emitting diode is extinguished
	}	
}
/*********************************************************************************************/















