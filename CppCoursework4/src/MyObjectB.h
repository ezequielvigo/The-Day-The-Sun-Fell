#pragma once
#include "DisplayableObject.h"
class Aeyev2Engine;

class MyObjectB :
	public DisplayableObject
{
public:
	MyObjectB(Aeyev2Engine* pEngine);
	~MyObjectB(void);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

private:
	//Our pointer to the main engine
	Aeyev2Engine* m_pMainEngine;
	

};

