#pragma once
#include "cocos2d.h"
#include "time.h"
using namespace cocos2d;
using namespace std;


class BackgroundLayer:public Layer{
public:
	BackgroundLayer(void);
    
	~BackgroundLayer(void);
    
	virtual bool init();
    
	CREATE_FUNC(BackgroundLayer);

	void stop();

	void restart();

private:
	void scrollBackground(float dt);

	Sprite* background1;

	Sprite* background2;

	SEL_SCHEDULE backgroundShift;
};