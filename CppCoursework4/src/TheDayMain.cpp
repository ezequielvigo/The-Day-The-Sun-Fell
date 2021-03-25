#include "header.h"

#include "TheDayMain.h"

#include "ImageManager.h"

#include "sunPlayableObject.h"

#include "TileManager.h"

#include "MoonEnemy.h"

#include "windows.h"

#include "SDL_audio.h"

#include <iostream>

#include <fstream>

#include <memory>





TheDayMain::TheDayMain(void)
	:m_state(startScreen),
	score(1000),
	currentStage(1),
	currentEnemies(0),
	gameSaved(false)
{

	//Setting Up Loop1 Sound
	SDL_Init(SDL_INIT_AUDIO);
	//Variables for loadWav
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;
	SDL_LoadWAV("Music/loop1.wav", &wavSpec, &wavBuffer, &wavLength);
	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, NULL);
	int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);


}


TheDayMain::~TheDayMain(void)
{

}


void TheDayMain::virtSetupBackgroundBuffer()
{




	//Necessary for the file reading
	std::ifstream inFile;
	std::string line;
	int j;
	
	std::string fileToOpen = "resources/level"+ currentStage;
	fileToOpen += ".txt";

	switch (m_state) {
		
	case startScreen:
		setAllObjectsVisible(false);
		fillBackground(0);
		
		theDay = ImageManager::loadImage("images/background/titleScreen.png", true);
		theDay = theDay.shrinkBy(2) ;
		theDay.renderImage(getBackgroundSurface(), 0, 0, 350, 50, theDay.getWidth() , theDay.getHeight());
		

		break;
	case infoScreen:
		setAllObjectsVisible(false);
		fillBackground(0);

		info = ImageManager::loadImage("images/background/instructions.png", false);
		info = info.shrinkBy(2);
		info.renderImage(getBackgroundSurface(), 0, 0, 350, 125, info.getWidth(), info.getHeight());

		break;

	case startTransition:
		setAllObjectsVisible(false);
		sunObject->setVisible(true);
		
		introBackground = ImageManager::loadImage("images/background/daytime.png", false);
		introBackground = introBackground.resizeTo(getWindowWidth(), getWindowHeight());
		introBackground.renderImage(getBackgroundSurface(), 0, 0, 0, 0, getWindowWidth(), getWindowHeight());

		if (startOfGame == false) {
			m_state = playingGame;
			lockAndSetupBackground();
			redrawDisplay();
		}
		break;
	case playingGame:
		
		setAllObjectsVisible(true);

		if (endOfGame) {
			this->pause();
			m_state = endTransition;
			lockAndSetupBackground();
			redrawDisplay();
			return;
		}
		
		gameBackground = ImageManager::loadImage("images/background/starrynightoptional.jpg", true);
		gameBackground = gameBackground.resizeTo(getWindowWidth(), getWindowHeight());
		gameBackground.renderImage(getBackgroundSurface(), 0, 0, 0, 0, getWindowWidth(), getWindowHeight());
	    

		gameGround = ImageManager::loadImage("images/floor/nightFloor.jpg", true);
		gameGround.renderImage(getBackgroundSurface(), 0, 0, 0, 700, getWindowWidth(), 100);

		ladder = ImageManager::loadImage("images/objects/ladder.png", false);
		ladder = ladder.resizeTo(100,550);
		

		//Sets values for the levels
		

		char data[14][10];
		j = 0;
		//Opens the necessary level file

		switch (currentStage) {
		case 1:
			inFile.open("resources/level1.txt");
			break;
		case 2: 
			inFile.open("resources/level2.txt");
			break;
		case 3:
			inFile.open("resources/level3.txt");
			break;
		case 4:
			inFile.open("resources/level4.txt");
			ladder.renderImageWithMask(getBackgroundSurface(), 0, 0, 1200, 150, ladder.getWidth(), ladder.getHeight(), 0x000000);

			break;
		}
		if (currentStage > 1) {
		for (int i = currentEnemies; i < currentStage-1; i++) {
				storeObjectInArray(i + 1, new BouncingMoon(this, 100, 0, "images/objects/pixelMoon.png", i * 40, 150, (i + 1)*2, (i + 1)*2.5));
				currentEnemies++;
		}
		}

		//Writes the values from the file to data
		if (!inFile) {
			std::cout << "Unable to Open File";
		}
		else {
			while (getline(inFile, line)) {
				for (int i = 0; i < line.length(); i++) {
					if (line[i] != ' ' && line[i] != '\n') {
						data[j][i] = line[i];
					}
				}
				j++;
			}
		}
		//Makes sure to close the file reader
		inFile.close();

		m_oTileManager.setMapSize(13, 8);
		// Set up the tiles
		for (int x = 0; x < 13; x++)
			for (int y = 0; y < 8; y++)
				m_oTileManager.setMapValue(x, y, data[y][x] - 'a');

		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 13; x++)
				std::cout << m_oTileManager.getMapValue(x, y);
			std::cout << std::endl;
		}
		m_oTileManager.setTopLeftPositionOnScreen(0, 0);
		m_oTileManager.drawAllTiles(this, getBackgroundSurface());
		break;

	case pausedGame:
		SDL_CloseAudio();
		fillBackground(0);
		setAllObjectsVisible(false);
		pausedScreen = ImageManager::loadImage("images/background/pausedScreen.png", false);
		pausedScreen = pausedScreen.shrinkBy(2);
		pausedScreen.renderImage(getBackgroundSurface(), 0, 0, 350, 125, pausedScreen.getWidth(), pausedScreen.getHeight());

		break;

	case endTransition:
		setAllObjectsVisible(false);
		sunObject->setVisible(true);
		endBackground = ImageManager::loadImage("images/background/daytime.png", false);
		endBackground = endBackground.resizeTo(getWindowWidth(), getWindowHeight());
		endBackground.renderImage(getBackgroundSurface(), 0, 0, 0, 0, getWindowWidth(), getWindowHeight());
		break;

	}
	return;
	}





