#include "header.h"

#include "BouncingEnemy.h"

#include "TheDayMain.h"




BouncingEnemy::BouncingEnemy(TheDayMain* pEngine, int iID, int iSize, std::string filename)
	:DisplayableObject(iSize, iSize, pEngine, iSize, iSize, false)
	, m_pEngine(pEngine)
	, m_iID(iID)
	,m_iSize(iSize)
	,image(pEngine->loadImage(filename, false))
{
	setVisible(true);
}


BouncingEnemy::~BouncingEnemy(void)
{
}
