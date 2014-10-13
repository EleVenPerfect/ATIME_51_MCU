/*******************************************************************/
/*                         GUI ͼ�λ��û�����                      */
/* �ļ���: gui.c                                                  */
/* ƽ̨: TOP51 + keil C51                                            */
/* ��˾: ��������                                                  */
/* ��ַ��http://www.ajdz.net                                       */
// ��  ��: TFTͼ���û��ӿڲ����
/* ����              		����         		ע��       */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* ��ΰ��		08/10/20			ԭʼ�ļ�   */
/* ��ΰ��		2010/3/30		V1.1��ֲ��STC ����51��Ƭ��*/
/* ��ΰ��		2010/4/29		V1.2��������ʾԤ���庺���ַ���������������Ҫ�˹��޸��ַ�����*/
/*                        �����˻����κ���ʾ�������ͳ���������*/
/*******************************************************************/
/*˵���� ���֡�Ӣ���ַ�Ϊ8*16�������� �����ַ�Ϊ16*16��������                                        */
/*******************************************************************/
#include "stc.h"
#include "top51.h"
#include "GUI/gui.h"
#include "LCM/ILI9325.h"
#include "bmp.h"
#include "16x8.h"
#include "chinese.h"

/************************************
����
��ڲ����� b_color�Ǳ�����ɫ��
���ڲ���: ��
˵����ʹ�ñ�����ɫ���TFTģ����Ļ��ȫ����ʾ���ݡ�
*************************************/
void GUI_clearscreen(uint b_color)
{
	uint i,j;
	LCD_setwindow(0,0,240,320);
	for (i=0;i<320;i++)
	{
		for(j=0;j<240;j++)
			write_data_u16(b_color);
	}
}


/*********************************************
����
��ڲ����� (x��y)�ǵ�����꣬color �ǵ����ɫ��
���ڲ���: ��
˵������ָ������ɫ��ָ��������λ���ϻ���һ���㡣
**********************************************/
void GUI_Point(uchar x, uint y, uint color)
{  
	LCD_setxy(x,y);
	write_data_u16(color);
}


/**********************************************************
�޷����ַ������Զ�������ʽ��ʾ
��ڲ�����(x��y)����ʾ���ݵ����Ͻ����꣬color ����ʾ�ַ�����ɫ��
          b_color�Ǳ�����ɫ��
���ڲ���: ��
˵�����޷����ַ�������ָ������ɫ�ͱ�����ɫ��ָ��������λ����
�Զ�������ʽ��ʾ������
************************************************************/
void GUI_sprintf_chartobit(uchar x, uint y,uchar dat, uint color,uint b_color)
{  
	uchar i ;
	for(i=0;i<8;i++)
	{
		if((dat&(0x80>>i))==(0x80>>i))
		{
			GUI_sprintf_nu(x,y,1,color,b_color) ;
		}
		else 
		{
			GUI_sprintf_nu(x,y,0,color,b_color) ;
		}
		x+=8 ;
	}
}


/**********************************************************
�޷����ַ�������ʮ��������ʽ��ʾ
��ڲ�����(x��y)����ʾ���ݵ����Ͻ����꣬dat ������ʾ���޷����ַ�������
          color ����ʾ�ַ�����ɫ��b_color�Ǳ�����ɫ��
���ڲ���: ��
˵�����޷����ַ�������ָ������ɫ�ͱ�����ɫ��ָ��������λ����
      ��ʮ��������ʽ��ʾ������
************************************************************/
void GUI_sprintf_chartohex(uchar x, uint y,uchar dat, uint color,uint b_color)
{  
	uchar i ;
	GUI_sprintf_nu(x,y,dat>>4,color,b_color) ;
	x+=8 ;
	GUI_sprintf_nu(x,y,dat&0x0f,color,b_color) ;
}


