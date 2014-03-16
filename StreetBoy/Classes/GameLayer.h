#pragma once
#include "cocos2d.h"
#include "OptionLayer.h"

using namespace cocos2d;

class GameLayer : public Layer , public OptionDelegate {
public:
	GameLayer();
	~GameLayer();
	bool virtual init();
	CREATE_FUNC(GameLayer);

	/**
	* This layer need physical engine work
	*/
	void setPhyWorld(PhysicsWorld* world){this->world = world;}

	void onTouchLeft();
	void onTouchRight();

private:
	PhysicsWorld *world;
};