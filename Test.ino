/*!
  @file     TM1638plus_TEST_Model1.ino
  @author   Gavin Lyons
  @brief
     demo file library for  TM1638 module(LED & KEY). Model 1
  @note
      Carries out series of tests to demo arduino library TM1638plus.

    TESTS:

  0.   TEST 0 Reset
  1.   TEST 1 Brightness
  2.   TEST 2 ASCII display
  3.   TEST 3 Set a single segment
  4.   TEST 4 Hex digits
  5.   TEST 5 Text String with Decimal point
  6.   TEST 6 TEXT + ASCII combo
  7.   TEST 7 Integer Decimal number
  8.   TEST 8 Text String + Float
  9.   TEST 9 Text String + decimal number
  10. TEST 10 Multiple dots
  11. TEST 11 Display Overflow
  12. TEST 12 Scrolling text
  13. TEST 13 setLED and setLEDs method
  14. TEST 14 Buttons + LEDS
*/

#include <TM1640plus.h>

// GPIO I/O pins on the Arduino connected to strobe, clock, data,
//pick on any I/O you want.
#define  STROBE_TM 4 // strobe = GPIO connected to strobe line of module
#define  CLOCK_TM 5 // clock = GPIO connected to clock line of module
#define  DIO_TM 6 // data = GPIO connected to data line of module
bool high_freq = false; //default false,, If using a high freq CPU > ~100 MHZ set to true.

//Constructor object (GPIO STB , GPIO CLOCK , GPIO DIO, use high freq MCU)
TM1640plus tm( CLOCK_TM , DIO_TM);


// Some vars and defines for the tests.
#define myTestDelay  5000
#define myTestDelay1 1000
#define myTestDelay3 3000

void setup()
{
//  Serialinit();
  tm.displayBegin();
  delay(myTestDelay1);

  //Test 0 reset
  Test0();
}

void loop()
{
    Test1();  // Brightness
    Test2();  // ASCII display
    Test3();  // Set a single segment in each digit
    Test4();  // Hex digits
    Test5();  // Text String with Decimal point
    Test6();  // TEXT + ASCII combo
    Test7();  // Integer Decimal number
    Test8();  // Text String + Float hack
    Test9();  // Text String + decimal number
    Test10();  // Multiple Decimal points
    Test11();  // Display Overflow
    Test12();  // Scrolling text
//    Test13();  // setLED and setLEDs
   // Test14();  // Buttons + LEDS
}

void Test0()
{
  // Test 0 reset test
//  tm.setLED(0, 1);
  delay(myTestDelay);
  tm.reset();
}

void Test1() {
  // Test 1  Brightness and reset
  for (uint8_t brightness = 0; brightness < 8; brightness++)
  {
    tm.brightness(brightness);
    tm.displayText("00000000");
    delay(myTestDelay1);
  }
  tm.reset();
  // restore default brightness
  tm.brightness(0x02);
}

void Test2() {
  //Test 2 ASCII , display 2.341

  tm.displayASCIIwDot(0, '2');
  tm.displayASCII(1, '3');
  tm.displayASCII(2, '4');
  tm.displayASCII(3, '1');
  delay(myTestDelay3);
  tm.reset();
}

void Test3() {
  //TEST 3 single segment (digit position, (dp)gfedcba)
  // (dp)gfedcba =  seven segments positions
  uint8_t pos = 0;
  for (pos = 0 ; pos<8 ; pos++)
  {
    tm.display7Seg(pos, 1<<7-pos); // Displays a single seg in (dp)gfedcba) in each  pos 0-7
    delay(myTestDelay1);
  }
}

void Test4() {
  // Test 4 Hex digits.
  tm.displayHex(0, 0);
  tm.displayHex(1, 1);
  tm.displayHex(2, 2);
  tm.displayHex(3, 3);
  tm.displayHex(4, 4);
  tm.displayHex(5, 5);
  tm.displayHex(6, 6);
  tm.displayHex(7, 7);
  delay(myTestDelay3); // display 01234567

  tm.displayHex(0, 8);
  tm.displayHex(1, 9);
  tm.displayHex(2, 0x0A);
  tm.displayHex(3, 0x0B);
  tm.displayHex(4, 0x0C);
  tm.displayHex(5, 0x0D);
  tm.displayHex(6, 0x0E);
  tm.displayHex(7, 0x0F);
  delay(myTestDelay3); // display 89ABCDEF
  tm.reset();

  tm.displayHex(1, 0xFFFE);
  tm.displayHex(7, 0x10);
  delay(myTestDelay3); // display " E      0"

}

