#pragma once
#include "cocos2d.h"
#include "string.h"
#include "Constant.h"
#include "UserRecord.h"

using namespace cocos2d;
using namespace std;

class StatusLayer : public Layer {
public:
	StatusLayer();
	~StatusLayer();
	virtual bool init();
	CREATE_FUNC(StatusLayer);
	void start();
	void playing(int score);
	void gameOver(int score);

private:
	void menuPauseCallback(Object* pSender);
	void menuHomeCallback(Object* sender);
	void menuRestartCallback(Object* sender);
	void showHomeAndRestartButton(float dt);

	Menu* menu;
	Node* scorePanel;
	MenuItemSprite* pause;
	MenuItemSprite* home;
	MenuItemSprite* restart;
	LabelBMFont *scoreLabel;
};