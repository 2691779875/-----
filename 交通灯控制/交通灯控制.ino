/*
 Name:		交通灯控制.ino
 Created:	2017/3/29 9:49:04
 Author:	lzl
*/
#include <MsTimer2.h>
#include <EEPROM.h>
#include <SSD1306_text.h>
#include <Wire.h>
#define OLED_RESET A3
SSD1306_text display(OLED_RESET);
String SerialData0 = "";
String RX_RGYTime = "RGYTIM01NSG26_NSY24_NSTG19_NSTY17_WEG09_WEY07_WETG05_WETY02_SUM034";

String RGY_Flag="";
//String RX_RGYTime = "RC";

//***********************************************红绿灯************************************//
const int R_NS = 2;
const int G_NS = 3;
const int Y_NS = 4;

const int R_NS_T = 5;
const int G_NS_T = 6;
const int Y_NS_T = 7;

const int R_WE = 8;
const int G_WE = 9;
const int Y_WE = 10;

const int R_WE_T = A0;
const int G_WE_T = A1;
const int Y_WE_T = A2;
//***********************************************红绿灯************************************//
int RGY_time;
//int NS_G_TIME = 8, NS_Y_TIME = 2, NS_T_G_TIME = 5, NS_T_Y_TIME = 2, WE_G_TIME = 8, WE_Y_TIME = 2, WE_T_G_TIME = 5, WE_T_Y_TIME = 2,RGY_SUM_TIME;
//int NS_G_TIME = 26, NS_Y_TIME = 24, NS_T_G_TIME = 19, NS_T_Y_TIME =17, WE_G_TIME = 9, WE_Y_TIME = 7, WE_T_G_TIME = 2, WE_T_Y_TIME = 2, RGY_SUM_TIME;
int NS_G_TIME , NS_Y_TIME, NS_T_G_TIME , NS_T_Y_TIME, WE_G_TIME, WE_Y_TIME , WE_T_G_TIME, WE_T_Y_TIME , RGY_SUM_TIME;
String Str_NS_G_time = "";
String Str_NS_Y_time = "";
String Str_NS_T_G_time = "";
String Str_NS_T_Y_time = "";
String Str_WE_G_time = "";
String Str_WE_Y_time = "";
String Str_WE_T_G_time = "";
String Str_WE_T_Y_time = "";
String Str_RGY_time = "";