void Test5() {
  // Test 5 TEXT  with dec point
  // abcdefgh with decimal point for c and d
  tm.displayText("abc.d.efgh");
  delay(myTestDelay);
}

void Test6() {
  // Test6  TEXT + ASCII combo
  // ADC=.2.948
  char text1[] = "ADC=.";
  tm.displayText(text1);
  tm.displayASCIIwDot(4, '2');
  tm.displayASCII(5, '9');
  tm.displayASCII(6, '4');
  tm.displayASCII(7, '8');
  delay(myTestDelay);
  tm.reset();
}

void Test7() {
  // TEST 7a Integer left aligned , NO leading zeros
  tm.displayIntNum(45, false, TMAlignTextLeft); // "45      "
  delay(myTestDelay);
  // TEST 7b Integer left aligned , leading zeros
  tm.displayIntNum(99991, true, TMAlignTextLeft); // "00099991"
  delay(myTestDelay);
  tm.reset();
  // TEST 7c Integer right aligned , NO leading zeros
  tm.displayIntNum(35, false, TMAlignTextRight); // "      35"
  delay(myTestDelay);
  // TEST 7d Integer right aligned , leading zeros
  tm.displayIntNum(9983551, true, TMAlignTextRight); // "09983551"
  delay(myTestDelay);

  // TEST 7e tm.DisplayDecNumNIbble left aligned
  tm.DisplayDecNumNibble(134, 70, false, TMAlignTextLeft); // "134 " "70" , left aligned, NO leading zeros
  delay(myTestDelay);
  tm.DisplayDecNumNibble(23, 662, true, TMAlignTextLeft); // "0023" "0662" , left aligned , leading zeros
  delay(myTestDelay);
  tm.reset();

  // TEST 7f tm.DisplayDecNumNIbble right aligned
  tm.DisplayDecNumNibble(43, 991, false, TMAlignTextRight); // "  43" " 991" , right aligned, NO leading zeros
  delay(myTestDelay);
  tm.DisplayDecNumNibble(53, 8, true, TMAlignTextRight); // "0053" "0008" , right aligned , leading zeros
  delay(myTestDelay);

}

void Test8() {
  // TEST 8  TEXT STRING + integer SSSSIIII
  char workStr[11];
  uint16_t  data = 234;
  sprintf(workStr, "ADC=.%04d", data); // "ADC=.0234"
  tm.displayText(workStr);
  delay(myTestDelay3);
}

void Test9() {
  // TEST 9 Text String + Float  SSSSFFFF ,  just one possible method.
  float voltage = 12.45;
  uint16_t temp = 0;
  char workStr[11];
  uint8_t  digit1, digit2, digit3 , digit4;
  voltage =  voltage * 100; // 1245
  temp = (uint16_t)voltage;
  digit1 = (temp / 1000) % 10;
  digit2 = (temp / 100) % 10;
  digit3 = (temp / 10) % 10;
  digit4 =  temp % 10;

  sprintf(workStr, "ADC=.%d%d.%d%d", digit1, digit2, digit3, digit4);
  tm.displayText(workStr); //ADC=.12.45
  delay(myTestDelay3);
  tm.reset();
}

void Test10()
{
  //TEST 10 Multiple dots test
  tm.displayText("Hello...");
  delay(myTestDelay);
  tm.displayText("...---..."); //SOS in morse
  delay(myTestDelay);
}

void Test11()
{
  //TEST11 user overflow
  tm.displayText("1234567890abc"); //should display just 12345678
  delay(myTestDelay3);
  tm.reset();
}


void Test12() {
  //TEST 12 scrolling text, just one possible method.
  char textScroll[17] = " Hello world 123";
  unsigned long previousMillis_display = 0;  // will store last time display was updated
  const long interval_display = 1000;            //   interval at which to update display (milliseconds)

  while(1)
  {
  tm.displayText(textScroll);
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis_display >= interval_display)
  {
    previousMillis_display = currentMillis;
    if (strlen(textScroll) > 0)
    {
      memmove(textScroll, textScroll+1, strlen(textScroll));
      tm.displayText("        "); //Clear display or last character will drag across screen
    }else
    {
      return;
    }
   }
  }
}
