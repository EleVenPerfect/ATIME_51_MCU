/************************************
�⹦�ܣ�����1.8��Һ��������
��Ҫ�����������Ѷ��壺
		#include <reg52.h>
		#include "char.h"
		Ҫ��char.h�ڱ��⺯��ǰ�棬�ṩASCII�����
Ӧ�ú�����
	unsigned int trans_rgb(unsigned char r, unsigned char g, unsigned char b)    ��������δ����
	wait_tft18_ms(unsigned int n)
	LCD_SetRamAddr(unsigned int xStart, unsigned int xEnd, unsigned int yStart, unsigned int yEnd) 
	LCD_init(void)
	LCD_clear(unsigned char n)
	pic_play(unsigned char a[],unsigned int Start_X, unsigned int End_X,unsigned int Start_Y,unsigned int End_Y)
	�ļ����滹�в��ֺ�����ע����Ҫʹ��ʱ���ע�ͼ���ʹ��
�޸���ʷ��2014-02-25
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2013-02-11
���ߣ� ATIME	��Ȩ����
ʵ������
	#include <reg52.h>
	#include "char.h"
	#include "atime_tft_1_8.h"
	
	void main()
	{
		P1 =0XF0;
		LCD_init();
		wait_tft18_ms(1000);
		P1 =~P1;
	    while(1)
		{
			LCD_clear(2);
			wait_tft18_ms(500);
			P1 =~P1;
			LCD_ShowString("A T I M E",12,40,colors[0],colors[7]);
		  	wait_tft18_ms(500);
		}	
	}

	#include <reg52.h>
	#include "a.c"
	#include "atime_tft_1_8.h"
	
	void main()
	{
		P1 =0XF0;
		LCD_init();
		wait_tft18_ms(1000);
		P1 =~P1;
	    while(1)
		{
			LCD_clear(7);
			wait_tft18_ms(500);
			P1 =~P1;
		 	pic_play(a,7,61,8,74);
		    pic_play(a,68,122,8,74);
		    pic_play(a,7,61,82,148);
		    pic_play(a,68,122,82,148);
		  	wait_tft18_ms(500);
		}	
	}

����������ͣ�
	123.C(22): error C249: 'DATA': SEGMENT TOO LARGE  ���ļ�̫���ڴ治�㣻����취�������鶨��Ϊcode�����飬�����Ȼ�������Լ���ĳ���ȥ�����õĲ���
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
ע��
	��ʾͼƬҪ����ͼƬ��Сд��������ʼλ�ã�������ʾͼƬ����Ť����λ
	�����ļ������⣬�����������⣬������Ҫ����Ϊcode���顣
	���õĺ�����������ã�/*  */
/***************************************/

#ifndef _ATIME_TFT_1_8_H_ 
#define _ATIME_TFT_1_8_H_

/************************************
��ȫ�ֱ�����
***************************************/

#define  DATA   P0	
sbit LCD_WR   = P2^4;
sbit LCD_RS   = P2^5;
sbit LCD_CS   = P2^6;
sbit LCD_RST  = P2^7;

unsigned int code colors[8]={ 
 0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xffff };
//��      ��     ��     ��     ��    ǳ��	����    ��

/************************************
�������ܣ���ʱn����
���ݲ�������
����ֵ����	
***************************************/
void wait_tft18_ms(unsigned int n)
{
    int i;
	while(n--)
	{
		for(i=0; i<75; i++)
		{
			;
		}	
	}
}


/************************************
�������ܣ�����Ļдһ�ֽ�����
���ݲ�����value�� ��д������
����ֵ����
***************************************/
void WriteDAT(unsigned char value)    // color data
{
	LCD_CS  =  0;
	LCD_RS 	=  1;
	LCD_WR  =  0;
	DATA 	=  value;
    LCD_WR  =  0;
	LCD_WR  =  1;
   	LCD_CS  =  1;
}

/************************************
�������ܣ���Һ��д��һ�ֽ�ָ��
���ݲ�����value����д��ָ��
����ֵ����	
***************************************/
void WriteCOM(unsigned char value)    // color data
{
	LCD_CS  =  0;
	LCD_RS 	=  0;
	LCD_WR  =  0;
	DATA 	=  value;
	LCD_WR  =  0;
	LCD_WR  =  1;
   	LCD_CS  =  1;
}

/************************************
�������ܣ�������ʾ��ֹλ��
���ݲ�����
		  xStart:������ʾ��ʼ��
		  xEnd ��������ʾ������
		  yStart:������ʾ��ʼ��
		  yEnd : ������ʾ������
����ֵ����	
***************************************/
void LCD_SetRamAddr(unsigned int xStart, unsigned int xEnd, unsigned int yStart, unsigned int yEnd) 
{
	WriteCOM(0x2a);		   //��
	WriteDAT(xStart>>8);   //XS15-XS8
	WriteDAT(xStart);	   //XS7-XS0    (X start address)
	WriteDAT(xEnd>>8);	   //XE15-XE8
	WriteDAT(xEnd);		   //XE7-XE0    (X end address)

	WriteCOM(0x2b);		   //��	row address set (RASET)
	WriteDAT(yStart>>8);   //YS15-YS8
	WriteDAT(yStart);	   //YS7-YS0    (Y start address)
	WriteDAT(yEnd>>8);	   //YE15-YE8
	WriteDAT(yEnd);		   //YE7-YE0    (Y end address)

    WriteCOM(0x2c);		   //display on	��ʾ������  
}


