/************************************
�⹦�ܣ�FAT�ļ�ϵͳ
��Ҫ�󣺳����Ѿ����룺
		#include <reg52.h>
		#include "atime_spi.h"
		#include "atime_spi_sdcard.h"
		#include "atime_sd_fat.h"	
Ӧ�ú�����
			unsigned char int_fat(void)
			unsigned char read_file_start512(unsigned long cluster, unsigned char number)
			unsigned char read_file_continue512(unsigned char part)
			unsigned char search_file_name( unsigned long cluster, unsigned char name[12])
�޸���ʷ��
		   	 ���޸��ˡ�       ���޸����ݡ�  			���޸�ʱ�䡯
������ʱ�䣺2014-04-12
���ߣ� ATIME	��Ȩ����
ʵ������
����01�����䵥Ԫ����512�ֽڣ�
			#include <reg52.h>
			#include "atime_serial.h"
			#include "atime_spi.h"
			#include "atime_spi_sdcard.h"
			#include "atime_sd_fat.h"
			
			
			void main()
			{
				unsigned char offset;
				unsigned int i;
				serial_int(disable, baud9600, disable);
			
				int_fat();
				read_file_start512(fat_info.fat_clu_dir, 4);
			
				for(offset=FAT_READING; offset!=FAT_READ_OK; )
				{
					offset =read_file_continue512(0);
			
					for(i=0; i<512; i++)
						send_char(fat_temp[i]);
			
				}
			
				while(1);
			}
����02�����䵥Ԫ����1024�ֽڣ�			
			#include <reg52.h>
			#include "atime_serial.h"
			#include "atime_spi.h"
			#include "atime_spi_sdcard.h"
			#include "atime_sd_fat.h"
			
			
			void main()
			{
				unsigned char offset,j;
				unsigned int i;
				serial_int(disable, baud9600, disable);
			
				int_fat();
			
				send_char(fat_info.fat_cluster);
				read_file_start512(fat_info.fat_clu_dir, 4);
				for(i=0; i<512; i++)
					send_char(fat_temp[i]);
				read_file_continue512(1);
				for(i=0; i<512; i++)
					send_char(fat_temp[i]);
				for(offset=FAT_READING; offset!=FAT_READ_OK; )
				{
					for(j=0; j<fat_info.fat_cluster; j++)
					{
						offset =read_file_continue512(j);
				
						for(i=0; i<512; i++)
							send_char(fat_temp[i]);
					}
				}
			
				while(1);
			}

����03��ͨ���ļ������Ҳ����ļ�
			#include <reg52.h>
			#include "atime_serial.h"
			#include "atime_spi.h"
			#include "atime_spi_sdcard.h"
			#include "atime_sd_fat.h"
			
			void main()
			{
				unsigned char number,offset;
				unsigned int i;
				serial_int(disable, baud9600, disable);
				int_fat();
			
				number =search_file_name( fat_info.fat_clu_dir, "CHAR    .TXT");	 //��Ҫ�ļ�ϵͳ��Ŀ¼������CHAR.TXT�ļ�
				send_char(number);
			
				read_file_start512(fat_info.fat_clu_dir, number);
				for(i=0; i<512; i++)
					send_char(fat_temp[i]);
				for(offset=FAT_READING; offset!=FAT_READ_OK; )
				{
					offset =read_file_continue512(0);
				
					for(i=0; i<512; i++)
						send_char(fat_temp[i]);
				}
			
				while(1);
			}

����������ͣ�
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д������������ǰ�漸��
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
ע�⣺
	���ļ�ϵͳΪFAT32�ļ�ϵͳ��Ŀǰ��֧�ֶ�ȡ�ļ����ݣ������ṩд���ݹ��ܣ�
	�ļ���ֻ֧������8�ֽڵĶ��ļ������ļ���Ӧ�ô�д��ĸ��ʾ��
	��ȡ�ļ������У�ֻ�����˵�һ��FAT������FAT��1�ͱ�2���ڵĲ���޷��жϣ�
	���⺯�����ṩ�ļ���ȡ������ݴ���
	����ļ����ݵĶ�ȡ��������ȡ�����ļ�����ʵ��С�����ǰ�����������Ŀ����ÿ����ȡ�˵���������ȫ�����ֳ�����
	�⺯���ڲ�ֻ����һ����ȡ���ݵĻ���fat_temp[512]����ˣ��������ȡ���ݵĺ�����Ӧ������ȡ����������ݣ���ֹ��һ���������������ݸ��ǣ�
	�ļ�ϵͳ��ʼ�����ļ�ϵͳ��Ϣfat_info��������ģ�
	��ȡ�ļ����ļ���Ϣ������һ���صĴغŻ�ı��⣬������Ϣ���뵱ǰ��ȡ�ļ�����Ϣ����һ�¡�
	�����ļ����ļ��еĶ�ȡ����Ϊ���ļ����ݵĶ�ȡ�������Ҫ�ж��Ƿ�Ϊ�ļ��У���Ҫ���ж��ļ���С���ļ���־�ȡ�
	�������е�ȫ�ֱ������Ѿ�����ΪXDATA����Щ�ͺŵ�Ƭ�����ܻ��ڴ治�㣬���Գ���ȡ�����ֱ�����XDATA���ԡ�	

	����ĵ�������512M��sd���Ͻ��еģ���ʽ��ʱѡ���ļ�ϵͳFAT32�����䵥Ԫ��С512�ֽڣ�û��ѡ��ԭ�豸��Ĭ��ֵ��
***************************************/


