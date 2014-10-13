#ifndef GUI_H
#define GUI_H

#include"config.h"

/*GUI����*/
void GUI_clearscreen(uint b_color);//����
void GUI_Point(uchar x, uint y, uint color);//����
void GUI_sprintf_chartobit(uchar x, uint y,uchar dat, uint color,uint b_color);//�޷����ַ������Զ�������ʽ��ʾ
void GUI_sprintf_chartohex(uchar x, uint y,uchar dat, uint color,uint b_color);//�޷����ַ�������ʮ��������ʽ��ʾ
void GUI_sprintf_chartodec(uchar x,uint y,uchar dat,uint color,uint b_color);//�޷����ַ�������ʮ������ʽ��ʾ
void GUI_sprintf_nu(uchar x, uint y,uchar nu, uint color,uint b_color);//��ʾ1λ16������
void GUI_HLine(uchar x, uint y, uchar length, uint color);//������
void GUI_RLine(uchar x, uint y, uint high, uint color);//������
void GUI_line(uint x1,uint y1,uint x2,uint y2,uint color);//��ֱ��
void GUI_DisPicture(uchar x, uint y, uchar length, uint high);//��ʾͼƬ(ͼ��)
void GUI_sprintf_char(uchar x, uint y,uchar c, uint color,uint b_color);//��ʾӢ�Ļ������ַ�
void GUI_sprintf_string(uchar x, uint y,char code *s, uint color,uint b_color);//��ʾӢ���ַ���
void GUI_sprintf_HZ(uchar x, uint y, uint color,uint b_color);//��ʾԤ���庺���ַ���
void GUI_box(uchar sx,uint sy,uchar ex,uint ey,uint color);//��ʵ�ľ���
void GUI_rectangle( uchar sx,uint sy,uchar ex,uint ey,uint color);//�����ľ���
void GUI_wrul(uchar x, uint y, unsigned long num, uint color,uint b_color);//��ʮ������ʽ��ʾ�޷��ų�������
void GUI_wrlval(uchar x, uint y,unsigned long num,uchar bits,uchar dp,uint color,uint b_color);//��ʮ������ʽ��ʾ������
uint RGB(uchar R,uchar G,uchar B);//RGB��ɫ���


/*���峣����ɫ����ɫ��*/
#define RED 0xf800	//��
#define YELLOW 0xffe0	//��
#define GREEN 0x07e0	//��
#define CYAN 0x07ff	//��
#define BLUE 0x001f	//��
#define PURPLE 0xf81f	//��
#define BLACK 0x0000	//��
#define WHITE 0xffff	//��
#define GRAY 0x7bef	//��


#endif













