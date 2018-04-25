#include"serial.h"

/**********************************************
			���ں���
***********************************************/

void Serial_Init(void)
{
	 TMOD|=0x20;			//���ö�ʱ��1������ʽ2,�Զ�����
	 SCON=0x50;			//���ô��ڷ�ʽ1,ʹ��REN
	 TH1=0xfd;			//װ�س�ֵ,������9600
	 TL1=0xfd;
	 EA=1;				//�����ж�
	 ES=1;				//�������ж�
	 PS=1;				//�жϼ���
	 TR1=1;				//����ʱ��1
}
/**********************************************
			
***********************************************/
void Serial_Send(unsigned char dat)
{
	ES=0;					//�ش����ж�
	SBUF=dat;				//��������
	while(!TI);				//�ȴ����ݷ������
	TI=0;					//��־λ���
	ES=1;					//�������ж�
}
/**********************************************
			
***********************************************/

/***************************************************
void Serial_Receive(void) interrupt	4
{
		if(RI)
		{
			RI=0;
			Serial_dat=SBUF;
			Serial_flag=1;
		}
}

***************************************************/
