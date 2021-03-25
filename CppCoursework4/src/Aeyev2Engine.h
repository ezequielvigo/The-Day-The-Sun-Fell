#pragma once
#include "BaseEngine.h"
#include "CourseworkTileManager.h"
class Aeyev2Engine :
	public BaseEngine
{
public:
	Aeyev2Engine();
	~Aeyev2Engine();
	void virtSetupBackgroundBuffer();
	int virtInitialiseObjects();
	void virtMouseDown(int iButton, int iX, int iY);
	void virtDrawStringsOnTop();
	void virtKeyDown(int iKey);

	CourseworkTileManager& GetTileManager() { return tileManager; }


protected:
	CourseworkTileManager tileManager;
};

