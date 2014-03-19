#pragma once
#include "cocos2d.h"
#include "Constant.h"
#include "OptionLayer.h"
#include "BoySprite.h"

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

	// ground
	Sprite* ground1;
	Sprite* ground2;
	SEL_SCHEDULE groundShift;
	void initGround();
	void scrollGround(float dt);

	// boys
	BoySprite* boy;
	void initBoy();

	void update(float dt);
};