/**********************************************************
�޷����ַ�������ʮ������ʽ��ʾ
��ڲ�����(x��y)����ʾ���ݵ����Ͻ����꣬dat������ʾ���޷����ַ�������
          color ����ʾ�ַ�����ɫ��b_color�Ǳ�����ɫ��
���ڲ���: ��
˵�����޷����ַ�������ָ������ɫ�ͱ�����ɫ��ָ��������λ����
      ��ʮ������ʽ��ʾ������
************************************************************/
void GUI_sprintf_chartodec(uchar x,uint y,uchar dat,uint color,uint b_color)
{
	GUI_sprintf_char(x,y,dat/100+'0',color,b_color);
	GUI_sprintf_char(x+8,y,dat/10%10+'0',color,b_color);
	GUI_sprintf_char(x+16,y,dat%10+'0',color,b_color);
}


/*********************************************
��ʾ1λ16������
��ڲ����� (x��y) ����ʾ���ݵ����Ͻ����꣬c������ʾ��1λ16��������color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾ1λ16��������
**********************************************/
void GUI_sprintf_nu(uchar x, uint y,uchar nu, uint color,uint b_color)
{  
  	uchar  s_x=0 ,s_y=0, temp=0 ;
  	uint j;
   if (nu>9)
  	{nu=nu+7;} 
   nu=nu+16;
   for(s_y=0;s_y<16;s_y++)
   {
	 	if(s_y+y<320)
	   {
			j=nu;
		   j=j*16+s_y;
		   temp=font16x8[j];
	      //temp = font16x8[nu*16+s_y] ;
	  	   for( s_x=0 ; s_x<8 ; s_x++ )
	      {
		     	if(x+s_x<240)
		      {
			     	if((temp&(0x80>>(s_x))) == (0x80>>(s_x))  )
			      {
				   	GUI_Point(x+s_x, y+s_y,color) ;
			      }
			     	else
			      {
				     	GUI_Point(x+s_x, y+s_y,b_color) ;
				   }
			   }
		   }
	   }
	}
}

/**********************************************************
������
��ڲ����� (x��y)�Ǻ���������꣬length�Ǻ��߳��ȣ�color �Ǻ�����ɫ��
���ڲ���: ��
˵������ָ������ɫ��ָ��λ���ϻ���ָ�����ȵ�һ�����ߡ�
************************************************************/
void GUI_HLine(uchar x, uint y, uchar length, uint color) 
{  
	LCD_setwindow(x,y,x+length-1,y);
	do
	{  
		write_data_u16(color);//�����ʾ�����ˮƽ��
		length--;
	}while(length);
}

/**********************************************************
������
��ڲ����� (x��y)������������꣬high ���߸߶ȣ�color ��������ɫ��
���ڲ���: ��
˵������ָ������ɫ��ָ��λ���ϻ���ָ�����ȵ�һ�����ߡ�
************************************************************/
void GUI_RLine(uchar x, uint y, uint high, uint color) 
{  
   LCD_setwindow(x,y,x,y+high-1);
   do
   {  
		write_data_u16(color);// �����ʾ�������ֱ��
		high--;
   }while(high);	
}


/******************************************************************** 
��ֱ�ߣ����Ի����ⷽ��ֱ�ߣ��������ߡ����ߡ�б�ߣ���
��ڲ����� (x1,y1)���, (x2,y2)�յ�, color��ɫ��
���ڲ���: ��
˵������ָ������ɫ��ָ��������仭��һ��ֱ�ߡ�
***********************************************************************/
void GUI_line(uint x1,uint y1,uint x2,uint y2,uint color)  
{  
    uint t;  
    int xerr=0,yerr=0,delta_x,delta_y,distance;  
    int incx,incy;  
    uint row,col;  
    delta_x = x2-x1;//������������  
    delta_y = y2-y1;  
    col=x1;  
    row=y1;  
    if(delta_x>0) incx=1;//���õ�������  
    else   
    {  
        if(delta_x==0) incx=0;//��ֱ��  
        else {incx=-1;delta_x=-delta_x;}  
    }  
    if(delta_y>0)incy=1;  
    else  
    {  
        if(delta_y==0) incy=0;//ˮƽ��  
        else {incy=-1;delta_y=-delta_y;}  
    }  
    if(delta_x>delta_y) distance=delta_x;//ѡȡ��������������  
    else distance=delta_y;  

    for(t=0;t<=distance+1;t++)  
	{                                     //�������  
	    GUI_Point(col, row, color);
        xerr+=delta_x;  
        yerr+=delta_y;  
      	if(xerr>distance)  
        {  
            xerr-=distance;  
            col+=incx;  
        }  
        if(yerr>distance)  
        {  
            yerr-=distance;  
            row+=incy;  
        }  
    }  
}


