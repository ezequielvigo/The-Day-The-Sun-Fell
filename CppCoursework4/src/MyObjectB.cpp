#include "header.h"
#include "MyObjectB.h"
#include "Aeyev2Engine.h"
#include "CollisionDetection.h"



MyObjectB::MyObjectB(Aeyev2Engine* pEngine)
	: DisplayableObject(pEngine)
	,m_pMainEngine(pEngine)
{
	m_iCurrentScreenX = 550;
	m_iCurrentScreenY = 300;
	m_iDrawWidth = 100;
	m_iDrawHeight = 100;
	m_iColour = 0x00FF00;

}


MyObjectB::~MyObjectB()
{
}


void MyObjectB::virtDraw()
{
	
	// TODO: Add your implementation code here.
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		m_iColour);
}


void MyObjectB::virtDoUpdate(int iCurrentTime)
{
	// Checks which key is being pressed and adjusts movement accordingly
	if (getEngine()->isKeyPressed(SDLK_UP))
		m_iCurrentScreenY -= 2;
	if (getEngine()->isKeyPressed(SDLK_DOWN))
		m_iCurrentScreenY += 2;
	if (getEngine()->isKeyPressed(SDLK_LEFT))
		m_iCurrentScreenX -= 2;
	if (getEngine()->isKeyPressed(SDLK_RIGHT))
		m_iCurrentScreenX += 2;

	//Does the same as above but for wasd instead
	if (getEngine()->isKeyPressed('w'))
		m_iCurrentScreenY -= 2;
	if (getEngine()->isKeyPressed('s'))
		m_iCurrentScreenY += 2;
	if (getEngine()->isKeyPressed('a'))
		m_iCurrentScreenX -= 2;
	if (getEngine()->isKeyPressed('d'))
		m_iCurrentScreenX += 2;
	
	//Here we check the current position and if it has passed the boundaries of the screen we make it remain there so it can drift into nothing
	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	//We used the getWindowWidth for the right borders
	if (m_iCurrentScreenX >= getEngine()->getWindowWidth() - m_iDrawWidth)
		m_iCurrentScreenX = getEngine()->getWindowWidth() - m_iDrawWidth;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= getEngine()->getWindowHeight() - m_iDrawHeight)
		m_iCurrentScreenY = getEngine()->getWindowHeight() - m_iDrawHeight;

	DisplayableObject* pObject;
	//This will loop through the object array we created 
	for (int iObjectId = 0;
		(pObject = m_pMainEngine->getDisplayableObject(iObjectId)
			) != NULL;
		iObjectId++)
	{	//Checks if the object on this iteration is our own
		if (pObject == this)
			continue;
		//Checks if the object on this iteration is the null
		if (pObject == nullptr)
			continue;

		//A little primitive but I have set thse to be the known size I have for the objects
		int iSize = 50;
		int iOtherSize = iSize / 2;

		//Here it uses the CollisionDetetction checkCircles, to check if the object we are storing in pOnject is within the boundaries of our own
		if (CollisionDetection::checkCircles(pObject->getXCentre(), pObject->getYCentre(), m_iCurrentScreenX, m_iCurrentScreenY, iOtherSize + iSize)) {
			//Shifts the object back to its original position
			m_iCurrentScreenX = 550;
			m_iCurrentScreenY = 300;

			//Changes the colour to random one
			m_iColour += rand();
			
		}


		//Must redraw the display if there has been any changes
		this->redrawDisplay();
	}


}



