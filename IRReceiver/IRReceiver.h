/**
 * @name:			IRReceiver.h
 * @description:	Infrared Receiver Class For TSOPxxxx
 * @author:			Albert Harounian
 * @since:			March 13, 2013
 */
 
#ifndef __IRREIVER_H__
#define __IRREIVER_H__

#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <Arduino.h>

#define IR_MAX_PULSE_LENGTH 400
#define IR_SAMPLE_RESOLUTION 20

class IRReceiver{
public:	

	IRReceiver(uint8_t i_Pin);
	unsigned long GetCode();
	
private:
	
	uint8_t m_Bit;
	volatile uint8_t* m_InputPort;
	
	void decodePanasonic(uint16_t i_HighPulse, uint16_t i_LowPulse, unsigned long* o_Result);
};

#endif
