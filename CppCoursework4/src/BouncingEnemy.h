#ifndef BouncingEnemy_H
#define BouncingEnemy_H

#pragma once
#include "DisplayableObject.h"
#include "ImageManager.h"
#include "BaseEngine.h"
#include "MovementPosition.h"

class BaseEngine;

class BouncingEnemy :
	public DisplayableObject
{

public:
	BouncingEnemy(TheDayMain* pEngine, int iID, int iSize, std::string filename);

	~BouncingEnemy(void);


private:
	SimpleImage image;
	TheDayMain* m_pEngine;
	int m_iID;
	int m_iSize;



};

#endif