#pragma once
#include "DisplayableObject.h"
class Aeyev2Engine;

class MyObjectC :
	public DisplayableObject
{
public:
	//Ensuring it takes CourseWork 3 as a parameter
	MyObjectC(Aeyev2Engine* pEngine);
	~MyObjectC(void);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

private:
	//Our pointer to the main class
	Aeyev2Engine* m_pMainEngine;
	//private int for the direction
	int direction;
};

