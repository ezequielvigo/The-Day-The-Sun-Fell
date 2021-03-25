#include "header.h"
#include "TheDayTileManager.h"
#include "SimpleImage.h"
#include"ImageManager.h"
#include "TheDayMain.h"



void TheDayTileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY)
	const
{
	
	SimpleImage image = ImageManager::loadImage("images/objects/spike.png", false);
	
	// New implementation draws things of different sizes
	switch (getMapValue(iMapX, iMapY))
	{
	case 0:
	case 1:
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		
		//image.renderImage(m_pMainEngine->getForegroundSurface(), 0, 0, iMapX, iMapY, image.getHeight(),image.getWidth());

		image = image.shrinkBy(2);
		image.renderImageWithMask(pSurface, iStartPositionScreenX, iStartPositionScreenY, iStartPositionScreenX+50, iStartPositionScreenY+50, image.getWidth(), image.getHeight(), 0);
		break;
		

		
	}
}
