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

//--定义全局变量--//
unsigned char code DIG_CODE[17]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0、1、2、3、4、5、6、7、8、9、A、b、C、d、E、F的显示码
unsigned char disbuff[4]	   ={ 0,0,0,0,};
/*******************************************************************************
* 函 数 名         : DigDisplay
* 函数功能		   : 使用数码管显示
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void DigDisplay()
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
		}
		GPIO_DIG=disbuff[i];//发送段码
		j=10;						 //扫描间隔时间设定
		while(j--);	
		GPIO_DIG=0x00;//消隐
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
		disbuff[0]=0x3f;	   //“-”
	  disbuff[1]=0x50;	   //“-”
	  disbuff[2]=0x50;	   //“-”
	  disbuff[3]=0x79;	   //“-”
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