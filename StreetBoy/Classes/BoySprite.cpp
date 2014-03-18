#include "BoySprite.h"

BoySprite::BoySprite() {
}

BoySprite::~BoySprite() {
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

		auto slide = this->createAnimation("boy%02d_slide%02d.png",this->boyIndex, 4, 4);
		this->slideAction = RepeatForever::create(Animate::create(slide));

		auto jump = this->createAnimation("boy%02d_jump%02d.png",this->boyIndex, 2, 2);
		this->jumpAction = Animate::create(jump);

		return true;
	}else {
		return false;
	}
}

void BoySprite::changeBoyType(int type) {
}


void BoySprite::run() {
	if (changeState(ACTION_STATE_RUN)) {
        this->runAction(runningAction);
    }
}

void BoySprite::slide() {
	if(changeState(ACTION_STATE_SLIDE)) {
		this->runAction(slideAction);
	}
}

void BoySprite::jump() {
	if(changeState(ACTION_STATE_JUMP)) {
		//this->runAction(jumpAction);
	}
}

void BoySprite::die() {
	if(changeState(ACTION_STATE_DIE)) {
		this->stopAllActions();
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
