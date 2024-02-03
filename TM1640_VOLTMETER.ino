
#include "TM1640plus.h" // By Author 
#include <EEPROM.h>
//#define  CLOCK_TM 6
//#define  DIO_TM 7
//*******************************************************************************************************************************
int key = 0;
int keyOld = 0;
int keySpeed = 0;
#define BUTTON_1        2
#define BUTTON_2        3
#define BUTTON_3        4
#define channel1        8
byte dataDirection = 0;
byte wait = 1000;
unsigned long now;
const int timerMenu = 5000;
char displayBuffer[12];
float tes; // desired temperature
byte tset1, tset2; // value for read from EEPROM
byte tset01, tset02; // value for record in EEPROM
int tes0; // value use for record in EEPROM

byte ch1 = 100, ch2 = 400, ch3 = 300, ch4 = 500;
byte prag = 0;
//*******************************************************************************************
void klav() {
  key = 0;
  if (digitalRead(BUTTON_1) == LOW) key = 1;
  if (digitalRead(BUTTON_2) == LOW) key = 2;
  if (digitalRead(BUTTON_3) == LOW) key = 3;

  if (key != 0) {
    delay(keySpeed < 8 ? 200 : 20);
    keySpeed++;
  }
  if (key != keyOld) keySpeed = 0;
  keyOld = key;
}
//*********************************************************************************************

int analogInput = 0;
int analogInput1 = 1;
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // resistance of R1 (100K) -see text!
float R2 = 10000.0; // resistance of R2 (10K) - see text!
int value = 0;
int value2 = 0;
float vout1 = 0.0;
float vin1 = 0.0;

//Vars to read ADC on interval to provide data to display
unsigned long previousMillis = 0;        // will store last time ADC was updated
const long interval = 1000;           // interval at which to read ADC (milliseconds)

uint16_t ADC_Value = 0;  // variable to store the value coming from the ADC
uint16_t ADC_Value1 = 0;  // variable to store the value coming from the ADC
TM1640plus TM1640(5,6); // clock,data

void setup() {

  //Tm1638 Setup
  TM1640.displayBegin();
  TM1640.brightness(6);
  digitalWrite(BUTTON_1, HIGH);
  digitalWrite(BUTTON_2, HIGH);
  digitalWrite(BUTTON_3, HIGH);
  ch1 = EEPROM.read(100);
  ch2 = EEPROM.read(101);
  ch3 = EEPROM.read(102);
  ch4 = EEPROM.read(103);
  EEPROM.write(100, ch1);
  EEPROM.write(101, ch2);
  EEPROM.write(102, ch3);
  EEPROM.write(103, ch4);
  pinMode(channel1, OUTPUT);
  digitalWrite(channel1, LOW);
TM1640.displayText("testing123" );
delay(1000);

}
void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    ADC_Value = analogRead(A0) / 2;
    ADC_Value = map(ADC_Value, 0, 1024, 0, 999);
    ADC_Value1 = analogRead(A1) / 2;
    ADC_Value1 = map(ADC_Value1, 0, 1024, 0, 999);

  }
 
ModelTwoADC();
  klav();
  if (key == 1) {
    delay(500);
    setting(); //set the time
  }
  if (ADC_Value / 2  > ch1)
  {
    digitalWrite(channel1, HIGH);
  }
  else
    digitalWrite(channel1, LOW);
}

void ModelTwoADC()
{
  char workstr[10];
 sprintf(workstr,"%d%d.%dV%d%d.%dA", (ADC_Value / 100) % 10, (ADC_Value / 10) % 10,  ADC_Value % 10, (ADC_Value1 / 100) % 10, (ADC_Value1 / 10) % 10,  ADC_Value1 % 10 );

TM1640.displayText(workstr);
 //TM1638.displayText("testing123" );
delay(500);
}


