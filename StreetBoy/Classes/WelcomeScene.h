#pragma once
#include "cocos2d.h"
#include "WelcomeLayer.h"
using namespace cocos2d;

class WelcomeScene : public Scene {
public:
	WelcomeScene();
	~WelcomeScene();
	bool virtual init();
	CREATE_FUNC(WelcomeScene);

private:
	WelcomeLayer* welcomeLayer;
};