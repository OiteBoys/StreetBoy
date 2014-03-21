#pragma once
#include "cocos2d.h"
#include "Constant.h"
#include "OptionLayer.h"
#include "BoySprite.h"
#include "ObjectManager.h"

using namespace cocos2d;

typedef enum _game_status {
	GAME_STATUS_READY = 1,
	GAME_STATUS_START,
	GAME_STATUS_OVER
} GameStatus;

class StatusDelegate {
public:
	/**
	* When the game start, this method will be called
	*/
	virtual void onGameStart(void) = 0;

	/**
	* During paying, after the score changed, this method will be called
	*/
	virtual void onGamePlaying(int score) = 0;

	/**
	* When game is over, this method will be called
	*/
	virtual void onGameEnd(int score) = 0;
};

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

	/**
	* According to current game status, give the order to delegate.
	*/
	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);

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

	ObjectManager *objectManager;
	Vector<Sprite*> obstacles;
	float lastPositionX;

	bool onContactBegin(EventCustom *event, const PhysicsContact& contact);

	void gameOver();

	int score;
};