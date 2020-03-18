#ifndef __BSTCAR_H__
#define __BSTCAR_H__
/************BST-V51����С��ͷ�ļ�*************/
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
//����С������ģ������IO�� 
sbit LeftF=P1^0;  //����ǰ�� //
sbit LeftB=P1^1;  //���ֺ��� //
				  //0Ϊ��	 //
sbit RightF=P1^2; //����ǰ�� //
sbit RightB=P1^3; //���ֺ��� //

//���尴��
//sbit K4=P3^7;
//sbit K3=P3^6;

//�����������ڶ���
//sbit FM=P2^3;

//ѭ��LEDָʾ�ƶ���
//sbit Left_1_led=P1^6;	 //��ѭ�����⴫����       
//sbit Right_1_led=P1^7;	 //��ѭ�����⴫����  

//����LEDָʾ�ƶ���  
//sbit Left_2_led=P3^4;	 //����Ϻ��⴫����  
//sbit Right_2_led=P3^5;	 //�ұ��Ϻ��⴫����  


#define Left_moto_go      {LeftF=0,LeftB=1;}   //������ǰ��
#define Left_moto_back    {LeftF=1,LeftB=0;}   //��ߵ�����ת
#define Left_moto_Stop    {LeftF=1,LeftB=1;}   //��ߵ��ͣת                     
#define Right_moto_go     {RightF=0,RightB=1;} //�ұߵ����ǰ��
#define Right_moto_back   {RightF=1,RightB=0;} //�ұߵ�������
#define Right_moto_Stop   {RightF=1,RightB=1;} //�ұߵ��ͣת  



#endif
