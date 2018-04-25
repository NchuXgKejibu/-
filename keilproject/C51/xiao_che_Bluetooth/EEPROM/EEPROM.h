#include<reg52.h>
#ifndef _EEPROM_H
#define _EEPROM_H
#include<intrins.h>

extern unsigned char R[20];			//��������

/**********************************************
			����ISP/IAP��������
***********************************************/
#define EECMD_read 	0x01		//��
#define EECMD_write	0x02		//д
#define EECMD_erase	0x03		//��������

#define EE_Waittime	0x01		//����CPU�ȴ�ʱ��
/**********************************************
			�Ĵ�������
***********************************************/
sfr ISP_DATA=0xe2;
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;
/**********************************************
				���ܺ���
***********************************************/
void ISP_IAP_enable(void);		//��ISP/IAP����
void ISP_IAP_disable(void);		//�ر�ISP/IAP����
void ISP_IAP_trig(void);		//��������
unsigned char EEPROM_Read(unsigned int addr);	//��ȡָ����ַ���ֵ
void EEPROM_Write(unsigned int addr,unsigned char dat);	//��ָ����ַд���ֽ�
void EEPROM_Erase(unsigned int sector_addr);	//��������
void EEPROM_Memory(void);

#endif