/**********************************************************
��ʾͼƬ(ͼ��)
��ڲ�����(x��y)�ǿ�ʼ������꣬length��ͼƬ���ȣ�high��ͼƬ�߶ȡ�//pic ͼƬ�����ָ��
���ڲ���: ��
˵������ָ��λ������ʾ���ȶ����ͼƬ��
Ҫ��ʾ��ͼƬ���ȶ�����bmp.h�е�pic[]�����У�
������޸�ͼƬ��С�����ݣ����޸�bmp.h�е�pic[]���飬
������Image2Lcd�������Ҫ��ʾ��ͼ���Զ�ת��Ϊ�������ݡ� 
************************************************************/
//void GUI_DisPicture(uchar x, uint y, uchar length, uint high ,const uchar *pic)
void GUI_DisPicture(uchar x, uint y, uchar length, uint high)
{
   uint temp=0,tmp=0,num=0;
	LCD_setwindow(x,y,x+length-1,y+high-1);
	num=length*high*2;
	do
	{  
	   //temp=pic[tmp]|( pic[tmp+1]<<8);
	   temp=pic[tmp+1];
	   temp=temp<<8;
	   temp=temp|pic[tmp];
	   write_data_u16(temp);//�����ʾ
	   tmp+=2;
	}while(tmp<num);
}


/*********************************************
��ʾӢ�Ļ������ַ�
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����꣬c����ʾ��Ӣ���ַ���
          color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾ����Ӣ���ַ��������ַ���
**********************************************/
void GUI_sprintf_char(uchar x, uint y,uchar c, uint color,uint b_color)
{  
	uchar  s_x ,s_y, temp ;
  	uint j;
  	c -= 32;
  	for( s_y=0 ; s_y < 16 ; s_y++ )
   {
		if(s_y+y<320)
	   {
			j=c;
		   j=j*16+s_y;
		   temp=font16x8[j];
	     	//temp = font16x8[c*16+s_y] ;
	  	   for( s_x=0 ; s_x<8 ; s_x++ )
	      {
		    	if(x+s_x<240)
		      {
			     	if((temp&(0x80>>(s_x))) == (0x80>>(s_x))  )
			      {
				   	GUI_Point(x+s_x, y+s_y,color) ;
			      }
			     	else
			      {
				     	GUI_Point(x+s_x, y+s_y,b_color) ;
				   }
			   }
		   }
	   }
	}
}



/*********************************************
��ʾӢ���ַ���
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����꣬*s��Ӣ���ַ���ָ�룬
          color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾӢ���ַ�����
**********************************************/
void GUI_sprintf_string(uchar x, uint y,char code *s, uint color,uint b_color)
{  
	for(;*s!='\0';s++)
	{
		GUI_sprintf_char(x, y,*s, color,b_color);
		x=x+8;
	}
	
	//while (*s) 
	//	{
	//	GUI_sprintf_char(x, y,*s, color,b_color);
	//	s++;
	//	x=x+8;
	//	}
}


