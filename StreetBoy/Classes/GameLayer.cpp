#include "GameLayer.h"

GameLayer::GameLayer() {}

GameLayer::~GameLayer(){}

bool GameLayer::init() {
	if(Layer::init()) {
		// add ground
		initGround();
		groundShift = schedule_selector(GameLayer::scrollGround);
		this->schedule(groundShift, 0.01f);

		// add the boy
		initBoy();
		return true;
	}else {
		return false;
	}
}

void GameLayer::onTouchLeft() {
	// boy slide
}

void GameLayer::onTouchRight() {
	// boy jump
}

void GameLayer::initBoy() {
	boy = BoySprite::getInstance();
	boy->setPosition(GAME_BOY_POSITION_X, ground1->getPositionY() + ground1->getContentSize().height + boy->getContentSize().height/2);
	boy->run();
	this->addChild(boy);
}


void GameLayer::initGround() {
	ground1 = SPRITE("road01.png");
	ground1->setAnchorPoint(Point::ZERO);
	ground1->setPosition(0, GAME_GROUND_HEIGHT);
	this->addChild(ground1);

	ground2 = SPRITE("road01.png");
	ground2->setAnchorPoint(Point::ZERO);
	ground2->setPosition(ground1->getContentSize().width, GAME_GROUND_HEIGHT);
	this->addChild(ground2);
}

void GameLayer::scrollGround(float dt){
	this->ground1->setPositionX(this->ground1->getPositionX() - 4.0f);
	this->ground2->setPositionX(this->ground1->getPositionX() + this->ground1->getContentSize().width - 4.0f);
	if(this->ground2->getPositionX() == 0) {
		this->ground1->setPositionX(0);
	}
}