/**
 * @name:			RotaryEncoder.h
 * @description:	Rotary Encoder class
 * @author:			Albert Harounian
 * @since:			March 25, 2013
 */
 
#ifndef __ROTARYENCODER_H__
#define __ROTARYENCODER_H__

#include <Arduino.h>

#define ROTARY_ENCODER_NOOP 0
#define ROTARY_ENCODER_CW 1
#define ROTARY_ENCODER_CCW 2

class RotaryEncoder{
public:	
	
	void (*OnTurnRight)();
	void (*OnTurnLeft)();
	
	RotaryEncoder(uint8_t i_PinA, uint8_t i_PinB);
	void Refresh();
	
private:
	
	uint8_t m_Value;
	uint8_t m_BitA;
	uint8_t m_BitB;
	volatile uint8_t* m_InputAPort;
	volatile uint8_t* m_InputBPort;
	
	static const uint8_t const s_States =  {
		ROTARY_ENCODER_NOOP,
		ROTARY_ENCODER_CCW,
		ROTARY_ENCODER_CW,
		ROTARY_ENCODER_NOOP,
		ROTARY_ENCODER_CW,
		ROTARY_ENCODER_NOOP,
		ROTARY_ENCODER_NOOP,
		ROTARY_ENCODER_CCW,
		ROTARY_ENCODER_CCW,
		ROTARY_ENCODER_NOOP,
		ROTARY_ENCODER_NOOP,
		ROTARY_ENCODER_CW,
		ROTARY_ENCODER_NOOP,
		ROTARY_ENCODER_CW,
		ROTARY_ENCODER_CCW,
		ROTARY_ENCODER_NOOP
	};
};

#endif
