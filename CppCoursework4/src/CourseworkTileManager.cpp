#include "header.h"
#include "CourseworkTileManager.h"



CourseworkTileManager::CourseworkTileManager()
	:TileManager(40,40,32,20)
{
}


CourseworkTileManager::~CourseworkTileManager()
{
}

void CourseworkTileManager::virtDrawTileAt(
	BaseEngine* pEngine, // We don't need this but maybe a student will so it is
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY);
	unsigned int iColour = 0x101f01 * ((iMapX + iMapY + iMapValue) % 16);
	pSurface->drawOval(
		iStartPositionScreenX, // Left
		iStartPositionScreenY, // Top
		iStartPositionScreenX + getTileWidth() - 1, // Right
		iStartPositionScreenY + getTileHeight() - 1, // Bottom
		iColour); // Pixel colour
}