void LED_Init()
{
	pinMode(R_NS, OUTPUT);
	pinMode(G_NS, OUTPUT);
	pinMode(Y_NS, OUTPUT);
	pinMode(R_NS_T, OUTPUT);
	pinMode(G_NS_T, OUTPUT);
	pinMode(Y_NS_T, OUTPUT);
	pinMode(R_WE, OUTPUT);
	pinMode(G_WE, OUTPUT);
	pinMode(Y_WE, OUTPUT);
	pinMode(R_WE_T, OUTPUT);
	pinMode(G_WE_T, OUTPUT);
	pinMode(Y_WE_T, OUTPUT);
}
void RGY_ALL_LOW()
{
	digitalWrite(R_NS, LOW);
	digitalWrite(G_NS, LOW);
	digitalWrite(Y_NS, LOW);
	digitalWrite(R_NS_T, LOW);
	digitalWrite(G_NS_T, LOW);
	digitalWrite(Y_NS_T, LOW);
	digitalWrite(R_WE, LOW);
	digitalWrite(G_WE, LOW);
	digitalWrite(Y_WE, LOW);
	digitalWrite(R_WE_T, LOW);
	digitalWrite(G_WE_T, LOW);
	digitalWrite(Y_WE_T, LOW);

}
void NS()
{

	digitalWrite(R_NS, LOW);
	digitalWrite(Y_NS, LOW);
	digitalWrite(G_NS_T, LOW);
	digitalWrite(Y_NS_T, LOW);
	digitalWrite(G_WE, LOW);
	digitalWrite(Y_WE, LOW);
	digitalWrite(R_WE_T, LOW);
	digitalWrite(G_WE_T, LOW);
	digitalWrite(G_NS, HIGH);//南北绿灯亮，其他全红灯
	digitalWrite(R_NS_T, HIGH);
	digitalWrite(R_WE, HIGH);
	digitalWrite(R_WE_T, HIGH);
}
void NS_STOP_Yellow()
{
	digitalWrite(R_NS, LOW);
	digitalWrite(G_NS_T, LOW);
	digitalWrite(Y_NS_T, LOW);
	digitalWrite(G_WE, LOW);
	digitalWrite(Y_WE, LOW);
	digitalWrite(G_WE_T, LOW);
	digitalWrite(Y_WE_T, LOW);
	digitalWrite(G_NS, LOW);//南北绿灯灭，黄灯亮
	digitalWrite(Y_NS, HIGH);
	digitalWrite(R_NS_T, HIGH);
	digitalWrite(R_WE, HIGH);
	digitalWrite(R_WE_T, HIGH);
}
void NS_T()
{

	digitalWrite(G_NS, LOW);
	digitalWrite(Y_NS, LOW);
	digitalWrite(R_NS_T, LOW);
	digitalWrite(Y_NS_T, LOW);
	digitalWrite(G_WE, LOW);
	digitalWrite(Y_WE, LOW);
	digitalWrite(G_WE_T, LOW);
	digitalWrite(Y_WE_T, LOW);
	digitalWrite(G_NS_T, HIGH);//南北转弯绿灯亮，其他全红灯
	digitalWrite(R_NS, HIGH);
	digitalWrite(R_WE, HIGH);
	digitalWrite(R_WE_T, HIGH);
}
void NS_T_STOP_Yellow()
{
	
	digitalWrite(G_NS, LOW);
	digitalWrite(Y_NS, LOW);
	digitalWrite(R_NS_T, LOW);
	digitalWrite(G_WE, LOW);
	digitalWrite(Y_WE, LOW);
	digitalWrite(G_WE_T, LOW);
	digitalWrite(Y_WE_T, LOW);
	digitalWrite(G_NS_T, LOW);//南北转弯绿灯灭，黄灯亮
	digitalWrite(Y_NS_T, HIGH);
	digitalWrite(R_NS, HIGH);
	digitalWrite(R_WE, HIGH);
	digitalWrite(R_WE_T, HIGH);
}
void WE()
{
	
	digitalWrite(G_NS, LOW);
	digitalWrite(Y_NS, LOW);
	digitalWrite(G_NS_T, LOW);
	digitalWrite(Y_NS_T, LOW);
	digitalWrite(R_WE, LOW);
	digitalWrite(Y_WE, LOW);
	digitalWrite(G_WE_T, LOW);
	digitalWrite(Y_WE_T, LOW);

	digitalWrite(G_WE, HIGH);//东西绿灯亮，其他全红灯
	digitalWrite(R_NS, HIGH);
	digitalWrite(R_NS_T, HIGH);
	digitalWrite(R_WE_T, HIGH);
}
void WE_STOP_Yellow()
{

	digitalWrite(G_NS, LOW);
	digitalWrite(Y_NS, LOW);
	digitalWrite(G_NS_T, LOW);
	digitalWrite(Y_NS_T, LOW);
	digitalWrite(R_WE, LOW);
	digitalWrite(G_WE_T, LOW);
	digitalWrite(Y_WE_T, LOW);

	digitalWrite(G_WE, LOW);//东西绿灯灭，黄灯亮
	digitalWrite(Y_WE, HIGH);
	digitalWrite(R_NS, HIGH);
	digitalWrite(R_NS_T, HIGH);
	digitalWrite(R_WE_T, HIGH);
}
void WE_T()
{

	digitalWrite(G_NS, LOW);
	digitalWrite(Y_NS, LOW);

	digitalWrite(G_NS_T, LOW);
	digitalWrite(Y_NS_T, LOW);

	digitalWrite(G_WE, LOW);
	digitalWrite(Y_WE, LOW);
	digitalWrite(R_WE_T, LOW);

	digitalWrite(Y_WE_T, LOW);

	digitalWrite(R_NS, HIGH);
	digitalWrite(R_NS_T, HIGH);
	digitalWrite(R_WE, HIGH);
	digitalWrite(G_WE_T, HIGH);//东西转弯绿灯亮，其他全红灯
}
void WE_T_STOP_Yellow()
{
	digitalWrite(R_NS, LOW);
	digitalWrite(G_NS, LOW);
	digitalWrite(Y_NS, LOW);
	digitalWrite(R_NS_T, LOW);
	digitalWrite(G_NS_T, LOW);
	digitalWrite(Y_NS_T, LOW);
	digitalWrite(R_WE, LOW);
	digitalWrite(G_WE, LOW);
	digitalWrite(Y_WE, LOW);
	digitalWrite(R_WE_T, LOW);


	digitalWrite(G_WE_T, LOW);//东西转弯绿灯灭，黄灯亮
	digitalWrite(Y_WE_T, HIGH);//
}
void Read_Time()
{
	NS_G_TIME = EEPROM.read(1);
	NS_Y_TIME = EEPROM.read(2);
	NS_T_G_TIME = EEPROM.read(3);
	NS_T_Y_TIME = EEPROM.read(4);
	WE_G_TIME = EEPROM.read(5);
	WE_Y_TIME = EEPROM.read(6);
	WE_T_G_TIME = EEPROM.read(7);
	WE_T_Y_TIME = EEPROM.read(8);
	RGY_SUM_TIME = EEPROM.read(9);
	RGY_time = RGY_SUM_TIME;
} 
void setup() 
{
	LED_Init();
	Read_Time();
	Serial.begin(115200);
	MsTimer2::set(1000, flash);
	MsTimer2::start();
}
void flash()
{
	if (RGY_time == 0)
	{
		RGY_time = RGY_SUM_TIME;
	}
	RGY_time--;
	Serial.print(RGY_Flag+": ");
	Serial.println(RGY_time);
}

