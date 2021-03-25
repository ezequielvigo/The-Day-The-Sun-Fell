#pragma once
#ifndef MoonEnemy_H
#define MoonEnemy_H

#include "DisplayableObject.h"
#include "ImageManager.h"
#include "MovementPosition.h"

#include "TheDayMain.h"

class BaseEngine;

class MoonEnemy :
	public DisplayableObject
{
public:

	MoonEnemy(TheDayMain* pEngine, int iSize, int iID, std::string filename);

	~MoonEnemy(void);

private:
	SimpleImage image;
	TheDayMain* m_pEngine;
	int m_iSize;
	int m_iID;
public:
	void virtDraw();
	void virtDoUpdate();
};

class BouncingMoon :
	public MoonEnemy
{
public:
	BouncingMoon(TheDayMain* pEngine, int iSize, int iID, std::string filename, double dX, double dY, double dSX, double dSY);
	void setPosition(double dX, double dY);
	void setSpeed(double dSX, double dSY);
	void virtDoUpdate(int iCurrentTime) override;


protected:

	double m_dX;
	double m_dY;
	double m_dSX;
	double m_dSY;

};

#endif


