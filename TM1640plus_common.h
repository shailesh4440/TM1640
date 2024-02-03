/*!
	@file     TM1638plus_common.h
	@author   Gavin Lyons
	@brief    Arduino library Tm1638plus, Header  file for common data and functions between model classes. 

	@note  See URL for full details. https://github.com/gavinlyonsrepo/TM1638plus
*/

#ifndef TM1640PLUS_COMMON_H
#define TM1640PLUS_COMMON_H

#if (ARDUINO >=100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define TM_ACTIVATE 0x8F /**<  Start up device */
#define TM_BUTTONS_MODE 0x42 /**<  Buttons mode */
#define TM_WRITE_LOC 0x44 /**<  Write to a memory location */
#define TM_WRITE_INC 0x40 /**<  Incremental write */
#define TM_SEG_ADR 0xC0  /**<  leftmost segment Address C0 C2 C4 C6 C8 CA CC CE */
#define TM_LEDS_ADR 0xC1  /**<  Leftmost LED address C1 C3 C5 C7 C9 CB CD CF */
#define TM_BRIGHT_ADR 0x88 /**<  Brightness address */
#define TM_BRIGHT_MASK 0x07 /**<  Brightness mask  */
#define TM_DEFAULT_BRIGHTNESS 0x02 /**< Brightness can be 0x00 to 0x07 , 0x00 is least bright */
#define TM_DISPLAY_SIZE 16 /**< Size of display in digits */

#define TM_ASCII_OFFSET 32 /**<  ASCII table offset to jump over first missing 32 chars */
#define TM_HEX_OFFSET   16 /**<  ASCII table offset to reach the number position */
#define TM_DOT_MASK_DEC    128 /**<  0x80 Mask to  switch on decimal point in seven segement  */



/*! Alignment of text on display */
typedef enum : uint8_t
{
	TMAlignTextRight = 1,   /**< Align text to the right on  display */
	TMAlignTextLeft = 2      /**< Align text to the left  on  display */
}AlignTextType_e; 

extern const unsigned char * pFontSevenSegptr; /**<  Pointer to the seven segment font data table */

/*!
	@brief  The base Class , used to store common data & functions for all models types.
*/
class TM1640plus_common{

public:

	TM1640plus_common();
	void displayBegin();	 
	void reset(void);  
	void brightness(uint8_t brightness);

protected:

	
	void sendCommand(uint8_t value);
	void sendData(uint8_t data);
	
	uint8_t _DATA_IO;    /**<  GPIO connected to DIO on Tm1640  */
	uint8_t _CLOCK_IO; /**<  GPIO connected to CLk on Tm1640  */
	
	
private:

};

#endif
