#include "header.h"
#include "TheDayMain.h"
#include "sunPlayableObject.h"
#include "SimpleImage.h"
#include "CollisionDetection.h"


sunPlayableObject::sunPlayableObject(TheDayMain* pEngine, std::string strURL)
	:DisplayableObject(pEngine)
	,m_pMainEngine(pEngine)
	,image(pEngine->loadImage(strURL, false))
	,jumpStarted(false)
	,iStartJumpY(700)
	,iMaxJumpY(500)
	, endingAnimation(false)
{
	image = image.shrinkBy(4);
	m_iCurrentScreenX = 10;
	m_iCurrentScreenY = 100;
	m_iDrawHeight = image.getHeight();
	m_iDrawWidth = image.getWidth();

	setVisible(true);
}


sunPlayableObject::~sunPlayableObject(void)
{
}


void sunPlayableObject::virtDraw()
{
	// TODO: Add your implementation code here.
	
	if (isVisible()) {
		
		
		getEngine()->drawForegroundOval(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0xFF8C00
		);
		
		image.renderImageWithMask(m_pMainEngine->getForegroundSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY,image.getWidth(), image.getHeight(),0x000000);
	}
}


void sunPlayableObject::virtDoUpdate(int iCurrentTime)
{
	while (m_pMainEngine->isPaused()) {
		return;
	}

	TheDayTileManager& tileManager = m_pMainEngine->getTileManager();
	int& gameScore = m_pMainEngine->getCurrentScore();
	int& currentStage = m_pMainEngine->getCurrentStage();
	bool& startOfGame = m_pMainEngine->getStartOfGame();
	bool& gameLoaded = m_pMainEngine->getGameLoaded();
	bool& endOfGame = m_pMainEngine->getEndOfGame();
	if (startOfGame) {

		if (m_iCurrentScreenY < 600) {
			m_iCurrentScreenY += 1;
			this->redrawDisplay();
		}

		if (m_iCurrentScreenY >= 600) {
			startOfGame = false;
			m_pMainEngine->lockAndSetupBackground();
			m_pMainEngine->redrawDisplay();
		}

	}
	if (endingAnimation) {
		if (m_iCurrentScreenY > 100 && m_iCurrentScreenX > 10) {
			m_iCurrentScreenY -= 2;
		}

		if (m_iCurrentScreenY <= 100) {
			endingAnimation = false;
			endOfGame = true;
			m_pMainEngine->lockAndSetupBackground();
			m_pMainEngine->redrawDisplay();
		}
	}
	if (gameLoaded) {
		m_iCurrentScreenY = 600;
		gameLoaded = false;
	}

	//TileManager Collisions
	if (tileManager.isValidTilePosition(m_iCurrentScreenX, m_iCurrentScreenY)) {
		int mapX = tileManager.getMapXForScreenX(m_iCurrentScreenX); // Which column?
		int mapY = tileManager.getMapYForScreenY(m_iCurrentScreenY); // Which row?
		int value = tileManager.getMapValue(mapX, mapY); // Current value

		if (tileManager.getMapValue(mapX, mapY) == 3) {
			m_iCurrentScreenX = 0;
			gameScore -= 10;
		}
		this->redrawDisplay();
	}

	//Handles Jumping and Movement
	if (jumpStarted) {
		if (m_iCurrentScreenY + m_iDrawHeight < iMaxJumpY) {
			iMovementDirection = 6;
			m_iCurrentScreenY += iMovementDirection;
		}
		if (m_iCurrentScreenY + m_iDrawHeight > iStartJumpY) {
			m_iCurrentScreenY = iStartJumpY - m_iDrawHeight;
			jumpStarted = false;
			return;
		}
		else {
			m_iCurrentScreenY += iMovementDirection;
		}
		if (getEngine()->isKeyPressed(SDLK_LEFT))
			m_iCurrentScreenX -= 4;
		if (m_pMainEngine->isKeyPressed(SDLK_RIGHT))
			m_iCurrentScreenX += 4;
		this->redrawDisplay();
	}

	// TODO: Add your implementation code here.
	if (!jumpStarted) {
		if (getEngine()->isKeyPressed(SDLK_UP))
			jumpStarted = true;
		iMovementDirection = -4;
		if (getEngine()->isKeyPressed(SDLK_LEFT))
			m_iCurrentScreenX -= 2;
		if (m_pMainEngine->isKeyPressed(SDLK_RIGHT))
			m_iCurrentScreenX += 2;


		if (m_iCurrentScreenX < 0)
			m_iCurrentScreenX = 0;
		if (m_iCurrentScreenX >= getEngine()->getWindowWidth() - m_iDrawWidth) {
			if (currentStage < 4) {
				m_iCurrentScreenX = 0;
				currentStage += 1;
				m_pMainEngine->lockAndSetupBackground();
				m_pMainEngine->redrawDisplay();
			}
			
		}
		if (m_iCurrentScreenY < 0)
			m_iCurrentScreenY = 0;
		if (m_iCurrentScreenY > iStartJumpY - m_iDrawHeight)
			m_iCurrentScreenY = iStartJumpY - m_iDrawHeight;

	}

	if (currentStage == 4 && m_iCurrentScreenX >= getEngine()->getWindowWidth() - m_iDrawWidth) {
		endingAnimation = true;
		return;
	}

	DisplayableObject* pObject;
	if(!endingAnimation){
		for (int i = 0; i < 4; i++) {
			for (int iObjectId = i;
				(pObject = m_pMainEngine->getDisplayableObject(iObjectId)
					) != NULL;
				iObjectId++)
			{	//Checks if the object on this iteration is our own
				if (pObject == this)
					continue;
				//Checks if the object on this iteration is the null
				if (pObject == nullptr)
					continue;

				int iRadius = half<int>(m_iDrawHeight, 1);
				if (CollisionDetection::checkCircles(pObject->getXCentre(), pObject->getYCentre(), m_iCurrentScreenX, m_iCurrentScreenY, iRadius)) {
					//Shifts the object back to its original position
					m_iCurrentScreenX = 0;
					gameScore -= 20;
				}
			}
		}

		redrawDisplay();
	}
}