/*********************************************
��ʾԤ���庺���ַ���
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����꣬color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������ָ��λ������ʾԤ����������ַ�����
      Ҫ��ʾ�������ַ������ȶ�����chinese.h�е�china_char[]�����У�
		������޸������ַ������ȡ����ݣ����޸�chinese.h�е�
		china_char[]���飬��������ģ��ȡ���zimoV2.2����Ҫ��ʾ��
		�����ַ����Զ�ת��Ϊ�������ݡ�
**********************************************/
void GUI_sprintf_HZ(uchar x, uint y, uint color,uint b_color)
{ 
	uchar  s_x=0 ,s_y=0, temp=0 ;  
	uchar n;
	uint j,words;
	words=sizeof(china_char)/32;
	for( n=0 ; n<words ; n++ )
  	{
	 	for( s_x=0 ; s_x<16 ; s_x++ ) 
	  	{
	   	if(s_x+x<240)
	   	{
	   	   j=n;
	   	   j=j*32+s_x;
	   	   temp = china_char[j] ;
	   	   //temp = china_char[n*32+s_x] ;
	   		for( s_y=0 ; s_y<8 ; s_y++ )
	       	{
		     		if(y+s_y<320)
		       	{
			     		if((temp&(0x80>>(s_y))) == (0x80>>(s_y))  )
			       	{
				      	GUI_Point(x+s_x+n*16, y+s_y,color) ;
			       	}
			     		else
			       	{
				      	GUI_Point(x+s_x+n*16, y+s_y,b_color) ;
				   	}
					}
		   	}
		   }
		}
		for( s_x=0 ; s_x<16 ; s_x++ ) 
	  	{
	   	if(s_x+x<240)
	   	{
	   		j=n;
	   		j=j*32+s_x+16;
	   		temp = china_char[j] ;
	   		//temp = china_char[n*32+s_x+16] ;
		    	for( s_y=0 ; s_y<8 ; s_y++ )
	       	{
		     		if(y+s_y<320)
		       	{
			     		if((temp&(0x80>>(s_y))) == (0x80>>(s_y))  )
			       	{
				      	GUI_Point(x+s_x+n*16, y+s_y+8,color) ;
			       	}
			     		else
			       	{
				      	GUI_Point(x+s_x+n*16, y+s_y+8,b_color) ;
				   	}
					}
		   	}
		   }
		}
	}
}



/*********************************************
��ʵ�ľ���
��ڲ����� (sx,sy)���ϽǶ�������, (ex,ey)���½Ƕ�������, color��ɫ
���ڲ���: ��
˵������ָ��λ���ϻ���ʵ�ľ��Ρ�
**********************************************/
void GUI_box(uchar sx,uint sy,uchar ex,uint ey,uint color)
{ 
	uint temp;   
	LCD_setwindow(sx,sy,ex,ey); 
   sx=ex-sx+1;
	sy=ey-sy+1;

	while(sx--)
	{
	 	temp=sy;
		while(temp--)
	 	{	
			write_data_u16(color);
		}
	}
}


/*********************************************
�����ľ���
��ڲ����� (sx,sy)���ϽǶ�������, (ex,ey)���½Ƕ�������, color��ɫ
���ڲ���: ��
˵������ָ��λ���ϻ������ľ��Ρ�
**********************************************/
void GUI_rectangle( uchar sx,uint sy,uchar ex,uint ey,uint color)
{
	GUI_line(sx,sy,ex,sy,color);
	GUI_line(sx,sy,sx,ey,color);
	GUI_line(ex,sy,ex,ey,color);
	GUI_line(sx,ey,ex,ey,color);
}

/*********************************************
��ʮ������ʽ��ʾ�޷��ų�������
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����ꣻ
			 num������ʾ���޷��ų�������
	       num����ֵ��ΧΪ��0~4,294,967,295(ʮ����)��
			 Ҳ����˵���øú�����������ཫһ��10λʮ��������ʾ��LCD���ϣ�
			 color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������һ���޷��ų���������ʮ������ʽ��ʾ��TFT���ϡ�
ע�⣺��ʹ�øú���ʱ������������ʾ�����м�λ����������LCD��Ļ��
      ռ10���ַ��Ŀռ䣨��ʾ�Ķ�λʮ����������10λʱ��
		������������Ч��ʾ����ǰ�油�ո񣩡�
**********************************************/
void GUI_wrul(uchar x, uint y, unsigned long num, uint color,uint b_color)
{
	unsigned long temp; 
	uchar i;
	for(i=0;i<10;i++)
	{
		if(num!=0)
		{
			temp=num/10;
			GUI_sprintf_char(x-7,y,num-temp*10+'0',color,b_color);
			num=temp;
		}
		else/*��ǰд��10λ��Ҳ����ǰ�涼д�ո�*/
		{
			GUI_sprintf_char(x-7,y,' ',color,b_color);
		}
		x=x-8;/*���ù�������ֲ�����Զ�����*/
	}
}

