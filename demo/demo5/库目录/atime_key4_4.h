/************************************
�⹦�ܣ��������ɨ���
��Ҫ�����������Ѷ��壺
		#include <reg52.h>
Ӧ�ú�����
			key4_4( )
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-01-29
���ߣ� ATIME	��Ȩ����
ʵ������
		#include <reg52.h>
		#include <string.h>
		#include "atime_key4_4.h"
		#include "atime_lcd1602.h"

		void main()
		{
			unsigned char i[1];
			int_lcd1602(rightmove, cursornotdisplay);
			print1602("You Press",1,1);
			while(1)
			{
				 i[0] =key4_4();
				 print1602(i,1,11);
				 wait_key4_4_ms(10);
			} 
		}

����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
***************************************/


#ifndef _ATIME_KEY4_4_H_ 
#define _ATIME_KEY4_4_H_


/************************************
��ȫ�ֱ�����
***************************************/

#define KEY4 P0			//�����������I/O��


/************************************
�������ܣ���ʱ��Լn ����ms
���ݲ�����n ʱ��
����ֵ����	
ע�⣺�˺������ܾ�ȷ��ʱ
***************************************/
void wait_key4_4_ms(unsigned int n)
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
�������ܣ�ɨ����̰��µİ���
���ݲ�������
����ֵ��0--9  A--E  �� ��	
ע�⣺�����κΰ���ʱ���ؿո�
***************************************/
unsigned char key4_4(void )
{
	KEY4 =0xf0;
	if(KEY4|0XF0 !=0XF0)
	{
		wait_key4_4_ms(10);					   //�����ʱ10msȥ��
		if(KEY4|0XF0 !=0XF0)
		{
			KEY4 =0xfe;
			switch(KEY4)
			{
				case 0xee : return('0') ; break;
				case 0xde : return('1') ; break;
				case 0xbe : return('2') ; break;
				case 0x7e : return('3') ; break;
				default :
				{
					KEY4 =0xfd;
					switch(KEY4)
					{
						case 0xed : return('4') ; break;
						case 0xdd : return('5') ; break;
						case 0xbd : return('6') ; break;
						case 0x7d : return('7') ; break;
						default : 
						{
							KEY4 =0xfb;
							switch(KEY4)
							{
								case 0xeb : return('8') ; break;
								case 0xdb : return('9') ; break;
								case 0xbb : return('A') ; break;
								case 0x7b : return('B') ; break;
								default : 
								{
								 	KEY4 =0xf7;
									switch(KEY4)
									{
										case 0xe7 : return('C') ; break;
										case 0xd7 : return('D') ; break;
										case 0xb7 : return('E') ; break;
										case 0x77 : return('F') ; break;
										default : return (' ');	
									}
								}
							}
						}	
					}	
				}
			}
		}
		else return (' ');
	}
	else return (' ');
}		



#endif