#pragma once
#include "TileManager.h"



class TheDayTileManager :
	public TileManager
{
public:
	TheDayTileManager(void) : TileManager(100, 100)
	{
	}
	~TheDayTileManager(void) 
	{
	}


	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;

private:
	SimpleImage image;

public:
	SimpleImage operator/(int n) {
		TheDayTileManager temp;
		temp.image = (temp.image).shrinkBy(n);
		return temp.image;
	}

};

