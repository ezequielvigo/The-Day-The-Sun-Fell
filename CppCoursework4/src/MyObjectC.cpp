#include "header.h"

#include "MyObjectC.h"
#include "Aeyev2Engine.h"





 int direction = 2;

 MyObjectC::MyObjectC(Aeyev2Engine* pEngine)
	 :DisplayableObject(pEngine)
	 , m_pMainEngine(pEngine)
	 ,direction(2)
{
	m_iCurrentScreenX = 100;
	m_iCurrentScreenY =187;
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;
	m_iColour = 0x00FF00;
	setVisible(true);
	
}


MyObjectC::~MyObjectC(void)
{
}


void MyObjectC::virtDraw()
{
	//Draws the object as a foreground oval
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x0000ff
	);
}


void MyObjectC::virtDoUpdate(int iCurrentTime)
{
	if (getEngine()->isPaused()) {
		return;
	}
	
	//Reaches left border therefore we switch the direction
	if (m_iCurrentScreenX<0) {
		direction = 2;
	}
	//Reaches right border therefore we switch the direction
	else if(m_iCurrentScreenX >= getEngine()->getWindowWidth() - m_iDrawWidth){
		direction = -2;
	}
	//Controls the movement of the object
	m_iCurrentScreenX += direction;

	//Uses the function I inserted into CourseWork3.h in order to return a reference to the TileManager
	CourseworkTileManager& tileManager = m_pMainEngine->GetTileManager();
		
	//Checks if the object is in a position where a tile is located
	if (tileManager.isValidTilePosition(m_iCurrentScreenX+50, m_iCurrentScreenY+50)) {
		int mapX = tileManager.getMapXForScreenX(m_iCurrentScreenX+50); // Which column?
		int mapY = tileManager.getMapYForScreenY(m_iCurrentScreenY+50); // Which row?
		int value = tileManager.getMapValue(mapX, mapY); // Current value?
		//Redraws the tile by adding 1 to its current color value which makes it go to the next possible color
		tileManager.setAndRedrawMapValueAt(mapX, mapY, value + 1, getEngine(), getEngine()->getBackgroundSurface());
		
	}
	//Need to ensure we redraw the display
	redrawDisplay();

}