/************************************
�������ܣ�Һ����ʼ��
���ݲ�������
����ֵ����	
***************************************/
void  LCD_clear(unsigned char n);	 //����һ��׼�����õĺ���
void LCD_init(void)					 //Һ����ʼ������ʼ
{	                    //�뿴�����ֲ������� �˽��������Ĺ���
	LCD_RST=1;
	wait_tft18_ms(100);
	LCD_RST=0;
	wait_tft18_ms(100);
	LCD_RST=1;
	wait_tft18_ms(100);
	
	WriteCOM(0x01);	    //software reset�����λ
	wait_tft18_ms(100);
	WriteCOM(0x11);	    //sleep out/power on(SLPOUT) �˳�˯��
	wait_tft18_ms(50);
	WriteCOM(0x20);		//display inversion off �ر�ȡ��
	wait_tft18_ms(50);
	WriteCOM(0x38);	    //ID mode off (IDMOFF)
	wait_tft18_ms(50);
	WriteCOM(0x13);	    //Normal display mode on (Partial mode off)
	
	WriteCOM(0x3a);	    //color mode Interface pixel format  (COLMOD)
	WriteDAT(0x05);		//16-bit/pixel , 1-times data transfer
	
	WriteCOM(0xc0);		//power control 1      (PWCTR1)
	WriteDAT(0x03);		//default value  LCM=0 set the GVDD voltage=4.65
	
//	WriteCOM(0xc5);	   
//	WriteDAT(0xc8);	   //VCOMH voltage set 4.300V
	
	WriteCOM(0xc6);
	WriteDAT(0x1f);	   //VCOMAC voltage set 5.550V ;
	wait_tft18_ms(10);
	
	WriteCOM(0xfe);
	WriteDAT(0x00);
	WriteDAT(0x04);
	
	WriteCOM(0x26);	   //gamma sel
	WriteDAT(0x04);
	
	
	WriteCOM(0x2a);	   //column address set (CASET)
	WriteDAT(0x00);	   //XS15-XS8
	WriteDAT(0x00);	   //XS7-XS0    (X start address)
	WriteDAT(0x00);	   //XE15-XE8
	WriteDAT(0x7f);	   //XE7-XE0    (X end address)
	
	WriteCOM(0x2b);	   //row address set (RASET)
	WriteDAT(0x00);	   //YS15-YS8
	WriteDAT(0x00);	   //YS7-YS0    (Y start address)
	WriteDAT(0x00);	   //YE15-YE8
	WriteDAT(0x9f);	   //YE7-YE0    (Y end address)
	
	WriteCOM(0x36);	   //memory data access control  (MADCTR)
	WriteDAT(0xc0);
	
	WriteCOM(0x29);	  // display on

}


/************************************
�������ܣ����Һ����
���ݲ�����n:��������ɫ
����ֵ����	
***************************************/
void  LCD_clear(unsigned char n)
{
   unsigned int num;
   
   LCD_SetRamAddr(2,129,1,160);  //������ʾ������

   for(num=20480;num>0;num--)          //160*128=20480
   {
  	 WriteDAT(colors[n]>>8);   //��8λ
	 WriteDAT(colors[n]);	   //��8λ
   }
}


/************************************
�������ܣ���ɫת��
���ݲ�����
	R:��ɫ
	G:��ɫ
	B:��ɫ
	ȡֵ��Ϊ0~255
����ֵ��16λ���ɫ��ɫ����ֵ	
***************************************/
unsigned int trans_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return((unsigned int)(r&0xf8)<<8|(unsigned int)(g&0xfc)<<3|(unsigned int)(b&0xf8)>>3);
}


/************************************
�������ܣ���ĳλ����ʾĳ���������
���ݲ�����
		  a[]:	   ����ʾ����
		  Start_X: ����λ����ʼ��
		  End__X:  ����λ�ý�����
		  Start_Y: ����λ����ʼ��
		  End_Y:   ����δ֪������
����ֵ����
***************************************/
void  pic_play(unsigned char a[],unsigned int Start_X, unsigned int End_X,unsigned int Start_Y,unsigned int End_Y)
{
   unsigned int m;
   LCD_CS = 0;
   LCD_SetRamAddr(Start_X,End_X-1,Start_Y,End_Y-1) ;   //���õ�ַ
   LCD_RS = 1; 

   for(m=0; m<((End_X-Start_X)*(End_Y-Start_Y)); m++)	
   {		
      WriteDAT(a[m*2+1]);	//��λ��ǰ
	  WriteDAT(a[m*2]);     //��λ�ں�
   }
   LCD_CS = 1;
}


