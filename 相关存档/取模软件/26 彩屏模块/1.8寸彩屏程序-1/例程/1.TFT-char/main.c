 /*********************************************************************
*                                                                     *
*           TFTҺ�����ַ��ͺ�����ʾ����                               *
*              ��  ���пƼ�  ��                                       *
*                                                                     *
* ʵ��Ŀ�ģ�1.����TFT������������ı�д��							  *
            2.ѧ������ȡ��ģ���Ӧ��(ȡ�ַ��ͺ�������)				  *
			3.ѧ������������ģ��������                                *
*                                                                     *
*ʵ�����󣺲�������ʾ���֡����֡���ĸ��                               *
*                                                                     *
***********************************************************************/

#include <reg52.h>
#include <intrins.h>

#include "lcd.h"


/**********************************************************

  ������

**********************************************************/
void main(void)
{  
   P2 = 0xff;
   P0 = 0xff;

   LCD_init();
   LCD_clear(5);
  
   ChineseChar(14,10,2,colors[2],colors[7],1);	//��
   ChineseChar(38,10,2,colors[2],colors[7],2);	//��
   ChineseChar(62,10,2,colors[2],colors[7],3);	//��
   ChineseChar(86,10,2,colors[2],colors[7],4);	//��
     
   
   LCD_ShowString(12,40,colors[0],colors[7],"-");
   ChineseChar(20,40,0,colors[0],colors[7],1);	//��
   ChineseChar(32,40,0,colors[0],colors[7],2);	//��
   ChineseChar(44,40,0,colors[0],colors[7],3);	//��
   ChineseChar(56,40,0,colors[0],colors[7],4);	//��
   ChineseChar(68,40,0,colors[0],colors[7],5);	//��
   ChineseChar(80,40,0,colors[0],colors[7],6);	//Ƭ
   ChineseChar(92,40,0,colors[0],colors[7],7);	//��
   ChineseChar(104,40,0,colors[0],colors[7],8);	//��
   ChineseChar(116,40,0,colors[0],colors[7],9);	//�� 

   LCD_ShowString(4,58,colors[0],colors[5],"www.PRECHIN.com");


    ChineseChar(0,80,1,colors[4],colors[7],1);	//ר
	ChineseChar(16,80,1,colors[4],colors[7],2);	//ҵ
	ChineseChar(32,80,1,colors[6],colors[7],3);	//��
	ChineseChar(48,80,1,colors[6],colors[7],4);	//��
	ChineseChar(60,80,1,colors[2],colors[7],5);	//��
	ChineseChar(76,80,1,colors[2],colors[7],6);	//̳
	LCD_ShowString(92,80,colors[4],colors[7],":");

	LCD_ShowString(4,100,colors[7],colors[2],"www.PRECHIN.net");

	
   	   
   LCD_ShowString(12,124,colors[0],colors[7],"TELE:");
   LCD_ShowString(12,142,colors[2],colors[7],"0755-61190227");

   while(1)	;
}

/*********************************************************/
