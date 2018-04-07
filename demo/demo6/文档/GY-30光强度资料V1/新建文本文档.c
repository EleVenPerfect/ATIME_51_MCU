
//***************************************
// BH1750FVI IIC????
// ?????STC89C51 
// ??:11.0592M
// ??:LCD1602
// ???? Keil uVision2
// ??????24c04????
// ??:2011?4?20?
//****************************************
#include "STC12C5A60S2.H"
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H>
#include "atime_serial.h"
#define   uchar unsigned char
#define   uint unsigned int	
#define   DataPort P0	 //LCD1602????
sbit	  	SCL=P3^4;      //IIC??????
sbit  	  SDA=P3^5;      //IIC??????
sbit      LCM_RS=P2^0;   //LCD1602????		
sbit      LCM_RW=P2^1;   //LCD1602????		
sbit      LCM_EN=P2^2;   //LCD1602???? 

#define	  SlaveAddress   0x46 //?????IIC???????,??ALT  ADDRESS????????
                              //ALT  ADDRESS????????0x46,???????0xB8
typedef   unsigned char BYTE;
typedef   unsigned short WORD;

BYTE    BUF[8];                         //???????      	
uchar   ge,shi,bai,qian,wan;            //????
int     dis_data;                       //??

void delay_nms(unsigned int k);
void InitLcd();
void Init_BH1750(void);

void WriteDataLCM(uchar dataW);
void WriteCommandLCM(uchar CMD,uchar Attribc);
void DisplayOneChar(uchar X,uchar Y,uchar DData);
void conversion(uint temp_data);

void  Single_Write_BH1750(uchar REG_Address);               //??????
uchar Single_Read_BH1750(uchar REG_Address);                //???????????
void  Multiple_Read_BH1750();                               //????????????
//------------------------------------
void Delay5us();
void Delay5ms();
void BH1750_Start();                    //????
void BH1750_Stop();                     //????
void BH1750_SendACK(bit ack);           //??ACK
bit  BH1750_RecvACK();                  //?ack
void BH1750_SendByte(BYTE dat);         //IIC?????
BYTE BH1750_RecvByte();                 //IIC?????

//-----------------------------------

//*********************************************************
void conversion(uint temp_data)  //  ????? ?,?,?,?,?
{  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //????
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //????
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //????
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //????
    ge=temp_data+0x30; 	
}

//????**************************
void delay_nms(unsigned int k)	
{						
	unsigned char i, j;
	for(;k>0;k--)
	{
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);					
}
	}

/*******************************/
void WaitForEnable(void)	
{					
DataPort=0xff;		
LCM_RS=0;LCM_RW=1;_nop_();
LCM_EN=1;_nop_();_nop_();
while(DataPort&0x80);	
LCM_EN=0;				
}					
/*******************************/
void WriteCommandLCM(uchar CMD,uchar Attribc)
{					
if(Attribc)WaitForEnable();	
LCM_RS=0;LCM_RW=0;_nop_();
DataPort=CMD;_nop_();	
LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}					
/*******************************/
void WriteDataLCM(uchar dataW)
{					
WaitForEnable();		
LCM_RS=1;LCM_RW=0;_nop_();
DataPort=dataW;_nop_();	
LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}		
/***********************************/
void InitLcd()				
{			
WriteCommandLCM(0x38,1);	
WriteCommandLCM(0x08,1);	
WriteCommandLCM(0x01,1);	
WriteCommandLCM(0x06,1);	
WriteCommandLCM(0x0c,1);
}			
/***********************************/
void DisplayOneChar(uchar X,uchar Y,uchar DData)
{						
Y&=1;						
X&=15;						
if(Y)X|=0x40;					
X|=0x80;			
WriteCommandLCM(X,0);		
WriteDataLCM(DData);		
}						

/**************************************
??5??(STC90C52RC@12M)
???????,???????,???????????
???1T?MCU?,????????
**************************************/
void Delay5us()
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 10;
	while (--i);
}
/**************************************
??5??(STC90C52RC@12M)
???????,???????
???1T?MCU?,????????
**************************************/
void Delay5ms()
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 54;
	j = 198;
	do
	{
		while (--j);
	} while (--i);
}

/**************************************
????
**************************************/
void BH1750_Start()
{
    SDA = 1;                    //?????
    SCL = 1;                    //?????
    Delay5us();                 //??
    SDA = 0;                    //?????
    Delay5us();                 //??
    SCL = 0;                    //?????
}

