/**********************************************************************
*                                                                     *
*           TFTҺ��������̼�ֵ��ʾ����                               *
*              ��  ���пƼ�  ��                                       *
*                                                                     *
* ʵ��Ŀ�ģ�1.����TFT������������ı�д��							  *
            2.ѧ������ȡ��ģ���Ӧ��(ȡ�ַ��ͺ�������)				  *
			3.ѧ������������ģ��������                                *
            4.�ɱ��ASCII��������TFT����ʾ�;������ԭ��            *
*                                                                     *
*ʵ�����󣺲�������ʾ������̵ļ�ֵ                                   *
*                                                                     *
***********************************************************************/

#include <reg52.h>
#include <intrins.h>

#include "lcd.h"
#include "4x3.h"

unsigned char Val[14];

/*********************************************8
*
* ���ַ���ֵ���ƶ���������
************************************************/
void char_Initi()
{
   Val[0]  = 'V';
   Val[1]  = 'a';
   Val[2]  = 'l';
   Val[3]  = 'u';
   Val[4]  = 'e';
   Val[5]  = ':';
   Val[6]  = ' ';
   dis_buf  = '0';   // �Դ˱�����ʼ�����Ա�տ���ʱ��û�а�������ʱ����ʾΪ0
   Val[8]  = ' ';
   Val[9]  = '-';
   Val[10]  = 'H';
   Val[13]  = '\0';


}


/**********************************************************

  ������

**********************************************************/
void main(void)
{  
   P2 = 0xff;
   P0 = 0xff;
   
   char_Initi();
   LCD_init();
   LCD_clear(5);
  
    ChineseChar(14,10,2,colors[2],colors[7],1);	//��
    ChineseChar(38,10,2,colors[2],colors[7],2);	//��
    ChineseChar(62,10,2,colors[2],colors[7],3);	//��
    ChineseChar(86,10,2,colors[2],colors[7],4);	//��
     
   
    ChineseChar(32,60,1,colors[4],colors[7],1);	//��
	ChineseChar(48,60,1,colors[4],colors[7],2);	//��
	ChineseChar(64,60,1,colors[6],colors[7],3);	//��
	ChineseChar(80,60,1,colors[6],colors[7],4);	//��
	
    ChineseChar(24,80,1,colors[2],colors[7],5);	//��
    ChineseChar(40,80,1,colors[2],colors[7],6);	//ֵ
	ChineseChar(56,80,1,colors[2],colors[7],7);	//��
    ChineseChar(72,80,1,colors[2],colors[7],8); //ȡ
    ChineseChar(88,80,1,colors[2],colors[7],9); //��


   while(1)	
  {
        keydown();
        Val[7] = dis_buf; //dis_buf �Ѿ�ת������ASCIIֵ
	    LCD_ShowString(20,100,colors[7],colors[2],Val); //���ַ��͵���������ʾ
	   
  }  
}

/*********************************************************/
