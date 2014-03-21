#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
#include "OptionLayer.h"
#include "BackgroundLayer.h"

using namespace cocos2d;

class GameScene : public Scene , public StatusDelegate{
public:
	GameScene();
	~GameScene();
	bool virtual init();
	CREATE_FUNC(GameScene);

	/**
	* When the game start, this method will be called
	*/
	void onGameStart(void);

	/**
	* During paying, after the score changed, this method will be called
	*/
	void onGamePlaying(int score);

	/**
	* When game is over, this method will be called
	*/
	void onGameEnd(int score);

private:
	GameLayer *gameLayer;
	OptionLayer *optionLayer;
	BackgroundLayer* backgroundLayer;
};