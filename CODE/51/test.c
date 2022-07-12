#include "wca.h"

//mode choice
sbit MODE1 = P0^0;
sbit MODE2 = P0^1;
sbit MODE3 = P0^2;
sbit MODE4 = P0^3;
sbit MODE5 = P0^4;
sbit MODE6 = P0^5;
//little toy
sbit LED1 = P1^0;
sbit LED2 = P1^1;
sbit BUZZER = P1^2;
sbit BUTTON1 = P2^7;
sbit BUTTON2 = P2^4;
//the car
sbit LEFT_BI = P2^3;
sbit LEFT_FI = P2^2;
sbit RIGHT_BI = P2^1;
sbit RIGHT_FI =	P2^0;
sbit LEFT_H1 = P3^5;
sbit LEFT_H2 = P3^3;//int0
sbit RIGTH_H1 = P3^4;
sbit RIGHT_H2 = P3^2;//int1
//others
sbit SET = P3^6;//wireless part setting
sbit CS = P3^7;//wireless part sleep
sbit RST = P5^4;
sbit TXD = P3^1;
sbit RXD = P3^0;

unsigned char Mode;// sent to cam
unsigned char Move;//receive from cam
unsigned char Flag;//1 = have received data
unsigned char WirelessInpute;//this two only for wireless part
unsigned char WirelessOutput;
void initPins();
void initSerial();
void sendMode();
void receiveMove();
void startMove();
void carStop();
void carGoStraight();
void carGOLeft();
void carGoRight();
void carBackStraight();
void carBackLeft();
void carBackRight();
void getLED1On();
void getLED2On();
void getLED1Off();
void getLED2Off();
void getBuzzerOn();
void getBuzzerOff();
unsigned char getMode();
void getWirelessInput();
void getWirelessOutput();
void getDelay(int TIME_BY_S);
void main()
{
	initPins();//some pins  inital status
	initSerial();//serial attribute init
	IE = 0;	// ping bi zhong duan
	while(1)//start loop
	{		
		// carGoStraight();	
		// getDelay(2000);
		// carStop();
		// getDelay(3000);
		carGOLeft();
		getDelay(280);
		carStop();
		getDelay(2000);
		// carGoStraight();
		// // LED1 = LEFT_BI;
		// // LED2 = RIGHT_BI;
		// LED1 = 1;
        // getDelay(1);
        // LED1 = 0;
        // LED2 = 1;
        // getDelay(1);
        // LED2 = 0; 
		// if(MODE6 == 0)
		// {
		// 	LED1 = 1;
		// }
		// else 
		// {
		// 	LED1 = 0;
		// }


	}//loop end
	//one loop one move	
}
void initPins()
{
	LED1 = 0;
	LED2 = 0;//light  off first
	// LEFT_BI = 1;
	// LEFT_FI = 1;
	// RIGHT_BI = 1;
	// RIGHT_FI = 1;
	BUTTON1 = 1;
	BUTTON2 = 1;
	BUZZER = 1;
	MODE1 = 1;
	MODE2 = 1;
	MODE3 = 1;
	MODE4 = 1;
	MODE5 = 1;	
	MODE6 = 1;
	// WirelessInpute = 0;// not sure!!!
	// WirelessOutput = 0;
	P0M1 = 0x00;
    P0M0 = 0x01;
    P1M1 = 0x00;
    P1M0 = 0x01;
    P2M1 = 0x00;
    P2M0 = 0x0F;
    P3M1 = 0x00;
    P3M0 = 0x01;
	P4M1 = 0x00;
    P4M0 = 0x00;
    P5M1 = 0x00;
    P5M0 = 0x00;
    P6M1 = 0x00;
    P6M0 = 0x00;
    P7M1 = 0x00;
    P7M0 = 0x00;
}
void initSerial() //for  data trans
{
	TMOD=0x20; //timer  T1 work_mode 2
	TL1=250; //
	TH1=250;
	TR1=1; //timer1 start
	PCON=0x80; //SMOD=1	
	SCON=0x50; //9600bit/s 
	TI=1;
}
void sendMode()//output data
{
	if(TI == 1)//output  ready??     a reg for interpret   is interpreted
	{
		if(Flag==1) //have receive the data?
		{
			SBUF = Mode;
			Flag = 0;
			TI = 0;
		}
	}
}
void receiveMove()//inpute data
{
	if(RI==1)//oh data is coming
	{
		Move = SBUF;
		Flag = 1;
		RI = 0;
	}
}
void startMove()
{
	switch(Move)
	{
		case 0x31:carGoStraight();break;//ascii for number 1  ...
		case 0x32:carGOLeft();break;
		case 0x33:carGoRight();break;
		case 0x34:carBackStraight();break;
		case 0x35:carBackLeft();break;
		case 0x36:carBackRight();break;
		default :break;
	}
}
void carStop()
{
	LEFT_BI = 0;
	LEFT_FI = 0;
	RIGHT_BI = 0;
	RIGHT_FI = 0;
}
void carGoStraight()
{
	LEFT_BI = 0;
	LEFT_FI = 1;
	RIGHT_BI = 1;
	RIGHT_FI = 0;
}
void carGOLeft()
{
	LEFT_BI = 1;
	LEFT_FI = 0;
	RIGHT_BI = 1;
	RIGHT_FI = 0;
}
void carGoRight()
{
	LEFT_BI = 0;
	LEFT_FI = 1;
	RIGHT_BI = 0;
	RIGHT_FI = 1;
}
void carBackStraight()
{
	LEFT_BI = 1;
	LEFT_FI = 0;
	RIGHT_BI = 1;
	RIGHT_FI = 0;
}
void carBackLeft()
{
	LEFT_BI = 0;
	LEFT_FI = 0;
	RIGHT_BI = 1;
	RIGHT_FI = 0;
}
void carBackRight()
{
	LEFT_BI = 1;
	LEFT_FI = 0;
	RIGHT_BI = 0;
	RIGHT_FI = 0;
}
void getLED1On()
{
	LED1 = 1;
}
void getLED2On()
{
	LED2 = 1;
}
void getLED1Off()
{
	LED1 = 0;
}
void getLED2Off()
{
	LED2 = 0;
}
void getBuzzerOn()
{
	BUZZER = 1;
}
void getBuzzerOff()
{
	BUZZER = 0;
}
unsigned char getMode()
{
	unsigned char Mode = 0x21 ;//!
	
	if(MODE1 == 0)
	{
		Mode = 0x41 ;//A
	}
	else if(MODE2 == 0)
	{
		Mode = 0x42 ;//B
	}
	else if(MODE3 == 0)
	{
		Mode = 0x43 ;//C
	}
	else if(MODE4 == 0)
	{
		Mode = 0x44 ;//D
	}
	else if(MODE5 == 0)
	{
		Mode = 0x45 ;//E
	}
	else if(MODE6 == 0)
	{
		Mode = 0x46 ;//F
	}
	return Mode;
}

void getWirelessInput()//wireless part
{
	
}
void getWirelessOutput()
{
	
}
void getDelay(int TIME_MS)		//@11.0592MHz
{
	unsigned char i, j;
	while(TIME_MS--)
	{
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
	
}



