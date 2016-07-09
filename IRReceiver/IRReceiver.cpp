#include "IRReceiver.h"

IRReceiver::IRReceiver(uint8_t i_Pin){
	m_Bit = digitalPinToBitMask(i_Pin);
	m_InputPort = portInputRegister(digitalPinToPort(i_Pin));
}

unsigned long IRReceiver::GetCode(){
	unsigned long result = 0;
	
	while (1)
	{
		uint16_t high, low;
		high = low = 0;
		
		while ( (*m_InputPort & m_Bit) == 0 )
		{
			high++;
			_delay_us(IR_SAMPLE_RESOLUTION);
		}
		
		while ( (*m_InputPort & m_Bit) != 0)
		{
			low++;
			_delay_us(IR_SAMPLE_RESOLUTION);
			
			// If the pulse is too long, we backed to idle status - return result
			if (low >= IR_MAX_PULSE_LENGTH) {
				result >>= 1; // omit the last bit
				return result;
			}
		}		
		
		// for other protocols: http://www.sbprojects.com/knowledge/ir/index.php
		decodePanasonic(high, low, &result);
		
		result <<= 1;
	}
}

void IRReceiver::decodePanasonic(uint16_t i_HighPulse, uint16_t i_LowPulse, unsigned long* o_Result){
	// decodes for Panasonic/Sharp protocol: 320us of high pulse followed by 1680us of low pulse is logic 1, 320us followed by 680us is logic 0
	// so just check whether the low pulse is greater than 1ms
	if (i_LowPulse > 1000 / IR_SAMPLE_RESOLUTION)
	{
		*o_Result |= 1;
	}
}