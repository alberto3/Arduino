#include <avr/interrupt.h>
#include <Button.h>
#include <IRReceiver.h>

// BLINK LED
#define LED_PIN 10

// TSOP4838 Pin
#define IR_PIN 2

IRReceiver irReceiver(IR_PIN);

void setup()
{
	pinMode(LED_PIN, OUTPUT);
	
	attachInterrupt(0, SIGNAL_IR, FALLING); // pin 2 = external interupt #0
}

void loop()
{
}

void SIGNAL_IR(){
	uint8_t oldSREG = SREG;
	cli();
	handleIRInterrupt();
	SREG = oldSREG;
}

void handleIRInterrupt(){
	unsigned long irCode;
	
	irCode = irReceiver.GetCode();
	
	if (irCode > 0)
	{
		switch(irCode){
			case 0x1000405: // Volume Up
				blink();
				
				break;
				
			case 0x1008485: // Volume Down
				blink();
				
				break;
				
			case 0x1004C4D: // Mute/Unmute
				blink();
				
				break;
				
			case 0x100A0A1: // Input selector
				blink();
				
				break;
				
			case 0x1009C9D: // Info
				blink();
				
				break;
		}
	}
}

void blink(){
	digitalWrite(LED_PIN, HIGH);
	delay(5);
	digitalWrite(LED_PIN, LOW);
}