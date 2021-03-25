#include "header.h"

#include "MoonEnemy.h"

#include "TheDayMain.h"



MoonEnemy::MoonEnemy(TheDayMain* pEngine, int iSize, int iID, std::string filename)
	: DisplayableObject(iSize, iSize, pEngine, iSize, iSize)
	, m_pEngine(pEngine)
	, m_iSize (iSize)
	,m_iID(iID)
	, image(pEngine->loadImage(filename, false))
{
	setVisible(true);
}


MoonEnemy::~MoonEnemy(void)
{
}


void MoonEnemy::virtDraw()
{
	// TODO: Add your implementation code here.
	if (!isVisible()) {
		return;
	}
	image = image.resizeTo(100, 100);
	m_iDrawHeight = image.getHeight();
	m_iDrawWidth = image.getWidth();

	m_pEngine->drawForegroundOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xe2e2e2
	);

	image.renderImageWithMask(m_pEngine->getForegroundSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, image.getWidth(), image.getHeight(), 0x000000);

}


void MoonEnemy::virtDoUpdate()
{
	// TODO: Add your implementation code here.
	redrawDisplay();
}


BouncingMoon::BouncingMoon(TheDayMain* pEngine, int iSize, int iID, std::string filename, double dX, double dY, double dSX, double dSY) 
	: MoonEnemy(pEngine, iSize, iID, filename)
	, m_dX(dX)
	, m_dY(dY)
	, m_dSX(dSX)
	, m_dSY(dSY)
{

}

void BouncingMoon::setPosition(double dX, double dY) {
	m_dX = dX;
	m_dY = dY;
}

void BouncingMoon::setSpeed(double dSX, double dSY) {
	m_dSX = dSX;
	m_dSY = dSY;
}

void BouncingMoon::virtDoUpdate(int iCurrentTime) {
	m_dX += m_dSX;
	m_dY += m_dSY;

	if ((m_dX + m_iStartDrawPosX) < 0)
	{
		m_dX = -m_iStartDrawPosX;
		if (m_dSX < 0)
			m_dSX = -m_dSX;
	}

	if ((m_dX + m_iStartDrawPosX + m_iDrawWidth) > (getEngine()->getWindowWidth() - 1))
	{
		m_dX = getEngine()->getWindowWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
		if (m_dSX > 0)
			m_dSX = -m_dSX;
	}

	if ((m_dY + m_iStartDrawPosY) < 0)
	{
		m_dY = -m_iStartDrawPosY;
		if (m_dSY < 0)
			m_dSY = -m_dSY;
	}

	if ((m_dY + m_iStartDrawPosY + m_iDrawHeight) > (700 - 1))
	{
		m_dY = 700 - m_iStartDrawPosY - m_iDrawHeight;
		if (m_dSY > 0)
			m_dSY = -m_dSY;
	}

	// Work out current position
	m_iCurrentScreenX = (int)(m_dX + 0.5);
	m_iCurrentScreenY = (int)(m_dY + 0.5);

	// Ensure that the object gets redrawn on the display, if something changed
	redrawDisplay();
}