#ifndef _ATIME_SD_FAT_H_ 
#define _ATIME_SD_FAT_H_


/************************************
��ȫ�ֱ�����
***************************************/

unsigned char xdata fat_temp[512] ={0};		//FAT���ݻ���

/************************************
�ļ�ϵͳ�ṹ����
***************************************/

struct fat_info
{
	unsigned long fat_offset;				//����������ʼ������
	unsigned long fat_directory;			//��Ŀ¼������
	unsigned long fat_clu_dir;				//��Ŀ¼��ʼ����
	unsigned long fat_fat1;					//fat��������
	unsigned char fat_cluster;				//ÿ��������
}xdata fat_info;


struct file_info
{
	unsigned char file_name[9];				//�ļ��������һλ����Ϊ0��
	unsigned char file_extension[4];		//��չ�������һλ����Ϊ0��
	unsigned long file_size;				//�ļ���С
	unsigned long file_position;			//�ļ���ʼ�شغ�
	unsigned long file_next_pos;			//�ļ�����һ���صĴغ�
}xdata file_info;

/************************************
����궨������
***************************************/

#define NOT_FAT			0X01				//����FAT�ļ�ϵͳ
#define FAT_OK			0X00				//FAT32׼������
#define FAT_READ_OK		0x03			    //��ȡ�ļ��������
#define FAT_READING		0x04				//�ļ����ڶ�ȡ�У����Կ��Լ�����ȡ
/************************************
�������ܣ�FAT�ļ�ϵͳMBR��ʼ��
���ݲ�������
����ֵ����ʼ������
���󷵻�ֵ��NOT_FAT:����FAT�ļ�ϵͳ��û�м�⵽SD��
***************************************/
unsigned long int_mbr_fat(void)
{
	unsigned int i;
	unsigned char not_exit;
	unsigned long offset;

	for(i=0; i<100; i++);
	not_exit =sd_res();
	if(not_exit == 0x01)
		return( NOT_FAT);
	sd_read512( 0, fat_temp);
	if(fat_temp[510] != 0x55 ||fat_temp[511] !=0xAA)
		return( NOT_FAT);
	if(fat_temp[450] != 0x0B)
		return( NOT_FAT);
	if(fat_temp[0] == 0xEB)
		return(0);

	offset =fat_temp[454] +fat_temp[455]*0x100 +
			fat_temp[456]*0x10000 +fat_temp[457]*0x1000000;
		    

	return ( offset);
}


/************************************
�������ܣ�FAT�ļ�ϵͳDBR��ʼ��
���ݲ�����offset����ʼ������
����ֵ����Ŀ¼������
���󷵻�ֵ��NOT_FAT:����FAT�ļ�ϵͳ��û�м�⵽SD��
***************************************/
unsigned long int_dbr_fat(unsigned long offset)
{
	unsigned long directory;
	unsigned char not_exit;

	not_exit =sd_read512( offset, fat_temp);
	if(not_exit == 0x04)
		return(NOT_FAT);
	if(fat_temp[0] != 0xEB)
		return ( NOT_FAT);
	directory =offset +fat_temp[14] +fat_temp[15]*0x100
		       +fat_temp[16]*(fat_temp[36] +fat_temp[37]*0x100	
			   +fat_temp[38]*0x10000 +fat_temp[39]*0x1000000);	
			  
	return ( directory);
}



