/**
 * @name:			Button.h
 * @description:	Button Class
 * @author:			Albert Harounian
 * @since:			March 11, 2013
 * @since:			January 17, 2014 :: Added: 1. Timeout control
 *										Refactored: 1. m_Status and m_StartTime member type
 */
 
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <Arduino.h>

#define BUTTON_DEFAULT_CLICK_TIMEOUT 		300
#define BUTTON_DEFAULT_LONG_PRESS_TIMEOUT 	900

#define BUTTON_IS_PRESSED			0x80
#define BUTTON_IS_ACTIVE			0x40
#define BUTTON_IS_PULL_UP			0x20
#define BUTTON_IS_HIGH_STATE		0x10
#define BUTTON_HIT_COUNT			0x07

class Button{
public:	
	
	enum ePullType{
		down,
		up
	};
	
	enum eState{
		low,
		high
	};

	void (*OnPress)();
	void (*OnLongPress)();
	void (*OnRelease)();
	void (*OnLongRelease)();
	void (*OnClick)();
	void (*OnDoubleClick)();

	Button();
	Button(ePullType i_PullType);
	
	static uint8_t GetClickTimeout();
	static uint16_t GetPressTimeout();
	static void SetClickTimeout(uint8_t i_Timeout);
	static void SetPressTimeout(uint16_t i_Timeout);

	void SetState(eState i_State);
	bool IsActivated();
	void Refresh();
	
private:
	
	uint8_t m_Status;
	uint32_t m_StartTime;
	
	static uint8_t m_ClickTimeout;
	static uint16_t m_PressTimeout;
	
	void init(ePullType i_PullType);
	void clickTimedOut();
	void longPressTimedOut();
	void pressed();
	void released();
	void reset();
	void refresh();
};

#endif
