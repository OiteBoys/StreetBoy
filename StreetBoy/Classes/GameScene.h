#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
#include "OptionLayer.h"
#include "BackgroundLayer.h"

using namespace cocos2d;

class GameScene : public Scene {
public:
	GameScene();
	~GameScene();
	bool virtual init();
	CREATE_FUNC(GameScene);

private:
	GameLayer *gameLayer;
	OptionLayer *optionLayer;
};