/************************************
�������ܣ���ĳλ����ʾһ���ַ�
���ݲ�����
		  x:  ����λ��
		  y:  ����λ��
		  For_color: �ַ���ɫ
		  Bk_color:	 ������ɫ
		  ch:	 ����ʾ��ĸ
����ֵ����
***************************************/
/*
void LCD_ShowChar(unsigned char x,unsigned char y,unsigned int For_color,unsigned int Bk_color, char ch)
{       
   unsigned char temp;
   unsigned char pos,t;
   unsigned char CHAR_W,CHAR_H;
   
   CHAR_W = 8;         //8*16
   CHAR_H = 16;

   LCD_SetRamAddr(x, x+CHAR_W-1, y, y+CHAR_H-1);	  //������ʾ������
   ch = ch-32;                       //����ASCII����˳��ĵ���Ӧ��ĸ�ı���

   for(pos=0; pos<CHAR_H; pos++)  
   {
      temp= Font8x16[ch][pos];
      
      for(t=0; t<CHAR_W; t++)
      {                 
	    if(temp&0x80)
	     {WriteDAT(For_color>>8); WriteDAT(For_color); } //textcolor  //������ɫ
    
	 else 
		 {WriteDAT(Bk_color>>8) ; WriteDAT(Bk_color) ;  	}
	
		
        temp<<=1; 
	
      }
	  
   }
}  
										 */

/************************************
�������ܣ���ĳλ����ʾһ���ַ���
���ݲ�����
		  x:  ����λ��
		  y:  ����λ��
		  For_color: �ַ���ɫ
		  Bk_color:	 ������ɫ
		  *p:	 ����ʾ��ĸ�����׵�ַ
����ֵ����
***************************************/
/*
void LCD_ShowString(unsigned char *p, unsigned char x, unsigned char y, unsigned int For_color, unsigned int Bk_color)
{         
  	 while(*p!='\0')
     {       
     	LCD_ShowChar(x,y,For_color,Bk_color,*p);
    	 x +=8 ;	  //����Ŀ��
    	 p++ ;
    }
}							   */



/************************************
�������ܣ���ĳλ����ʾһ������
���ݲ�����
		  x:  ����λ��
		  y:  ����λ��
		  For_color: ������ɫ
		  Bk_color:	 ������ɫ
		  c������ʾ����
		  size��
����ֵ����
ʾ����
			   ChineseChar(1,20,40,0,colors[0],colors[7]);	//��
			   ChineseChar(2,32,40,0,colors[0],colors[7]);	//��
			   ChineseChar(3,44,40,0,colors[0],colors[7]);	//��
			   ChineseChar(4,56,40,0,colors[0],colors[7]);	//��
			   ChineseChar(5,68,40,0,colors[0],colors[7]);	//��
			   ChineseChar(6,80,40,0,colors[0],colors[7]);	//Ƭ
			   ChineseChar(7,92,40,0,colors[0],colors[7]);	//��
			   ChineseChar(8,104,40,0,colors[0],colors[7]);	//��
			   ChineseChar(9,116,40,0,colors[0],colors[7]);	//�� 

***************************************/
/*
void ChineseChar(char c, unsigned int x, unsigned int y, int size, unsigned int For_color,unsigned int Bk_color)
{
   int e=0,i,j;
   int ed;
   
   unsigned int  ncols;
   unsigned int  nrows;
   unsigned int  nbytes;

   unsigned char *pfont;
   unsigned char *pchar;
   unsigned char *fonttable[]={(unsigned char *)hz12,(unsigned char *)hz16,(unsigned char *)hz24};		//��������׵�ַ����fortable������
   
   pfont=(unsigned char *)fonttable[size];

   if(size==0)
   {
     ncols =12-1;
     nrows =12-1;
     nbytes =24;	 //(12*12)/8
   }
   else
   if(size==1)
   {
     ncols =16-1;
     nrows =16-1;
     nbytes =32;  //(16*16)/8
   }
   else
   if(size==2)
   {
     ncols =24-1;
     nrows =24-1;
     nbytes =72;   //(24*24)/8
   }
   
   pchar=pfont + (nbytes*(c-1));

   LCD_SetRamAddr(x, x+nrows, y,y+ncols);  //������ʾ������
   
   for(i=0;i<nbytes;i++)
   {
     ed=*pchar++;
	 if(size==0)
	 {
       if(i%2==0)
       e=8;
       else
       e=4;
	 }
	 else
	 e=8;
     
     for(j=0;j<e;j++)
     if((ed>>j)&0x01)
     {
       WriteDAT(For_color>>8);  //textcolor	������ɫ
	   WriteDAT(For_color);
	 }
     else
     {
       WriteDAT(Bk_color>>8);  //backcolor ������ɫ
	   WriteDAT(Bk_color);
	 }
  }
}
*/


#endif