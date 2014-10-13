/**********************************************************************
*                                                                     *
*           TFTҺ������ң�ؼ�ֵ��ʾ����                               *
*              ��  ���пƼ�  ��                                       *
*                                                                     *
* ʵ��Ŀ�ģ�1.����TFT������������ı�д��							  *
            2.ѧ������ȡ��ģ���Ӧ��(ȡ�ַ��ͺ�������)				  *
			3.ѧ������������ģ��������                                *
            4.���պ���ң���жϴ���                                    *
*                                                                     *
*ʵ������ ��������ʾ����ң�ذ�ť�ļ�ֵ                              *
*                                                                     *
***********************************************************************/

#include <reg52.h>
#include <intrins.h>
#include "lcd.h"

unsigned char Val[2];  //��ʼ������

#define uchar unsigned char
#define uint  unsigned int
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};

void delay(uchar x);  //x*0.14MS
void delay1(int ms);
void beep();
void IR_initi();

sbit IRIN = P3^2;         //���������������
sbit BEEP = P1^5;         //������������
sbit RELAY= P1^4;         //�̵���������

uchar IRCOM[7] = {0,0,0,0,0,0,0};

/**********************************************************

  ������

**********************************************************/
void main(void)
{  
   P2 = 0xff;
   P0 = 0xff;
   
   IR_initi() ; 
   LCD_init();
   LCD_clear(5);
  
    ChineseChar(14,10,2,colors[2],colors[7],1);	  //��
    ChineseChar(38,10,2,colors[2],colors[7],2);	  //��
    ChineseChar(62,10,2,colors[2],colors[7],3);	  //��
    ChineseChar(86,10,2,colors[2],colors[7],4);	  //��
     
   
    ChineseChar(32,60,1,colors[4],colors[7],1);	  //��
	ChineseChar(48,60,1,colors[4],colors[7],2);	  //��
	ChineseChar(64,60,1,colors[6],colors[7],3);	  //ң
	ChineseChar(80,60,1,colors[6],colors[7],4);	  //��
	
    ChineseChar(24,80,1,colors[2],colors[7],5);   //��
    ChineseChar(40,80,1,colors[2],colors[7],6);	  //ֵ
	ChineseChar(56,80,1,colors[2],colors[7],7);	  //��
    ChineseChar(72,80,1,colors[2],colors[7],8);   //ȡ
    ChineseChar(88,80,1,colors[2],colors[7],9);   //��
    
    LCD_ShowString(22,100,colors[7],colors[2],"Value:    H");  //���ַ��͵���������ʾ
    //LCD_ShowString(102,100,colors[7],colors[2],"");  //���ַ��͵���������ʾ
   


   while(1)	
  {
        Val[0] =  IRCOM[6];
        Val[1] =  IRCOM[5];
        
	    LCD_ShowString(78,100,colors[7],colors[2],Val); //���ַ��͵���������ʾ
	   
  }  
}

/***********************************************************
*                                                          *
*                ͨ���ⲿ�ж�������
***********************************************************/
void IR_initi()  
{
   IRIN=1;                    //I/O�ڳ�ʼ��
   BEEP=1;
   RELAY=1; 
   delay1(10);                 //��ʱ
   IE = 0x81;                 //�������ж��ж�,ʹ�� INT0 �ⲿ�ж�
   TCON = 0x01;               //������ʽΪ���帺���ش���

}

/**********************************************************/
void IR_IN() interrupt 0 using 0
{
  unsigned char j,k,N=0;
     EX0 = 0;   
	 delay(15);
	 if (IRIN==1) 
     { EX0 =1;
	   return;
	  } 
                           //ȷ��IR�źų���
  while (!IRIN)            //��IR��Ϊ�ߵ�ƽ������9ms��ǰ���͵�ƽ�źš�
    {delay(1);}

 for (j=0;j<4;j++)         //�ռ���������
 { 
  for (k=0;k<8;k++)        //ÿ��������8λ
  {
   while (IRIN)            //�� IR ��Ϊ�͵�ƽ������4.5ms��ǰ���ߵ�ƽ�źš�
     {delay(1);}
    while (!IRIN)          //�� IR ��Ϊ�ߵ�ƽ
     {delay(1);}
     while (IRIN)           //����IR�ߵ�ƽʱ��
      {
    delay(1);
    N++;           
    if (N>=30)
	 { EX0=1;
	 return;}                  //0.14ms���������Զ��뿪��
      }                        //�ߵ�ƽ�������                
     IRCOM[j]=IRCOM[j] >> 1;                  //�������λ����0��
     if (N>=8) {IRCOM[j] = IRCOM[j] | 0x80;}  //�������λ����1��
     N=0;
  }//end for k
 }//end for j
   
   if (IRCOM[2]!=~IRCOM[3])
   { EX0=1;
     return; }

   IRCOM[5]=IRCOM[2] & 0x0F;     //ȡ����ĵ���λ
   IRCOM[6]=IRCOM[2] >> 4;       //����4�Σ�����λ��Ϊ����λ

   if(IRCOM[5]>9)
    { IRCOM[5]=IRCOM[5]+0x37;}    //�ڶ�λ����ʾ
   else
	  IRCOM[5]=IRCOM[5]+0x30;

   if(IRCOM[6]>9)
    { IRCOM[6]=IRCOM[6]+0x37;}    //��һλ����ʾ 
   else
	  IRCOM[6]=IRCOM[6]+0x30;
   


     beep();
     EX0 = 1; 
} 


/**********************************************************/
void beep()
{
  unsigned char i;
  for (i=0;i<100;i++)
   {
   delay(4);
   BEEP=!BEEP;                 //BEEPȡ��
   } 
  BEEP=1;                      //�رշ�����
}
/**********************************************************/
void delay(unsigned char x)    //x*0.14MS
{
 unsigned char i;
  while(x--)
 {
  for (i = 0; i<13; i++) {}
 }
}

/**********************************************************/
void delay1(int ms)
{
 unsigned char y;
  while(ms--)
 {
  for(y = 0; y<250; y++)
  {
   _nop_();
   _nop_();
   _nop_();
   _nop_();
  }
 }
}


