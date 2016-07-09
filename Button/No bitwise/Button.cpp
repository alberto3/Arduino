#include "Button.h"
#include <Arduino.h>

Button::Button(ePullType i_PullType){
	m_PullType = i_PullType;
	reset();
}

bool Button::IsActivated(){
	return m_IsActive;
}

void Button::SetState(eState i_State){
	// Raising
	if(m_State == low && i_State == high){
		if(m_PullType == down){
			// pressed
			pressed();
		}else{
			// released
			released();
		}
	}
	// Falling
	else if(m_State == high && i_State == low){
		if(m_PullType == down){
			// released
			released();
		}else{
			// pressed
			pressed();
		}
	}
	m_State = i_State;
	refresh();
}

void Button::Refresh(){
	refresh();
}

void Button::pressed(){
	m_IsPressed = true;
	// This is the first time button pushed
	if(!m_IsActive){
		m_IsActive = true;
		m_StartTime = millis();
	}
	if(OnPress != 0){
		OnPress();
	}
}

void Button::released(){
	if(millis() - m_StartTime > BUTTON_LONG_PRESS_TIMEOUT){
		if(OnLongRelease != 0){
			OnLongRelease();
		}
		reset();
	}
	else{
		if(OnRelease != 0){
			OnRelease();
		}
		m_HitCount++;
		m_IsPressed = false;
	}
}

void Button::refresh(){
	unsigned long time = millis();
	if(m_IsActive){
		if(time - m_StartTime >= BUTTON_LONG_PRESS_TIMEOUT){
			longPressTimedOut();
		}
		else if(time - m_StartTime >= BUTTON_CLICK_TIMEOUT){
			clickTimedOut();
		}
	}
}

void Button::clickTimedOut(){
	if(!m_IsPressed){
		switch(m_HitCount){
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
	if(OnLongPress != 0 && m_IsPressed && m_HitCount == 0){
		OnLongPress();
	}
	reset();
}

void Button::reset(){
	m_HitCount = 0;
	m_StartTime = 0;
	m_IsActive = false;
	m_IsPressed = false;
}
