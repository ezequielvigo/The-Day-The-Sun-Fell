#include "header.h"
#include "Aeyev2Engine.h"
#include "MyObjectB.h"
#include "MyObjectC.h"


Aeyev2Engine::Aeyev2Engine()
{
}


Aeyev2Engine::~Aeyev2Engine()
{
}

void Aeyev2Engine::virtSetupBackgroundBuffer()
{
	// TODO: Add your implementation code here.
	for(int iX = 0; iX < getWindowWidth();iX++)
		for (int iY = 0; iY < this->getWindowHeight(); iY++) 
			switch (rand() % 2)
			{
			case 0: setBackgroundPixel(iX, iY, 0xFA0101); break;
			case 1: setBackgroundPixel(iX, iY, 0xFFF702); break;
			}
		//Draws the various rectangles	I wanted in the background
				lockBackgroundForDrawing();
				drawBackgroundRectangle(0, 0, 1300, 260, 0xFA0101);
				drawBackgroundRectangle(0, 540, 1300, 800, 0xFA0101);
				unlockBackgroundForDrawing();
				redrawDisplay();

		//Loops through all the tiles and sets random map values to them
				for (int i = 0; i < 32; i++)
					for (int j = 0; j < 20; j++)
						tileManager.setMapValue(i, j, rand());
		//Sets the top position where the tileManager will begin drawing and draws all the tiles
				tileManager.setTopLeftPositionOnScreen(0, 0);
				tileManager.drawAllTiles(this, getBackgroundSurface());

}
void Aeyev2Engine::virtMouseDown(int iButton, int iX, int iY)
{
	// TODO: Add your implementation code here.
	printf("Mouse clicked at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT) {
		if (tileManager.isValidTilePosition(iX, iY)) // Clicked within tiles?
		{
			int mapX = tileManager.getMapXForScreenX(iX); // Which column?
			int mapY = tileManager.getMapYForScreenY(iY); // Which row?
			int value = tileManager.getMapValue(mapX, mapY); // Current value?
			tileManager.setAndRedrawMapValueAt(mapX, mapY, value + rand(), this, getBackgroundSurface());
			 
		}
		redrawDisplay();
	}
}

int Aeyev2Engine::virtInitialiseObjects()
{
	// Destroys all the old objects and initialises the object array, then I store all my objects in different indexes in the array
	drawableObjectsChanged();
	destroyOldObjects(true);
	createObjectArray(2);
	storeObjectInArray(0, new MyObjectB(this));
	storeObjectInArray(1, new MyObjectC(this));
	
	//Makes all the objects visible
	setAllObjectsVisible(true);
	return 0;
}





void Aeyev2Engine::virtDrawStringsOnTop()
{	//This code initialises a character array that has the %6d set to rand which is constantly changin through sprint f
	char buf[128];
	sprintf(buf, "Random Numbers refreshing/redrawing appropriately %6d", rand());

	//I use this method to draw the string to the foreground selecting the location and the value being buf
	drawForegroundString(200, 50, buf, 0xff00ff, NULL);
	drawForegroundString(400, 200, "This proves it is in front of the object", 0xff0f0f, NULL);
}




void Aeyev2Engine::virtKeyDown(int iKeyCode)
{
	//Schecks which key is being pushed and reacts according with space or escape
	switch (iKeyCode) {
	case SDLK_ESCAPE :
		setExitWithCode(0);
		break;
	case SDLK_SPACE:
		if (isPaused())
			unpause();
		else
			pause();
		break;
	}
}
