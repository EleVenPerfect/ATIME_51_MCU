/*************************************************************************
*                                                                        *
*                 ��ȡSD�����ͺ������߳���                               *
*                       �����пƼ���                                     *
*                                                                        *
*                                                                        *
* ʵ��Ŀ�ģ�1.��һ��������Һ��������������								 *
*           2.ѧϰSD������������			                             *
*			3.������μ��������Ͳ���SD��CSD��CID�Ĵ���                   *
* ע�⣺����SD�����֪ʶ �뿴��SD��������ϡ�                            *
* ʵ������: ��������ʾ�����������ֺ�����                                 *
**************************************************************************/

#include <reg52.h>
#include <intrins.h>

#include "lcd.h"
#include "MMC.h"

uchar  csd_data[16];
uchar  cid_data[16];

unsigned char by;
unsigned int c_size, c_size_mult, read_bl_len;
unsigned long drive_size;
unsigned long   size_mb;



/**********************************************************

 ��ʱ�Ӻ���

**********************************************************/
void delayms(uint ms)
{
  unsigned char k;

  while (ms--)
  {
    for (k = 0; k < 228; k++)
      ;
  }
}


/**********************************************************

  ������

**********************************************************/
void main(void)
{  
   P2 = 0xff;
   P0 = 0xff;

   LCD_init();
   LCD_clear(5);

    LCD_ShowString(38,5,colors[4],colors[7],"SD/MMC");
    ChineseChar(32,22,0,colors[2],colors[7],1);	//��
    ChineseChar(48,22,0,colors[2],colors[7],2);	//��
    ChineseChar(64,22,0,colors[2],colors[7],3);	//��
    ChineseChar(80,22,0,colors[2],colors[7],4);	//��


	MMC_Init(); //��ʼ��SD��
    if(Init_Flag == 0)
   {
  	 LCD_ShowString(12,50,colors[0],colors[7],"INIT SUCCESS");
	 LCD_ShowString(2,75,colors[0],colors[7],"TYPE:");
     if(card_type)
     {  LCD_ShowString(52,75,colors[2],colors[7],"SD");
        ChineseChar(68,75,1,colors[2],colors[7],1);	//��
     }       
      else
     { LCD_ShowString(52,75,colors[2],colors[7],"MMC");
       ChineseChar(68,75,1,colors[2],colors[7],1);	//��
     }
   
     Read_CID_MMC(cid_data);

     LCD_ShowString(2,95,colors[0],colors[7],"NAME:");
     LCD_ShowChar(50,95,colors[2],colors[7],cid_data[3]);
     LCD_ShowChar(58,95,colors[2],colors[7],cid_data[4]);
     LCD_ShowChar(66,95,colors[2],colors[7],cid_data[5]);
     LCD_ShowChar(74,95,colors[2],colors[7],cid_data[6]);
     LCD_ShowChar(82,95,colors[2],colors[7],cid_data[7]);	  

     
     Read_CSD_MMC(csd_data);
	 
	 //C_SIZEΪCSD[73:62]
     c_size=csd_data[6] & 0x03; //bits 1..0
     c_size<<=10;
     c_size+=(unsigned int)csd_data[7]<<2;
     c_size+=csd_data[8]>>6;
	 
	 //READ_BL_LENΪCSD[83:80]
     by= csd_data[5] & 0x0F;
     read_bl_len=1;
     read_bl_len<<=by;	  //2^by

	 //C_SIZE_MULTΪCSD[49:47]
     by=csd_data[9] & 0x03;      //��ȡmultiply
     by<<=1;
     by+=csd_data[10] >> 7;

     c_size_mult=1;
     c_size_mult<<=(2+by);	  //2^(c_size_mult+2)
	 //�洢��������BLOCKNR*BLOCK_LEN  
	 //BLOCKNR = (C_SIZE+1) * MULT  MULT = (C_SIZE_MULT) * 2^(C_SIZE_MULT + 2)  BLOCK_LEN = (READ_BL_LEN < 12) * 2^(READ_BL_LEN)

     drive_size=(ulong)(c_size+1) * (ulong)c_size_mult * (ulong)read_bl_len;

     size_mb= drive_size>>20;    //1024*1024=1048576=2^20; 
     LCD_ShowString(2,115,colors[0],colors[7],"SIZE:");

     LCD_ShowChar(52,115,colors[2],colors[7],size_mb/1000|0x30); 
     LCD_ShowChar(60,115,colors[2],colors[7],size_mb%1000/100|0x30);
     LCD_ShowChar(68,115,colors[2],colors[7],size_mb%100/10|0x30); 
     LCD_ShowChar(76,115,colors[2],colors[7],size_mb%10|0x30); 
     LCD_ShowChar(84,115,colors[2],colors[7],'M');
     LCD_ShowChar(92,115,colors[2],colors[7],'B');
   }
   else
   {
     LCD_ShowString(12,50,colors[0],colors[7],"INIT FAILURE");	 //��ʼ��ʧ��
     while(1)
     {
       LCD_ShowString(8,75,colors[2],colors[7],"CARD CHECK-UP"); //�������ʾ������ʾ
       delayms(1000);
       LCD_ShowString(8,75,colors[2],colors[7],"              ");	 
       delayms(1000);
     } 
   }
  

   while(1)	;
}

/*********************************************************/