void TheDayMain::virtKeyDown(int iKeyCode)
{	
	switch (m_state) {
		case startScreen:
			switch (iKeyCode) {
			case SDLK_SPACE:
				m_state =startTransition;
				startOfGame = true;
				lockAndSetupBackground();
				redrawDisplay();
				break;

			case SDLK_ESCAPE:
				setExitWithCode(0);
				break;

			case SDLK_l:
				loadGame();
				m_state = playingGame;
				gameLoaded = true;
				lockAndSetupBackground();
				redrawDisplay();
				break;

			case SDLK_a:
				m_state = infoScreen;
				lockAndSetupBackground();
				redrawDisplay();
				break;
			}
			break;

		case playingGame:
			switch (iKeyCode) {
			case SDLK_SPACE:
				this->pause();
				gameSaved = false;
				m_state = pausedGame;
				lockAndSetupBackground();
				redrawDisplay();
				break;

			case SDLK_ESCAPE:
				setExitWithCode(0);
				break;
			}
			break;

		case pausedGame:
			switch (iKeyCode) {
			case SDLK_SPACE:
				this->unpause();
				m_state = playingGame;
				lockAndSetupBackground();
				redrawDisplay();
				break;
			
			case SDLK_ESCAPE:
				setExitWithCode(0);
				break;

			case SDLK_s:
				saveGame();
				lockAndSetupBackground();
				redrawDisplay();
				break;
			}
			break;

		case infoScreen:
			switch (iKeyCode) {
			case SDLK_ESCAPE:
				m_state = startScreen;
				lockAndSetupBackground();
				redrawDisplay(); 
				break;
			}
			break;
		case endTransition:
			switch (iKeyCode) {
			case SDLK_ESCAPE:
				setExitWithCode(0);
				break;
			}
	}

}


int TheDayMain::virtInitialiseObjects()
{
	// TODO: Add your implementation code here.
	drawableObjectsChanged();
	destroyOldObjects(true);
	createObjectArray(6);
	sunObject = new sunPlayableObject(this, "images/objects/sunAfterFalling.png");
	storeObjectInArray(0, sunObject);

	setAllObjectsVisible(false);
	
	return 0;
}


void TheDayMain::virtDrawStringsOnTop()
{
	switch (m_state) {


	case startScreen:
		
		break;

	case infoScreen:
		
		break;

	case startTransition:
		drawForegroundString(800, 500, "OH NO WHAT IS HAPPENING?", 0xff5200, NULL);
		break;

	case pausedGame:
		
		if (gameSaved == true)
			drawForegroundString(450, 500, "*GAME SUCCESFULLY SAVED*", 0xFFFFFF, NULL);
		
		break;

	case playingGame:
		char buf[128];
		char buf2[128];
		sprintf(buf, "Score : %d", score);
		sprintf(buf2, "Stage %d", currentStage);
		drawForegroundString(1000, 50, buf, 0xffffff, NULL);
		drawForegroundString(580, 50, buf2, 0xffffff, NULL);

		break;

	case endTransition:
		char buf3[128];
		sprintf(buf3, "Your final score was : %d", score);
		drawForegroundString(600, 150, "YOU WON!!", 0x00263b, NULL);
		drawForegroundString(500, 250, "Congratulations on Finishing", 0x00263b, NULL);
		drawForegroundString(500, 350, buf3, 0x00263b, NULL);
		drawForegroundString(500, 450, "PRESS ESC TO EXIT GAME", 0x00263b, NULL);
		break;

	}
}


void TheDayMain::saveGame()
{
	std::ofstream saveFile ("resources/saveFile.txt", std::ios::app);
	if (saveFile.is_open()) {
		saveFile << currentStage << " " << score << " \n";
		saveFile.close();
		gameSaved = true;
	}
	else {
		gameSaved = false;
	}

}


void TheDayMain::loadGame()
{

	std::ifstream fs;
	fs.open("resources/saveFile.txt", std::fstream::in);
	if (fs.is_open())
	{
		//Got to the last character before EOF
		fs.seekg(-1, std::ios_base::end);
		if (fs.peek() == '\n')
		{
			//Start searching for \n occurrences
			fs.seekg(-1, std::ios_base::cur);
			int i = fs.tellg();
			for (i; i > 0; i--)
			{
				if (fs.peek() == '\n')
				{
					//Found
					fs.get();
					break;
				}
				//Move one character back
				fs.seekg(i, std::ios_base::beg);
			}
		}
		std::string lastline;
		getline(fs, lastline);

		currentStage = lastline[0] - 48;
		int scoreString[4];
		
		score = 0;
		int val = 0;

		if (lastline[5] - 48 == 0) {
			score = 1000;
		}
		else {

			for (int i = 2; i <= 4; i++) {
				val = lastline[i] - 48;
				for (int j = 0; j < (4 - i); j++) {
					val = val * 10;
				}
				score += val;
			}

		}

		
		fs.close();
	}
	else {
		return;
	}

}






