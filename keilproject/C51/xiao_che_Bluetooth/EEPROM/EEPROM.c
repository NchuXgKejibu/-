#include"EEPROM.h"

unsigned char R[20]={0};		//��������


void ISP_IAP_enable(void)
{
	EA=0;							//���ж�
	ISP_CONTR&=0x18;				//�������λ
	ISP_CONTR|=EE_Waittime;			//д��Ӳ����ʱ
	ISP_CONTR|=0x80;				//ISPENʹ��
}

void ISP_IAP_disable(void)
{
	ISP_CONTR&=0x7f;				//ISPEN=0;
	ISP_TRIG=0x00;
	EA=1;							//���ж�
}

void ISP_IAP_trig(void)
{
	ISP_IAP_enable();				//��ISP/IAP
	ISP_TRIG=0x46;					//��������1
	ISP_TRIG=0xb9;					//��������2
	_nop_();
}

unsigned char EEPROM_Read(unsigned int addr)
{
	ISP_ADDRH=(unsigned char)(addr>>8);			//��ַ
	ISP_ADDRL=(unsigned char)(addr&0x00ff);
	ISP_CMD&=0xf8;								//�������λ
	ISP_CMD|=EECMD_read;						//д�������
	ISP_IAP_trig();								//����
	return(ISP_DATA);							//��������
}

void EEPROM_Write(unsigned int addr,unsigned char dat)
{
	ISP_ADDRH=(unsigned char)(addr>>8);			//��ַ
	ISP_ADDRL=(unsigned char)(addr&0x00ff);
	ISP_CMD&=0xf8;								//�������λ
	ISP_CMD|=EECMD_write;					//д��д����
	ISP_DATA=dat;								//д������
	ISP_IAP_trig();								//����
	ISP_IAP_disable();							//�ر�ISP/IAP
}

void EEPROM_Erase(unsigned int sector_addr)
{
	unsigned int sectoraddr;
	sectoraddr=sector_addr&0xfe00;				//ȡ������ַ
	ISP_ADDRH=(unsigned char)(sectoraddr>>8);	//��ַ
	ISP_ADDRL=0x00;
	ISP_CMD&=0xf8;								//�������λ
	ISP_CMD|=EECMD_erase;						//д���������
	ISP_IAP_trig();								//����
	ISP_IAP_disable();							//�ر�ISP/IAP
}

void EEPROM_Memory(void)
{
	int turn;
	for(turn=0;turn<20;turn++)
	{
		R[turn]=EEPROM_Read(0x2000+turn);	
	}
}


















