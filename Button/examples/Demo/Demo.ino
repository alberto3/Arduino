#include <Button.h>

Button buttonTest;

void setup()
{
	buttonTest.OnPress = buttonTest_OnPress;
	buttonTest.OnRelease = buttonTest_OnRelease;
	buttonTest.OnClick = buttonTest_OnClick;
	buttonTest.OnDoubleClick = buttonTest_OnDblClick;
	buttonTest.OnLongPress = buttonTest_OnLongPress;
	buttonTest.OnLongRelease = buttonTest_OnLongRelease;
	
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
}

void loop()
{
	buttonTest.SetState(digitalRead(8) == HIGH ? Button::high : Button::low);
}

void buttonTest_OnPress(){digitalWrite(2, HIGH);}
void buttonTest_OnRelease(){digitalWrite(3, HIGH);}
void buttonTest_OnLongPress(){digitalWrite(4, HIGH);}
void buttonTest_OnLongRelease(){digitalWrite(5, HIGH);}
void buttonTest_OnClick(){digitalWrite(6, HIGH);}
void buttonTest_OnDblClick(){digitalWrite(7, HIGH);}