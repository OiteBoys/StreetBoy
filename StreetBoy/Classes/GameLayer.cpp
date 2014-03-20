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

		// init the objects
		objectManager = ObjectManager::create();
		this->obstacles = objectManager->generalObstacles();
		this->lastPositionX = this->obstacles.at(this->obstacles.size() - 1)->getPositionX();
		for(auto object : obstacles) {
			object->setTag(1);
			this->addChild(object);
		}

		 this->scheduleUpdate();

		 auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = CC_CALLBACK_2(GameLayer::onContactBegin, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
		return true;
	}else {
		return false;
	}
}

bool GameLayer::onContactBegin(EventCustom *event, const PhysicsContact& contact) {
	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (spriteA->getTag() == 1 && spriteB->getTag() == 3){
		gameOver();
    }

	if (spriteB->getTag() == 1 && spriteA->getTag() == 3){
        gameOver();
    }

	return true;
}

void GameLayer::gameOver() {
	this->unschedule(groundShift);
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
		this->boy->getPhysicsBody()->setVelocity(Vect(0, 300));
	}
}

void GameLayer::update(float dt) {
	this->boy->step(dt);
}

void GameLayer::initBoy() {
	boy = BoySprite::getInstance();
	boy->setTag(3);
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
	groundNode->setTag(2);
    auto groundBody = PhysicsBody::create();
	groundBody->addShape(PhysicsShapeBox::create(Size(winSize.width, ground1->getContentSize().height)));
    groundBody->setDynamic(false);
    groundBody->setLinearDamping(0.0f);
    groundNode->setPhysicsBody(groundBody);
	groundNode->setPosition(winSize.width/2, GAME_GROUND_HEIGHT);
    this->addChild(groundNode);
}

void GameLayer::scrollGround(float dt){
	Size winSize = Director::getInstance()->getWinSize();
	this->ground1->setPositionX(this->ground1->getPositionX() - 4.0f);
	this->ground2->setPositionX(this->ground1->getPositionX() + this->ground1->getContentSize().width - 4.0f);
	if(this->ground2->getPositionX() == 0) {
		this->ground1->setPositionX(0);
	}

	this->lastPositionX -= 4;
	for(auto obstacle: this->obstacles) {
		obstacle->setPositionX(obstacle->getPositionX() - 4.0f);
		if(obstacle->getPositionX() < - obstacle->getContentSize().width) {
			/*obstacle->removeFromParent();
			this->obstacles.eraseObject(obstacle);*/
			obstacle->setPosition(lastPositionX + ObstacleSpace + obstacle->getContentSize().width, ObstacleYPosition + obstacle->getContentSize().height/2);
			lastPositionX = obstacle->getPositionX();
			//this->obstacles.pushBack(obs);
		}
	}
}