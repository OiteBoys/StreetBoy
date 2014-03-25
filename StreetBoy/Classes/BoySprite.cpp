#include "BoySprite.h"

BoySprite::BoySprite() {
}

BoySprite::~BoySprite() {
	this->runningAction->release();
	this->slideAction->release();
	this->jumpUpAction->release();
	this->jumpDownAction->release();
	this->dieAction->release();
}

BoySprite* BoySprite::shareBoySprite = nullptr;

BoySprite* BoySprite::getInstance(){
	if(shareBoySprite == NULL){
		shareBoySprite = new BoySprite();
		if(!shareBoySprite->init()){
			delete(shareBoySprite);
			shareBoySprite = NULL;
			CCLOG("ERROR: Could not init shareBoySprite");
		}
	}
	shareBoySprite->getPhysicsBody()->setEnable(true);
	return shareBoySprite;
}

bool BoySprite::init() {
	char name[50] = {0};
	this->boyIndex = 1;
	// add the this->boyIndex if there are more than one boys
	sprintf(name, "run0000.png");
	if(Sprite::initWithSpriteFrame(SPRITE_FRAME(name))) {
		auto running = this->createAnimation("run00%02d.png",this->boyIndex, 15, 4);
		this->runningAction = RepeatForever::create(Animate::create(running));
		this->runningAction->setTag(ACTION_STATE_RUN_TAG);
		// void released by system
		this->runningAction->retain();

		auto slide = this->createAnimation("slide00%02d.png",this->boyIndex, 15, 4);
		this->slideAction = RepeatForever::create(Animate::create(slide));
		this->slideAction->setTag(ACTION_STATE_SLIDE_TAG);
		this->slideAction->retain();

		auto jumpUp = this->createAnimation("jump0100%02d.png",this->boyIndex, 10, 2);
		this->jumpUpAction = Animate::create(jumpUp);
		this->jumpUpAction->setTag(ACTION_STATE_JUMP_UP_TAG);
		this->jumpUpAction->retain();

		auto jumpDown = this->createAnimation("jump0200%0d.png",this->boyIndex, 12, 2);
		this->jumpDownAction = Animate::create(jumpDown);
		this->jumpDownAction->setTag(ACTION_STATE_JUMP_DOWN_TAG);
		this->jumpDownAction->retain();

		this->dieAction = RotateBy::create(0.1f, -45);
		dieAction->retain();

		this->setPhysical();

		return true;
	}else {
		return false;
	}
}

void BoySprite::setPhysical() {
	// add the physical body
	PhysicsBody *body = PhysicsBody::create();
	body->addShape(NORMAL_SHAPE);
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
}

void BoySprite::changeBoyType(int type) {
}

void BoySprite::changeShape(){
	if(this->getPhysicsBody() == nullptr){
		return;
	}

	auto body = this->getPhysicsBody();
	body->removeAllShapes();
	if(this->getCurrentState() == ACTION_STATE_RUN) {
		body->addShape(NORMAL_SHAPE);
	}else if(this->getCurrentState() == ACTION_STATE_SLIDE){
		body->addShape(SLIDE_SHAPE);
	}else if(this->getCurrentState() == ACTION_STATE_JUMP_UP){
		body->addShape(NORMAL_SHAPE);
	}else if(this->getCurrentState() == ACTION_STATE_JUMP_DOWN){
		body->addShape(NORMAL_SHAPE);
	}
}

void BoySprite::run() {
	if (changeState(ACTION_STATE_RUN)) {
		this->changeShape();
        this->runAction(runningAction);
    }
}

void BoySprite::slide() {
	if(changeState(ACTION_STATE_SLIDE)) {
		this->changeShape();
		this->runAction(slideAction);
	}
}

void BoySprite::jumpUp() {
	if(changeState(ACTION_STATE_JUMP_UP)) {
		this->changeShape();
		this->runAction(jumpUpAction);
	}
}

void BoySprite::jumpDown() {
	if(changeState(ACTION_STATE_JUMP_DOWN)) {
		this->changeShape();
		this->runAction(jumpDownAction);
	}
}

void BoySprite::die() {
	if(changeState(ACTION_STATE_DIE)) {
		//this->setAnchorPoint(Point(1, 0));
		this->runAction(this->dieAction);
	}
}

void BoySprite::step(float dt) {
	Point vel = this->getPhysicsBody()->getVelocity();
	if(this->currentStatus == ACTION_STATE_JUMP_UP) {
		if(vel.y < 0.01) {
			this->jumpDown();
		}
	}else if(this->currentStatus == ACTION_STATE_JUMP_DOWN) {
		if((this->getPositionY() <= (27 + GAME_GROUND_HEIGHT + this->getContentSize().height/2 + 3)) && vel.y < 0.01 ){
			this->run();
		}
	}else if(this->currentStatus == ACTION_STATE_DIE) {
		if(this->getPositionY() < 0) {
			this->getPhysicsBody()->setEnable(false);
			this->removeFromParent();
		}
	}
}

Animation* BoySprite::createAnimation(const char *fmt, int boyIndex, int count, float fps) {
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(1/fps);
	for (int i = 0; i <= count; i++){
		char name[50] = {0};
		//sprintf(name, fmt, boyIndex, i);
		sprintf(name,fmt,i);
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animation->addSpriteFrame(frame);
	}
	return animation;
}

bool BoySprite::changeState(ActionState state) {
    this->stopAllActions();
    currentStatus = state;
    return true;
}

ActionState BoySprite::getCurrentState() {
	return this->currentStatus;
}