void setting() {
  klav();
  now = millis();
  while (millis() - now < timerMenu) {

    TM1640.displayText(displayBuffer );
    switch (dataDirection) {
      case 0:
        sprintf(displayBuffer, "CH1HI--");
        break;
      case 1:
        sprintf(displayBuffer, "ch1%d%d.%d", (ch1 / 100) % 10, (ch1 / 10) % 10, ch1 % 10);  EEPROM.write(100, ch1);
        break;
      case 2:
        sprintf(displayBuffer, "CH1LO-" );
        break;
      case 3:
        sprintf(displayBuffer, "ch1%d%d.%d", (ch2 / 100) % 10, (ch2 / 10) % 10, ch2 % 10); EEPROM.write(101, ch2);
        break;
      case 4:
        sprintf(displayBuffer, "CH2HI--");
        break;
      case 5:
        sprintf(displayBuffer, "ch2%d%d.%d", (ch3 / 100) % 10, (ch3 / 10) % 10, ch3 % 10); EEPROM.write(102, ch3);
        break;
      case 6:
        sprintf(displayBuffer, "CH2LO-");
        break;
      case 7:
        sprintf(displayBuffer, "ch2%d%d.%d", (ch4 / 100) % 10, (ch4 / 10) % 10, ch4 % 10); EEPROM.write(103, ch4);
        break;
    }

    switch (dataDirection) {
      case 0:

        break;
      case 1:
        if (key == 2) {

          ch1 = ch1 + 1;
          delay(wait);
          // if (tes < 5.0) tes = 5.0;  // limit for minimum set value
          now = millis();
        }
        if (key == 3) {
          ch1 = ch1 - 1;
          delay(wait);
          // if (ch1 >= 255) {
          //  ch1= 999;
          // }
          now = millis();
        }
        break;
      case 2: {
          break;
        }
      case 3:
        if (key == 2) {
          ch2++;
          delay(wait);
          if (ch2 >= 999) {
            ch2++;
            ch2 = 000;
          }
          now = millis();
        }
        if (key == 3) {
          ch2--;
          delay(wait);
          if (ch2 >= 255) {
            ch2 = 999;
            ch2--;
          }
          now = millis();
        }
        break;
      case 4: {
          break;
        }
      case 5:// Date
        if (key == 2) {
          ch3++;
          delay(wait);
          if (ch3 >= 999) {
            ch3 = 000;
          }
          now = millis();
        }
        if (key == 3) {
          ch3--;
          delay(wait);
          if (ch3 <= 0) {
            ch3 = 999;
          }
          now = millis();
        }
        break;
      case 6: {
          break;
        }
      case 7:  // month
        if (key == 2) {
          ch4++;
          delay(wait);
          if (ch4 >= 999) {
            ch4 = 000;
          }
          now = millis();
        }
        if (key == 3) {
          ch4--;
          delay(wait);
          if (ch4 <= 0 ) { // 252 253 254 255 0 1 2 3
            ch4 = 100;
          }
          now = millis();
        }
        break;



    }
    klav();
    if (key == 1) {
      delay(wait);
      dataDirection++;
      if (dataDirection >= 8) {
        dataDirection = 0;
        TM1640.displayText(" SAUE ");
        delay(500);
      //  return (true);
         return ;
      }
      now = millis();
    }


  }

}

/*
    char timebuf[11];
    char workstr[12];
   value = analogRead(analogInput);
   vout = (value * 5.0) / 1024.0; // see text
   vin = vout / (R2/(R1+R2));
   if (vin<0.09) {
   vin=0.0;//statement to quash undesired reading !
   }
   value2 = analogRead(analogInput1);
   vout1 = (value2 * 5.0) / 1024.0; // see text
   vin1 = vout1 / (R2/(R1+R2));
   if (vin1<0.09) {
   vin1=0.0;//statement to quash undesired reading !
   }

  //unsigned int len = sizeof(vin);
  //len = len +2;
  uint16_t Temp = vin*10; //value/2;
  uint16_t Temp1 = vin1*10;//value2/2;
  sprintf(workstr,"%d%d.%d%d%d.%d", (Temp / 100) % 10, (Temp / 10) % 10,  Temp % 10,(Temp1 / 100) % 10, (Temp1 / 10) % 10,  Temp1 % 10 );
  TM1638.displayText(workstr);

  delay(1000);

  }
*/



//===============================================================END=================================================
