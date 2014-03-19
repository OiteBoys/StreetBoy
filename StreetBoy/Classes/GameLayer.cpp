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

		 this->scheduleUpdate();
		return true;
	}else {
		return false;
	}
}

void GameLayer::onTouchLeft() {
	// boy slide
	if(boy->getCurrentState() != ActionState::ACTION_STATE_SLIDE) {
		this->boy->slide();
	}
}

void GameLayer::onTouchRight() {
	// boy jump
	if(boy->getCurrentState() != ActionState::ACTION_STATE_JUMP_UP || boy->getCurrentState() != ActionState::ACTION_STATE_JUMP_DOWN) {
		this->boy->jumpUp();
		this->boy->getPhysicsBody()->setVelocity(Vect(0, 400));
	}
}

void GameLayer::update(float dt) {
	this->boy->step(dt);
}

void GameLayer::initBoy() {
	boy = BoySprite::getInstance();
	boy->setPosition(GAME_BOY_POSITION_X, ground1->getPositionY() + ground1->getContentSize().height/2 + boy->getContentSize().height/2);
	boy->run();
	this->addChild(boy);
}


void GameLayer::initGround() {
	ground1 = SPRITE("road01.png");
	ground1->setAnchorPoint(Point(0, 0.5));
	ground1->setPosition(0, GAME_GROUND_HEIGHT);
	this->addChild(ground1);

	ground2 = SPRITE("road01.png");
	ground2->setAnchorPoint(Point(0, 0.5));
	ground2->setPosition(ground1->getContentSize().width, GAME_GROUND_HEIGHT);
	this->addChild(ground2);

	Size winSize = Director::getInstance()->getWinSize();
	auto groundNode = Node::create();
    auto groundBody = PhysicsBody::create();
	groundBody->addShape(PhysicsShapeBox::create(Size(winSize.width, ground1->getContentSize().height)));
    groundBody->setDynamic(false);
    groundBody->setLinearDamping(0.0f);
    groundNode->setPhysicsBody(groundBody);
	groundNode->setPosition(winSize.width/2, GAME_GROUND_HEIGHT);
    this->addChild(groundNode);
}

void GameLayer::scrollGround(float dt){
	this->ground1->setPositionX(this->ground1->getPositionX() - 4.0f);
	this->ground2->setPositionX(this->ground1->getPositionX() + this->ground1->getContentSize().width - 4.0f);
	if(this->ground2->getPositionX() == 0) {
		this->ground1->setPositionX(0);
	}
}