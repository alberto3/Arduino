#include <RotaryEncoder.h>

#define ROTARY_ENCODER_PIN_A 1
#define ROTARY_ENCODER_PIN_A 2

RotaryEncoder encoder(ROTARY_ENCODER_PIN_A, ROTARY_ENCODER_PIN_B);

void setup()
{
	encoder.OnTurnRight = encoder_OnTurnRight;
	encoder.OnTurnLeft = encoder_OnTurnLeft;
	
	pinMode(ROTARY_ENCODER_PIN_A, INPUT);
	pinMode(ROTARY_ENCODER_PIN_B, INPUT);
	
	digitalWrite(ROTARY_ENCODER_PIN_A, HIGH);
	digitalWrite(ROTARY_ENCODER_PIN_B, HIGH);
	
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
}

void loop()
{
	encoder.Refresh();
}

void encoder_OnTurnRight(){digitalWrite(3, HIGH);delay(20);igitalWrite(3, LOW);}
void encoder_OnTurnLeft(){digitalWrite(4, HIGH);delay(20);igitalWrite(4, LOW);}