/************************************
�������ܣ�ÿ��������
���ݲ�����offset����ʼ������
����ֵ��ÿ��������
***************************************/
unsigned char cluster_sector(unsigned long offset)
{
	sd_read512( offset, fat_temp);
	return( fat_temp[13]);
}


/************************************
�������ܣ�FAT�ļ�ϵͳDBR��ʼ��
���ݲ�����offset����ʼ������
����ֵ��FAT��1��������
***************************************/
unsigned long int_dbr_fat_dir(unsigned long offset)
{
	unsigned long directory;

	sd_read512( offset, fat_temp);

	directory =offset +fat_temp[14] +fat_temp[15]*0x100;	
			  
	return ( directory);	
}


/************************************
�������ܣ���ȡ��Ŀ¼��ʼ����
���ݲ�����offset����ʼ������
����ֵ����Ŀ¼��ʼ����
***************************************/
unsigned long int_dbr_clu_dir(unsigned long offset)
{
	sd_read512( offset, fat_temp);
	return( fat_temp[44] +fat_temp[45]*0x100 +fat_temp[46]*0x10000 +fat_temp[47]*0x1000000);
}


/************************************
�������ܣ�fat32�ļ�ϵͳ��ʼ��
���ݲ�������
����ֵ����ʼ�����
		FAT_OK  :�ļ�ϵͳ׼������
		NOT_FAT	:����FAT�ļ�ϵͳ��û�в�SD��
���󷵻�ֵ��NOT_FAT:����FAT�ļ�ϵͳ��û�м�⵽SD��
***************************************/
unsigned char int_fat(void)
{
	fat_info.fat_offset		=int_mbr_fat();
	if(fat_info.fat_offset == NOT_FAT)
		return( NOT_FAT);
	fat_info.fat_directory	=int_dbr_fat( fat_info.fat_offset);
	if(fat_info.fat_directory == NOT_FAT)
		return( NOT_FAT);
	fat_info.fat_fat1		=int_dbr_fat_dir( fat_info.fat_offset);
	fat_info.fat_cluster	=cluster_sector( fat_info.fat_offset);
    fat_info.fat_clu_dir	=int_dbr_clu_dir( fat_info.fat_offset);

	return(FAT_OK);
}


/************************************
�������ܣ�FAT���в�����һ����λ�ã������µ��ļ������
���ݲ�������
����ֵ����
***************************************/
void find_next_cluster(void)
{
	unsigned long next_cluster =0;
	next_cluster =fat_info.fat_fat1 +file_info.file_next_pos/128;	
	sd_read512( next_cluster, fat_temp);
	file_info.file_next_pos =fat_temp[(file_info.file_next_pos%128)*4]+
				  			 fat_temp[(file_info.file_next_pos%128)*4+1]*0x100+	
				   			 fat_temp[(file_info.file_next_pos%128)*4+2]*0x10000+
				  			 fat_temp[(file_info.file_next_pos%128)*4+3]*0x1000000;

}								



/************************************
�������ܣ���ת��Ϊ����
���ݲ�����cluster������
����ֵ��������
***************************************/
unsigned long cluster_to_offset(unsigned long cluster)
{
	unsigned long offset;
	if(cluster < fat_info.fat_clu_dir)
		return (NOT_FAT);
	offset =fat_info.fat_directory +( cluster -fat_info.fat_clu_dir)*fat_info.fat_cluster;
	return ( offset);
}



/************************************
�������ܣ���ȡ�ļ�����Ϣ
���ݲ�����cluster���ļ������ڴ���
		  number���ļ����ţ���0��ʼ��
����ֵ����
***************************************/
void read_filetable(unsigned long cluster, unsigned char number)
{
	unsigned long offset;

	offset =cluster_to_offset( cluster);	 
	offset =offset +number/16;
			    
	sd_read512( offset, fat_temp);

	file_info.file_name[0] =fat_temp[(number%16)*32];
	file_info.file_name[1] =fat_temp[(number%16)*32+1];
	file_info.file_name[2] =fat_temp[(number%16)*32+2];
	file_info.file_name[3] =fat_temp[(number%16)*32+3];
	file_info.file_name[4] =fat_temp[(number%16)*32+4];
	file_info.file_name[5] =fat_temp[(number%16)*32+5];
	file_info.file_name[6] =fat_temp[(number%16)*32+6];
	file_info.file_name[7] =fat_temp[(number%16)*32+7];
	file_info.file_name[8] =0x00;

	file_info.file_extension[0] =fat_temp[(number%16)*32+8];
	file_info.file_extension[1] =fat_temp[(number%16)*32+9];
	file_info.file_extension[2] =fat_temp[(number%16)*32+10];
	file_info.file_extension[3] =0x00;

	file_info.file_size =fat_temp[(number%16)*32+31]+
						 fat_temp[(number%16)*32+30]*0x100+
						 fat_temp[(number%16)*32+29]*0x10000+
						 fat_temp[(number%16)*32+28]*0x1000000;

	file_info.file_position =fat_temp[(number%16)*32+26]+
							 fat_temp[(number%16)*32+27]*0x100+
							 fat_temp[(number%16)*32+20]*0x10000+
							 fat_temp[(number%16)*32+21]*0x1000000;

	file_info.file_next_pos =fat_temp[(number%16)*32+26]+
							 fat_temp[(number%16)*32+27]*0x100+
							 fat_temp[(number%16)*32+20]*0x10000+
							 fat_temp[(number%16)*32+21]*0x1000000;

}