void loop() 
{

	while (Serial.available() > 0)
	{
		SerialData0 += char(Serial.read());
		delay(2);
	}

	
	if (SerialData0.substring(0, 8) == RX_RGYTime.substring(0, 8))
	{	

		Str_NS_G_time = SerialData0.substring(11, 13);
		Str_NS_Y_time = SerialData0.substring(17, 19);
		Str_NS_T_G_time = SerialData0.substring(24, 26);
		Str_NS_T_Y_time = SerialData0.substring(31, 33);
		Str_WE_G_time = SerialData0.substring(37, 39);
		Str_WE_Y_time = SerialData0.substring(43, 45);
		Str_WE_T_G_time = SerialData0.substring(50, 52);
		Str_WE_T_Y_time = SerialData0.substring(57, 59);
		Str_RGY_time = SerialData0.substring(63, 66);

		NS_G_TIME= Str_NS_G_time.toInt();
		NS_Y_TIME = Str_NS_Y_time.toInt();
		NS_T_G_TIME = Str_NS_T_G_time.toInt();
		NS_T_Y_TIME = Str_NS_T_Y_time.toInt();
		WE_G_TIME = Str_WE_G_time.toInt();
		WE_Y_TIME = Str_WE_Y_time.toInt();
		WE_T_G_TIME = Str_WE_T_G_time.toInt();
		WE_T_Y_TIME = Str_WE_T_Y_time.toInt();
		RGY_SUM_TIME = Str_RGY_time.toInt();

		EEPROM.write(1, NS_G_TIME);
		EEPROM.write(2, NS_Y_TIME);
		EEPROM.write(3, NS_T_G_TIME);
		EEPROM.write(4, NS_T_Y_TIME);
		EEPROM.write(5, WE_G_TIME);
		EEPROM.write(6, WE_Y_TIME);
		EEPROM.write(7, WE_T_G_TIME);
		EEPROM.write(8, WE_T_Y_TIME);
		EEPROM.write(9, RGY_SUM_TIME);

		Serial.print("SetSucessful");
		SerialData0 = "";
	}
	if (RGY_time > NS_G_TIME)  //NS G
	{
		NS();
		RGY_Flag = "南北_绿灯";
	}
	if (RGY_time <= NS_G_TIME && RGY_time > NS_Y_TIME)  //NS Y
	{
		NS_STOP_Yellow();
		RGY_Flag = "南北_黄灯";
	}
	if (RGY_time <= NS_Y_TIME && RGY_time > NS_T_G_TIME) //NS_T G
	{
		NS_T();
		RGY_Flag = "南北转弯绿灯";
	}
	if (RGY_time <= NS_T_G_TIME && RGY_time > NS_T_Y_TIME) //NS_T Y
	{
		NS_T_STOP_Yellow();
		RGY_Flag = "南北转弯黄灯灯";
	}
	if (RGY_time <= NS_T_Y_TIME && RGY_time > WE_G_TIME)//WE_G
	{
		WE();
		RGY_Flag = "东西绿灯";
	}
	if (RGY_time <= WE_G_TIME && RGY_time > WE_Y_TIME)//WE_Y
	{
		WE_STOP_Yellow();
		RGY_Flag = "东西黄灯";
	}
	if (RGY_time <= WE_Y_TIME && RGY_time > WE_T_G_TIME)//WE_T_G
	{
		WE_T();
		RGY_Flag = "东西转弯绿灯";
	}
	if (RGY_time <= WE_T_G_TIME && RGY_time > WE_T_Y_TIME)//WE_T_Y
	{
		WE_STOP_Yellow();
		RGY_Flag = "东西转弯黄灯";
	}


}
