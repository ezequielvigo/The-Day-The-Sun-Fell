#pragma once
#include "TileManager.h"
class CourseworkTileManager :
	public TileManager
{
public:
	CourseworkTileManager();
	~CourseworkTileManager();

	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
};

