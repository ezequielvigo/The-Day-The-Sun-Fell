#include "header.h"
#include "MyDemoA.h"
#include "ImageManager.h"
#include "MyObjectA.h"


MyDemoA::MyDemoA()
{
}


MyDemoA::~MyDemoA()
{
}


void MyDemoA::virtSetupBackgroundBuffer()
{
	// TODO: Add your implementation code here.
	//Drawing a background 
	fillBackground(0x000000);
	for (int iX = 0; iX < getWindowWidth(); iX++)
		for (int iY = 0; iY < this->getWindowHeight(); iY++)
			switch (rand() % 100)
			{
			case 0: setBackgroundPixel(iX, iY, 0xFF0000); break;
			case 1: setBackgroundPixel(iX, iY, 0x00FF00); break;
			case 2: setBackgroundPixel(iX, iY, 0x0000FF); break;
			case 3: setBackgroundPixel(iX, iY, 0xFFFF00); break;
			case 4: setBackgroundPixel(iX, iY, 0x00FFFF); break;
			case 5: setBackgroundPixel(iX, iY, 0xFF00FF); break;
			}
	//Rendering an image in background
	SimpleImage image = ImageManager::loadImage("demo.png", true);
	image.renderImage(getBackgroundSurface(), 0, 0, 10, 10, image.getWidth(), image.getHeight());

	//Drawing the tiles so we can use them
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			tm.setMapValue(i, j, rand());
	tm.setTopLeftPositionOnScreen(50, 50);
	tm.drawAllTiles(this, getBackgroundSurface());
}


void MyDemoA::virtMouseDown(int iButton, int iX, int iY)
{
	printf("Mouse clicked at %d %d \n", iX, iY);
	// TODO: Add your implementation code here.
	if (iButton == SDL_BUTTON_LEFT) {
		//drawBackgroundRectangle(iX - 10, iY - 10, iX + 10, iY + 10, 0xff0000);
		if (tm.isValidTilePosition(iX, iY)) // Clicked within tiles?
		{
			int mapX = tm.getMapXForScreenX(iX); // Which column?
			int mapY = tm.getMapYForScreenY(iY); // Which row?
			int value = tm.getMapValue(mapX, mapY); // Current value?
			tm.setAndRedrawMapValueAt(mapX, mapY, value + rand(), this, getBackgroundSurface());
		}
		redrawDisplay(); // Force background to be redrawn to foreground
	}
}


void MyDemoA::virtKeyDown(int iKeyCode)
{
	// TODO: Add your implementation code here.
	switch (iKeyCode) {
	case' ':
		lockBackgroundForDrawing();
		virtSetupBackgroundBuffer();
		unlockBackgroundForDrawing();
		redrawDisplay();
		break;
	}
}


int MyDemoA::virtInitialiseObjects()
{
	drawableObjectsChanged();
	destroyOldObjects(true);
	createObjectArray(1);
	storeObjectInArray(0, new MyObjectA(this));
	setAllObjectsVisible(true);
	// TODO: Add your implementation code here.
	return 0;
}
