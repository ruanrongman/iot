#include<reg51.h>
#include <intrins.h>
//***************************************
sbit trig =P2^1;
sbit echo =P2^0;
#define GPIO_DIG P0
unsigned int timer=0;
unsigned int time=0;
unsigned long int S=0;
bit flag=0;


sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//--����ȫ�ֱ���--//
unsigned char code DIG_CODE[17]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0��1��2��3��4��5��6��7��8��9��A��b��C��d��E��F����ʾ��
unsigned char disbuff[4]	   ={ 0,0,0,0,};
/*******************************************************************************
* �� �� ��         : DigDisplay
* ��������		   : ʹ���������ʾ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void DigDisplay()
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<8;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
		}
		GPIO_DIG=disbuff[i];//���Ͷ���
		j=10;						 //ɨ����ʱ���趨
		while(j--);	
		GPIO_DIG=0x00;//����
	}
}
/********************************************************/
void count(){
	time = TH0*256 +TL0;
	TL0 = 0;
	TH0 = 0;
  S = (long) (time*0.17) ;
	if(S>=4000||flag==1){
		flag = 0;
		disbuff[0]=0x3f;	   //��-��
	  disbuff[1]=0x50;	   //��-��
	  disbuff[2]=0x50;	   //��-��
	  disbuff[3]=0x79;	   //��-��
	}
	else{
		disbuff[3]=DIG_CODE[S%10000/1000];
	  disbuff[2]=DIG_CODE[S%1000/100];
	  disbuff[1]=DIG_CODE[S%100/10];
	  disbuff[0]=DIG_CODE[S%10/1];
	}
  	
}
//****************************************************
void spilt() interrupt 1{
	flag = 1;
}
void zd3() interrupt 3{
	TH1=0xf8;		   
  TL1=0x30;
	DigDisplay();
	timer++;
	if(timer>=400){
		timer=0;
		trig=1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
		trig = 0;
		
	}
	
}

//****************************************************
void main(){
TMOD = 0X11;
TH0 = 0;
TL0 = 0;
TH1=0xf8;		   
TL1=0x30;
ET0 = 1;
ET1 = 1;
TR1 = 1;
EA = 1;
while(1){
	while(!echo);
	TR0 = 1;	
	while(echo);
	TR0 = 0;
	count();
}

}