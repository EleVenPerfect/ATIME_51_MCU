
#include "fat.h"


xdata  uchar buffer[512];

uint8   BPBSecPerClust;   // ÿ�ص�������
uint16  FirstFATSector;   // ��FAT��ʼ����
uint16  FirstDirSector;   // ��Ŀ¼��ʼ����
uint16  FirstDataSector;  // ��������ʼ����
uint32  FatClusSec;       // �غ����ڵ�����
uint32  FirstDircluster;  // FAT32��Ŀ¼�״غ�
uint8   DirSecitemCunt;   // FDTÿ����Ŀ¼����� FAT16=8 FAT32=7

xdata   uint16 BPBbytesPerSec;		// ÿ�������ֽ���
xdata	uint16 BPBRevdFATSec;		// FAT1ǰ�ı���������
xdata	uint8  ParNumberFATs;		// �÷����ϵ�FAT����
//	uint16 BPBRootDirCunt;			// ��Ŀ¼����
xdata	uint16 BPBTotSector16;		// 16λ������
xdata	uint16 BPBFATPerSec16;		// 16bitÿFATռ�õ�������
xdata	uint16 BPBhiddsector;		// �÷���ϵͳ����������
xdata	uint32 BPBTotSector32;		// 32λ������
xdata	uint32 DataClusterCount;	// ����������
xdata	uint32 Sector;				// ��������

uint8 FAT_init()
{
/*
xdata  uint16 BPBbytesPerSec;		// ÿ�������ֽ���
xdata	uint16 BPBRevdFATSec;		// FAT1ǰ�ı���������
xdata	uint8  ParNumberFATs;		// �÷����ϵ�FAT����
//	uint16 BPBRootDirCunt;			// ��Ŀ¼����
xdata	uint16 BPBTotSector16;		// 16λ������
xdata	uint16 BPBFATPerSec16;		// 16bitÿFATռ�õ�������
xdata	uint16 BPBhiddsector;		// �÷���ϵͳ����������
xdata	uint32 BPBTotSector32;		// 32λ������
xdata	uint32 DataClusterCount;	// ����������
xdata	uint32 Sector;				// ��������
*/
	mmc_read_sector(0,buffer);		// ��SD��0����

	if((0xEB != buffer[0])&&(0xE9 != buffer[0]))			// ���0��������DBR
	{
		if((0x55 != buffer[510])||(0xAA != buffer[511]))
		 return MBR_ERR;	// MBR����

		Sector = ((uint32)buffer[454])|			// ����MBR��DPT�е�DBRƫ����,ֻ�õ�2�ֽ�
				 ((uint32)buffer[455]<<8);
		mmc_read_sector(Sector,buffer);			// ��DBR��������

		if((0xEB != buffer[0])&&(0xE9 != buffer[0]))
			return DBR_ERR;					// �������DBR�򱨴�����δ��ʽ����
	}
//-----------------------------------------------------------------

	BPBbytesPerSec = ((uint16)buffer[11])|		// ÿ�����ֽ�����ͨ��Ϊ512
					 ((uint16)buffer[12]<<8);

	BPBSecPerClust = buffer[13];				// ÿ��������

	BPBRevdFATSec  = ((uint16)buffer[14])|		// FAT1ǰ�ı���������
					 ((uint16)buffer[15]<<8);

	ParNumberFATs  = buffer[16];				// �÷����ϵ�FAT������ͨ��Ϊ2

//	BPBRootDirCunt = ((uint16)buffer[17])|		// ��Ŀ¼����,���Ϊ0�������FAT32ϵͳ
//					 ((uint16)buffer[18]<<8);

    BPBTotSector16 = ((uint16)buffer[19])|		// 16λ������
                     ((uint16)buffer[20]<<8);

	BPBFATPerSec16 = ((uint16)buffer[22])|		// ÿFATռ�õ�������,16bit
					 ((uint16)buffer[23]<<8);

	BPBhiddsector  = ((uint16)buffer[28])|		// ϵͳ����������,ֻ�õ�2�ֽ�
					 ((uint16)buffer[29]<<8);

    BPBTotSector32 = ((uint32)buffer[32])|		// 32λ������
                     ((uint32)buffer[33]<<8)|
                     ((uint32)buffer[34]<<16)|
                     ((uint32)buffer[35]<<24);

//-------------------------------------_-------------------------------
    // ����߼���������
    if(BPBTotSector32 == 0)
	{
        if(BPBTotSector16 == 0) 
		return SECTORS_ERR;			//�������������̴���
        else 
		BPBTotSector32 = BPBTotSector16;
    }
		
	FirstFATSector  = BPBhiddsector + BPBRevdFATSec;		
		// ��FAT��ʼ����=ϵͳ����������+FAT1ǰ�ı���������

	FirstDirSector  = FirstFATSector + BPBFATPerSec16 * ParNumberFATs;
		// ��Ŀ¼��ʼ����=��FAT��ʼ���� +(ÿFATռ�õ������� �� �÷����ϵ�FAT����)

	FirstDataSector = FirstDirSector + 32;
		// ��������ʼ����=��Ŀ¼��ʼ���� + ��Ŀ¼ռ������
	DataClusterCount= (BPBTotSector32 - FirstDataSector + BPBhiddsector)/BPBSecPerClust;
	    // ����������=(BPB�д�������-��������ʼ����+ϵͳ����������)/ÿ�ص�������
	
	//����Microsoft�ķ����жϴ�����
    //С��4085�ľ���FAT12��С��65525�ľ���FAT16������ΪFAT32��
	if(DataClusterCount<4085)
	return CLUSTER_COUNT_ERR;			//����FAT12�ļ�ϵͳ����֧�֣�
	else 
	if(DataClusterCount<=65525)
	{
		DirSecitemCunt = FAT16;		   // FAT16Ŀ¼�����Ļ���
		return FAT16;			       // �ļ�ϵͳ:FAT16
	}
	else if(DataClusterCount> 65525)
	{
		DirSecitemCunt = FAT32;					 // FAT32Ŀ¼�����Ļ���
		BPBFATPerSec16 = ((uint16)buffer[36])|		// FAT32ÿFATռ�õ�������,ֻ�õ�2�ֽ�
						 ((uint16)buffer[37]<<8);

		FirstDirSector  = FirstFATSector + BPBFATPerSec16 * ParNumberFATs;
			// ��Ŀ¼��ʼ����=��FAT��ʼ����+(ÿFATռ�õ����������÷����ϵ�FAT����)

		FirstDataSector = FirstDirSector + BPBSecPerClust;	
			// ��������ʼ����=��Ŀ¼��ʼ���� + ÿ��������(������Ŀ¼ռ������)

		FirstDircluster = ((uint32)buffer[44])|		// FAT32��Ŀ¼�״غ�
						  ((uint32)buffer[45]<<8)|
						  ((uint32)buffer[46]<<16)|
						  ((uint32)buffer[47]<<24);
		return FAT32;								// �ļ�ϵͳ:FAT32
	}
}