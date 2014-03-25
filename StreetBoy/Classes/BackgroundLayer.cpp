#include "BackgroundLayer.h"
#include "Constant.h"
BackgroundLayer::BackgroundLayer(){};
BackgroundLayer::~BackgroundLayer(){};

bool BackgroundLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//get the current time, the background image will selected by current time day or night: bg_day or bg_night
	time_t t = time(NULL);
	tm* lt = localtime(&t);
	int hour = lt->tm_hour;
	//create the background image according to the current time;
	
	//background1 = SPRITE("background_01.png");
	background1 = Sprite::create("background.png",CCRectMake(0,0,798,480));
	background1->getTexture()->setAntiAliasTexParameters();
	background1->setAnchorPoint(Point::ZERO);
	background1->setPosition(Point::ZERO);
	this->addChild(background1);

	//background2 = SPRITE("background_01.png");
	background2 = Sprite::create("background.png",CCRectMake(0,0,798,480));
	background2->getTexture()->setAntiAliasTexParameters();
	background2->setAnchorPoint(Point::ZERO);
	background2->setPosition(this->background1->getContentSize().width - 2.0f,0);
	this->addChild(background2);

	// scroll the background
	backgroundShift = schedule_selector(BackgroundLayer::scrollBackground);
    this->schedule(backgroundShift, 0.01f);
	return true;
}

void BackgroundLayer::scrollBackground(float dt){
	this->background1->setPositionX(this->background1->getPositionX() - 1.0f);
	this->background2->setPositionX(this->background1->getPositionX() + this->background1->getContentSize().width - 1.0f);
	if(this->background2->getPositionX() == 0) {
		this->background1->setPositionX(0);
	}
}

void BackgroundLayer::stop() {
	this->unschedule(backgroundShift);
}

void BackgroundLayer::restart() {
	this->schedule(backgroundShift, 0.01f);
}
