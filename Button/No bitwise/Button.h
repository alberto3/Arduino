/**
 * @name:			Button.h
 * @description:	Button Class
 * @author:			Albert Harounian
 */
 
#ifndef __BUTTON_H__
#define __BUTTON_H__

#define BUTTON_CLICK_TIMEOUT 		300
#define BUTTON_LONG_PRESS_TIMEOUT 	900

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

	Button(ePullType i_PullType);
	void SetState(eState i_State);
	bool IsActivated();
	void Refresh();
	
private:
	
	bool m_IsPressed;
	bool m_IsActive;
	eState m_State;
	ePullType m_PullType;
	unsigned char m_HitCount;
	unsigned long m_StartTime;
	
	void clickTimedOut();
	void longPressTimedOut();
	void pressed();
	void released();
	void reset();
	void refresh();
};

#endif
