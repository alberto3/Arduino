#include "Button.h"

uint8_t Button::m_ClickTimeout = BUTTON_DEFAULT_CLICK_TIMEOUT;
uint16_t Button::m_PressTimeout = BUTTON_DEFAULT_LONG_PRESS_TIMEOUT;

Button::Button(){
	init(down);
}

Button::Button(ePullType i_PullType){
	init(i_PullType);
}

void Button::init(ePullType i_PullType){
	if(i_PullType == up){
		m_Status |= BUTTON_IS_PULL_UP;
	}
	OnPress = OnLongPress = OnRelease = OnLongRelease = OnClick = OnDoubleClick = NULL;
	reset();
}

bool Button::IsActivated(){
	return (m_Status & BUTTON_IS_ACTIVE) != 0;
}

void Button::SetState(eState i_State){
	// Raising
	if((m_Status & BUTTON_IS_HIGH_STATE) == 0 && i_State == high){
		if((m_Status & BUTTON_IS_PULL_UP) == 0){
			// pressed
			pressed();
		}else{
			// released
			released();
		}
		m_Status |= BUTTON_IS_HIGH_STATE;
	}
	// Falling
	else if((m_Status & BUTTON_IS_HIGH_STATE) != 0 && i_State == low){
		if((m_Status & BUTTON_IS_PULL_UP) == 0){
			// released
			released();
		}else{
			// pressed
			pressed();
		}
		m_Status &= ~BUTTON_IS_HIGH_STATE;
	}
	refresh();
}

void Button::Refresh(){
	refresh();
}

void Button::pressed(){
	m_Status |= BUTTON_IS_PRESSED;
	// This is the first time button pushed
	if((m_Status & BUTTON_IS_ACTIVE) == 0){
		m_Status |= BUTTON_IS_ACTIVE;
		m_StartTime = millis();
	}
	if(OnPress != 0){
		OnPress();
	}
}

void Button::released(){
	if(millis() - m_StartTime > m_PressTimeout){
		if(OnLongRelease != 0){
			OnLongRelease();
		}
		reset();
	}
	else{
		if(OnRelease != 0){
			OnRelease();
		}
		m_Status++;// (m_Status & ~BUTTON_HIT_COUNT) | ((m_Status & BUTTON_HIT_COUNT) + 1);
		m_Status &= ~BUTTON_IS_PRESSED;
	}
}

void Button::refresh(){
	unsigned long time = millis();
	if((m_Status & BUTTON_IS_ACTIVE) != 0){
		if(time - m_StartTime >= m_PressTimeout){
			longPressTimedOut();
		}
		else if(time - m_StartTime >= m_ClickTimeout){
			clickTimedOut();
		}
	}
}

void Button::clickTimedOut(){
	if((m_Status & BUTTON_IS_PRESSED) == 0){
		switch(m_Status & BUTTON_HIT_COUNT){
			case 1:
				if(OnClick != 0){
					OnClick();
				}
				break;
			case 2:
				if(OnDoubleClick != 0){
					OnDoubleClick();
				}
				break;
		}
		reset();
	}
}

void Button::longPressTimedOut(){
	if(OnLongPress != 0 && (m_Status & BUTTON_IS_PRESSED) != 0 && (m_Status & BUTTON_HIT_COUNT) == 0){
		OnLongPress();
	}
	reset();
}

void Button::reset(){
	m_Status = (m_Status & BUTTON_IS_PULL_UP) | (m_Status & BUTTON_IS_HIGH_STATE);
}

uint8_t Button::GetClickTimeout(){
	return m_ClickTimeout;
}

uint16_t Button::GetPressTimeout(){
	return m_PressTimeout;
}

void Button::SetClickTimeout(uint8_t i_Timeout){
	m_ClickTimeout = i_Timeout;
}

void Button::SetPressTimeout(uint16_t i_Timeout){
	m_PressTimeout = i_Timeout;
}