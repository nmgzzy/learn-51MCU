#include<reg52.h>  

sbit LeftF=P1^0;  //����ǰ�� //
sbit LeftB=P1^1;  //���ֺ��� //
				  //0Ϊ��	 //
sbit RightF=P1^2; //����ǰ�� //
sbit RightB=P1^3; //���ֺ��� //

void delay(unsigned int xms)				
{
	unsigned int i,j;
	for(i=xms;i>0;i--)		      //i=xms����ʱԼxms����
		for(j=112;j>0;j--);
}

void run(void)	//ǰ��
{
    LeftF=0;
	LeftB=1;
	RightF=0;
	RightB=1;
}

void back(void)			  //���˺���
{
    LeftF=1;
	LeftB=0; 
	RightB=0;
	RightF=1;
}

void right(void)		 //��ת����
{
    LeftF=0;
	LeftB=1;
	RightB=1;
	RightF=1;
}

void left(void)			  //��ת����
{
    LeftF=1;
	LeftB=1; 
	RightB=1;
	RightF=0;
}

void stop(void)			  //ֹͣ����
{
    LeftF=1;
	LeftB=1;
	RightB=1;
	RightF=1;
}


void spin_right(void)	  //���Ҵ�ת����
{
    LeftF=0;
	LeftB=1;
	RightB=0;
	RightF=1;
}

void spin_left(void)	  //�����ת����
{
    LeftF=1;
	LeftB=0; 
	RightB=1;
	RightF=0;
}



void main(void)
{
    delay(2000); //��ʱ2s������
    back();		 
	delay(1000); //����1s
	stop();		 
	delay(500);	 //ֹͣ0.5s
	run();		 
	delay(1000); //ǰ��1s
	stop();
	delay(500);	 //ֹͣ0.5s
	left();
	delay(1000); //����ת1s
	right();
	delay(1000); //����ת1s
	spin_right();
    delay(2000); //������ת2s
	spin_left();
	delay(2000); //������ת2s
	stop();		 //ͣ��
	while(1);  //��ѭ��	��λ�������ܳ���
}











