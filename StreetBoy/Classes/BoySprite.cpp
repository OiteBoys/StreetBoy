#include "BoySprite.h"

BoySprite::BoySprite() {
}

BoySprite::~BoySprite() {
	this->runningAction->release();
	this->slideAction->release();
	this->jumpUpAction->release();
	this->jumpDownAction->release();
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
	return shareBoySprite;
}

bool BoySprite::init() {
	char name[50] = {0};
	this->boyIndex = 1;
	sprintf(name, "boy%02d_run01.png", this->boyIndex);
	if(Sprite::initWithSpriteFrame(SPRITE_FRAME(name))) {
		auto running = this->createAnimation("boy%02d_run%02d.png",this->boyIndex, 8, 8);
		this->runningAction = RepeatForever::create(Animate::create(running));
		this->runningAction->setTag(ACTION_STATE_RUN_TAG);
		// void released by system
		this->runningAction->retain();

		auto slide = this->createAnimation("boy%02d_slide%02d.png",this->boyIndex, 4, 4);
		this->slideAction = RepeatForever::create(Animate::create(slide));
		this->slideAction->setTag(ACTION_STATE_SLIDE_TAG);
		this->slideAction->retain();

		auto jumpUp = this->createAnimation("boy%02d_jump01.png",this->boyIndex, 1, 1);
		this->jumpUpAction = Animate::create(jumpUp);
		this->jumpUpAction->setTag(ACTION_STATE_JUMP_UP_TAG);
		this->jumpUpAction->retain();

		auto jumpDown = this->createAnimation("boy%02d_jump02.png",this->boyIndex, 1, 1);
		this->jumpDownAction = Animate::create(jumpDown);
		this->jumpDownAction->setTag(ACTION_STATE_JUMP_DOWN_TAG);
		this->jumpDownAction->retain();

		return true;
	}else {
		return false;
	}
}

void BoySprite::changeBoyType(int type) {
}


void BoySprite::run() {
	if (changeState(ACTION_STATE_RUN)) {
		if(this->getPhysicsBody() == nullptr){
			PhysicsBody *body = PhysicsBody::create();
			body->addShape(PhysicsShapeBox::create(this->getContentSize()));
			body->setDynamic(true);
			body->setLinearDamping(0.0f);
			body->setRotationEnable(false);
			this->setPhysicsBody(body);
		}else {
			auto body = this->getPhysicsBody();
			body->removeAllShapes();
			body->addShape(PhysicsShapeBox::create(this->getContentSize()));
		}
        this->runAction(runningAction);
    }
}

void BoySprite::slide() {
	if(changeState(ACTION_STATE_SLIDE)) {
		this->runAction(slideAction);
	}
}

void BoySprite::jumpUp() {
	if(changeState(ACTION_STATE_JUMP_UP)) {
		this->runAction(jumpUpAction);
	}
}

void BoySprite::jumpDown() {
	if(changeState(ACTION_STATE_JUMP_DOWN)) {
		this->runAction(jumpDownAction);
	}
}

void BoySprite::die() {
	if(changeState(ACTION_STATE_DIE)) {
		this->stopAllActions();
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
	}
}

Animation* BoySprite::createAnimation(const char *fmt, int boyIndex, int count, float fps) {
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(1/fps);
	for (int i = 1; i <= count; i++){
		char name[50] = {0};
		sprintf(name, fmt, boyIndex, i);
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
