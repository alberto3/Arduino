#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint8_t i_PinA, uint8_t i_PinB){
	m_BitA = digitalPinToBitMask(i_PinA);
	m_BitB = digitalPinToBitMask(i_PinB);
	m_InputAPort = portInputRegister(digitalPinToPort(i_PinA));
	m_InputBPort = portInputRegister(digitalPinToPort(i_PinB));
	m_Value = 0;
	OnTurnLeft = 0;
	OnTurnRight = 0;
}

void RotaryEncoder::Refresh(){
	m_Value <<= 2;
	
	if((*m_InputAPort & m_BitA) != 0)
	{
		m_Value |= 0x01;
	}
	
	if((*m_InputBPort & m_BitB) != 0)
	{
		m_Value |= 0x02;
	}
	
	switch(s_States[(m_Value & 0X0F)])
	{
		case ROTARY_ENCODER_CW:
			if(OnTurnRight)
			{
				OnTurnRight();
			}
			break;
		case ROTARY_ENCODER_CCW:
			if(OnTurnLeft)
			{
				OnTurnLeft();
			}
			break;
	}
}