/************************************
�������ܣ���ʼ��ȡ�ļ�����
���ݲ�����cluster���ļ������ڴأ�
		  number���ļ������кţ���0��ʼ��������
����ֵ����ȡ�ļ���״̬
		FAT_READ_OK����ȡ���
		FAT_READING:�ļ����ڶ�ȡ��
***************************************/
unsigned char read_file_start512(unsigned long cluster, unsigned char number)
{
	unsigned long offset;
	read_filetable( cluster, number);														
	offset =cluster_to_offset( file_info.file_next_pos);	
	if(fat_info.fat_cluster == 0x01)
		find_next_cluster();
	sd_read512( offset, fat_temp);			    	//Ҫ���ж϶�ȡ��һ������֮���ȡ���ݣ���ֹ������
	if(file_info.file_next_pos*0x10 >= 0X00000020 && file_info.file_next_pos*0x10 <= 0XFFFFFEF0)
		return( FAT_READING);	
	
	return( FAT_READ_OK);
}

/************************************
�������ܣ�������ȡ�ļ�����
���ݲ�����part���ļ��������ڴصĵڼ�������
����ֵ����ȡ�ļ���״̬
		FAT_READ_OK����ȡ���
		FAT_READING:�ļ����ڶ�ȡ��
***************************************/
unsigned char read_file_continue512(unsigned char part)
{
	unsigned long offset;
	offset =cluster_to_offset( file_info.file_next_pos) +part;
	if((part+1) == fat_info.fat_cluster)
		find_next_cluster();	
	sd_read512( offset, fat_temp);					//Ҫ���ж϶�ȡ��һ������֮���ȡ���ݣ���ֹ������
	if( file_info.file_next_pos*0x10 >= 0X00000020 && file_info.file_next_pos*0x10 <= 0XFFFFFEF0)
		return( FAT_READING);	
	
	return( FAT_READ_OK);
}


/************************************
�������ܣ������ļ������к�
���ݲ�����cluster���������ļ������ڴ�
		  name[11]:�ļ�������չ�����ո���0x20��䡣
		  ��ʽ˵����name[0~7]:�ļ�����name[8]:С���㣬name[9~11]: ��չ�������ֲ��������ÿո���䡣
����ֵ���ļ������кţ����������ڴص��������ļ���������û���ҵ��ļ�
	    һ���ļ���32�ֽڣ�һ������512���ֽڣ������һ���ض�����������16X���ļ���
		����16*fat_info.fat_cluster
***************************************/
unsigned char search_file_name( unsigned long cluster, unsigned char name[12])
{
	unsigned char i;

	for(i=0; i<16*fat_info.fat_cluster; i++)
	{
		read_filetable( cluster, i);
		if(name[0] != file_info.file_name[0])
			continue;
		if(name[1] != file_info.file_name[1])
			continue;
		if(name[2] != file_info.file_name[2])
			continue;
		if(name[3] != file_info.file_name[3])
			continue;
		if(name[4] != file_info.file_name[4])
			continue;
		if(name[5] != file_info.file_name[5])
			continue;
		if(name[6] != file_info.file_name[6])
			continue;
		if(name[7] != file_info.file_name[7])
			continue;
		
		if(name[ 9] != file_info.file_extension[0])
			continue;
		if(name[10] != file_info.file_extension[1])
			continue;
		if(name[11] != file_info.file_extension[2])
			continue;
		
		break;		
	}
	return (i);
}





/************************************
�������ܣ�
���ݲ�����
����ֵ��
***************************************/

#endif