/*********************************************
��ʮ������ʽ��ʾ������
��ڲ����� 
   x��y ----����ʾ���ݵ����Ͻ����� 
    num ----����ʾ�ĳ�����
   bits ----������ʾ��λ��
     dp ----С����λ��
  color ----��ɫ
b_color ----������ɫ
���ڲ���: ��
˵���� 
��һ������������ֵ��ʮ������ʽ��ʾ��TFT���ϣ����Ը�����Ҫȷ��
�Ƿ���ʾС�����Լ�С����λ�ã�Ҳ����ȷ����TFT��Ļ����ʾ��λ����
ע�⣺
1��Ҫ��ʾ�����ݱȹ涨����ʾλ���࣬�涨��λȫ��д������ʾ���������
2��������ʵ�����൱��GUI_wrul��������ǿ�棬�������ָ��bits=10 dp=0��
������ʾ��
GUI_wrlval(20��239��tp��10��0,WHITE,BLACK);
��ô�������ú�GUI_wrul������ȫһ����
**********************************************/
void GUI_wrlval(uchar x, uint y,unsigned long num,uchar bits,uchar dp,uint color,uint b_color)
{
	char str[10];/*�޷��ų�������ת��Ϊ�ַ�����10����������Ҫ10����Ԫ�洢*/	
	unsigned long temp; 
	uchar i;
	//LCD_wrcmd(CUR_AUTO_L);/*���ù�������ֲ�����Զ�����*/
	for(i=0;i<bits;i++)
	{
		if(num!=0)
		{
			temp=num/10;
			str[i]=num-temp*10+'0';
			num=temp;
		}
		else/*��ǰд*/
		{
			if(i>=dp)str[i]=0x20;/*С����ǰ�㶼��ո�*/
			else str[i]='0';/*С������㱣��*/
		}
	}
	i=0;
	if (num!=0)/*Ҫ��ʾ�����ݱȹ涨����ʾλ���࣬������ʾ���*/
	{
		while(i<bits)/*��ǰд���涨��λ����Ҳ����ǰ�涼д�ո�ֱ���涨��λ��*/
		{
			GUI_sprintf_char(x-7,y,'-',color,b_color);/*�涨��λȫ��д-����ʾ�������*/
			i++;
			x=x-8;
			if (i==dp) 
			{
				GUI_sprintf_char(x-7,y,'.',color,b_color);/*����С����*/
				x=x-8;
			}
		}
	}
	else
	{
		while(i<bits)/*��ʾǰ�����Ч����*/
		{
			if ((i==dp)&(str[dp]==0x20))
			{
				GUI_sprintf_char(x-7,y,'.',color,b_color);/*����С����*/
				x=x-8;
				GUI_sprintf_char(x-7,y,'0',color,b_color);/*С����ǰΪ0ʱҪ��д0*/
				x=x-8;
			}
			else
			{
				if ((i==dp)&(i!=0)) 
				{
					GUI_sprintf_char(x-7,y,'.',color,b_color);/*����С����*/
					x=x-8;
				}
				GUI_sprintf_char(x-7,y,str[i],color,b_color);
				x=x-8;
			}
			i++;				
		}
	}
}


/********************************************* 
RGB��ɫ���
��ڲ�����R����ɫ������0-255,G����ɫ������0-255,B����ɫ������0-255
���ڲ���: ��R5-G6-B5��ʽ��Ϻ��16λ��ɫ�롣
˵�����������ϳ�����R8-G8-B8��ʽת����8λ��Ƭ�����õ�R5-G6-B5��ʽ��
**********************************************/
uint RGB(uchar R,uchar G,uchar B)
{
	return((uint)(R&0XF8)<<8|(uint)(G&0XFC)<<3|(uint)(B&0XF8)>>3);
}

