#pragma once
#include "cocos2d.h"
#include "Constant.h"

using namespace cocos2d;
using namespace std;

class WelcomeLayer:public Layer {
public:
	WelcomeLayer();
	~WelcomeLayer();
	bool virtual init();
	CREATE_FUNC(WelcomeLayer);

private:
	void initMenu();
	void start(Object *sender);
	void selectBoy(Object *sender);
	void config(Object *sender);
	void help(Object *sender);
	void other(Object *sender);
	void more(Object *sender);
	int selected;
};