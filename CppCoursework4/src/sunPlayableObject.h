#pragma once
#include "DisplayableObject.h"
class TheDayMain;

class sunPlayableObject :
	public DisplayableObject
{
public:
	sunPlayableObject(TheDayMain* pEngine, std::string strURL);
	~sunPlayableObject(void);

private:
	TheDayMain* m_pMainEngine;
	SimpleImage image;
	bool jumpStarted = false;
	int iMaxJumpY = 500;
	int iStartJumpY= 600;
	int iMovementDirection;
	int value = 0;
	bool endingAnimation = false;
public:
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

	template <typename T, typename U>
	U half(T x, U y) {
		for (int i = 0; i < y; i++) {
			x = x / 2;
		}
		return x;
	}

};