/**************************************
????
**************************************/
void BH1750_Stop()
{
    SDA = 0;                    //?????
    SCL = 1;                    //?????
    Delay5us();                 //??
    SDA = 1;                    //?????
    Delay5us();                 //??
}

/**************************************
??????
????:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK(bit ack)
{
    SDA = ack;                  //?????
    SCL = 1;                    //?????
    Delay5us();                 //??
    SCL = 0;                    //?????
    Delay5us();                 //??
}

/**************************************
??????
**************************************/
bit BH1750_RecvACK()
{
    SCL = 1;                    //?????
    Delay5us();                 //??
    CY = SDA;                   //?????
    SCL = 0;                    //?????
    Delay5us();                 //??

    return CY;
}

/**************************************
?IIC??????????
**************************************/
void BH1750_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8????
    {
        dat <<= 1;              //????????
        SDA = CY;               //????
        SCL = 1;                //?????
        Delay5us();             //??
        SCL = 0;                //?????
        Delay5us();             //??
    }
    BH1750_RecvACK();
}

/**************************************
?IIC??????????
**************************************/
BYTE BH1750_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //??????,??????,
    for (i=0; i<8; i++)         //8????
    {
        dat <<= 1;
        SCL = 1;                //?????
        Delay5us();             //??
        dat |= SDA;             //???               
        SCL = 0;                //?????
        Delay5us();             //??
    }
    return dat;
}

//*********************************

void Single_Write_BH1750(uchar REG_Address)
{
    BH1750_Start();                  //????
    BH1750_SendByte(SlaveAddress);   //??????+???
    BH1750_SendByte(REG_Address);    //???????,
  //  BH1750_SendByte(REG_data);       //???????,
    BH1750_Stop();                   //??????
}

//********?????*****************************************
/*
uchar Single_Read_BH1750(uchar REG_Address)
{  uchar REG_data;
    BH1750_Start();                          //????
    BH1750_SendByte(SlaveAddress);           //??????+???
    BH1750_SendByte(REG_Address);                   //????????,?0??	
    BH1750_Start();                          //????
    BH1750_SendByte(SlaveAddress+1);         //??????+???
    REG_data=BH1750_RecvByte();              //???????
	BH1750_SendACK(1);   
	BH1750_Stop();                           //????
    return REG_data; 
}
*/
//*********************************************************
//
//????BH1750????
//
//*********************************************************
void Multiple_read_BH1750(void)
{   uchar i;	
    BH1750_Start();                          //????
    BH1750_SendByte(SlaveAddress+1);         //??????+???
	
	 for (i=0; i<3; i++)                      //????2?????,???BUF
    {
        BUF[i] = BH1750_RecvByte();          //BUF[0]??0x32??????
        if (i == 3)
        {

           BH1750_SendACK(1);                //?????????NOACK
        }
        else
        {		
          BH1750_SendACK(0);                //??ACK
       }
   }

    BH1750_Stop();                          //????
    Delay5ms();
}


//???BH1750,???????pdf????****
void Init_BH1750()
{
   Single_Write_BH1750(0x01);  

}
//*********************************************************
//???********
//*********************************************************
void main()
{  
   float temp;
   delay_nms(100);	    //??100ms	
	serial_int(enable, baud14400, disable);
   //InitLcd();           //???LCD
   //Init_BH1750();       //???BH1750
 
  while(1)              //??
  { 
Init_BH1750();  
    Single_Write_BH1750(0x01);   // power on
    Single_Write_BH1750(0x10);   // H- resolution mode

     delay_nms(500);              //??180ms

    Multiple_Read_BH1750();       //??????,???BUF?

    dis_data=BUF[0];
    dis_data=(dis_data<<8)+BUF[1];//????,?????
    
    temp=(float)dis_data/1.2;

    conversion(temp);         //???????
	//DisplayOneChar(0,0,'L'); 
	//DisplayOneChar(1,0,'i'); 
	//DisplayOneChar(2,0,'g'); 
	//DisplayOneChar(3,0,'h'); 
	//DisplayOneChar(4,0,'t'); 
   // DisplayOneChar(5,0,':'); 

    //DisplayOneChar(7,0,wan); //????
    //DisplayOneChar(8,0,qian);  
    //DisplayOneChar(9,0,bai); 
    //DisplayOneChar(10,0,shi); 
	//DisplayOneChar(11,0,ge); 

	//DisplayOneChar(13,0,'l'); ////?????
	//DisplayOneChar(14,0,'x');  
            send_char(wan);
						send_char(qian);
						send_char(bai);
						send_char(shi);
						send_char(ge);
						send_char('\n');
  }
} 

