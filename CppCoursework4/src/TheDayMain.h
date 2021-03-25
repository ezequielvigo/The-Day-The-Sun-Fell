#pragma once
#include "BaseEngine.h"
#include "TileManager.h"
#include "TheDayTileManager.h"
#include <memory>

class MoonEnemy;
class BouncingMoon;


class TheDayMain :
	public BaseEngine
{
public:
	TheDayMain(void);
	~TheDayMain(void);

	virtual void virtSetupBackgroundBuffer() override;
	virtual void virtKeyDown(int iKeyCode) override;
	virtual int virtInitialiseObjects() override;

	TheDayTileManager& getTileManager(){return m_oTileManager;}
	int& getCurrentScore() { return score; }
	int& getCurrentStage() { return currentStage; }
	bool& getStartOfGame() { return startOfGame; }
	bool& getEndOfGame() { return endOfGame; }
	bool& getGameLoaded() { return gameLoaded; }
	

public:
	enum State{startScreen, loadScreen, startTransition, endTransition, pausedGame, infoScreen, playingGame};

private:
	
	State m_state;
	SimpleImage gameBackground, gameGround, introBackground, theDay, info, endBackground, ladder, pausedScreen;

private:
	TheDayTileManager m_oTileManager;
	int currentStage , score, currentEnemies;
	bool startOfGame = false;
	bool endOfGame = false;
	bool gameSaved = false;
	bool gameLoaded = false;
	

public:
	void virtDrawStringsOnTop();
	void saveGame();
	void loadGame();
	

protected:
	DisplayableObject* sunObject;
};
