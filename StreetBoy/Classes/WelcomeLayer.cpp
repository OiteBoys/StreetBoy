#include "WelcomeLayer.h"

WelcomeLayer::WelcomeLayer(){}

WelcomeLayer::~WelcomeLayer(){}

bool WelcomeLayer::init() {
	if(Layer::init()) {
		// Add the background
		auto spriteFrameCache = SpriteFrameCache::getInstance();
		auto background = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("background_04.png"));
		background->setAnchorPoint(Point::ZERO);
		this->addChild(background);

		this->selected = 1;
		this->initMenu();
		return true;
	}else {
		return false;
	}
}

void WelcomeLayer::initMenu() {
	// Add the menu panel
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	auto panel = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("select_background.png"));
	panel->setPosition(WELCOME_PANEL_POSITION);
	this->addChild(panel);

	auto menu = Menu::create();
	menu->setPosition(Point::ZERO);
	menu->setTag(100);
	this->addChild(menu);

	// Add the start button
	auto start = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("start.png"));
	auto startSelected = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("start_selected.png"));
	auto startMenuItem = MenuItemSprite::create(start, startSelected, start, CC_CALLBACK_1(WelcomeLayer::start, this));
	startMenuItem->setPosition(WELCOME_START_POSITION);
	menu->addChild(startMenuItem);

	// Add the boy
	for(int i=1; i<=3; i++) {
		char boyName[50] = {0};
		if(i == this->selected){
			sprintf(boyName, "boy%02d_selected.png", i);
		}else {
			sprintf(boyName, "boy%02d.png", i);
		}
		auto boy = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName(boyName));
		sprintf(boyName, "boy%02d_selected.png", i);
		auto boySelected = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName(boyName));
		auto boyMenuItem = MenuItemSprite::create(boy, boySelected, boy, CC_CALLBACK_1(WelcomeLayer::selectBoy, this));
		switch (i){
		case 1: boyMenuItem->setPosition(WELCOME_BOY1_POSITION); break;
		case 2: boyMenuItem->setPosition(WELCOME_BOY2_POSITION); break;
		case 3: boyMenuItem->setPosition(WELCOME_BOY3_POSITION); break;
		default:break;
		}
		boyMenuItem->setTag(i);
		menu->addChild(boyMenuItem);
	}

	// Add other button
	auto config = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("config.png"));
	auto configSelected = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("config_selected.png"));
	auto configMenuItem = MenuItemSprite::create(config, configSelected, config, CC_CALLBACK_1(WelcomeLayer::config, this));
	configMenuItem->setPosition(WELCOME_CONFIG_POSITION);
	menu->addChild(configMenuItem);

	// Add help button
	auto help = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("help.png"));
	auto helpSelected = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("help_selected.png"));
	auto helpMenuItem = MenuItemSprite::create(help, helpSelected, help, CC_CALLBACK_1(WelcomeLayer::help, this));
	helpMenuItem->setPosition(WELCOME_HELP_POSITION);
	menu->addChild(helpMenuItem);

	// Add more button
	auto other = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("other.png"));
	auto otherSelected = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("other_selected.png"));
	auto otherMenuItem = MenuItemSprite::create(other, otherSelected, other, CC_CALLBACK_1(WelcomeLayer::more, this));
	otherMenuItem->setPosition(WELCOME_MORE_POSITION);
	menu->addChild(otherMenuItem);
}

void WelcomeLayer::start(Object *sender) {
}

void WelcomeLayer::selectBoy(Object *sender) {
	auto menuItemSprite = (MenuItemSprite*)sender;
	auto menu = (Menu *) this->getChildByTag(100);
	auto menuItemSelected = (MenuItemSprite *) menu->getChildByTag(this->selected);
	char name[50] = {0};
	sprintf(name, "boy%02d.png", this->selected);
	menuItemSelected->setNormalImage(SPRITE(name));
	this->selected = menuItemSprite->getTag();
	sprintf(name, "boy%02d_selected.png", this->selected);
	menuItemSprite->setNormalImage(SPRITE(name));
}

void WelcomeLayer::help(Object *sender) {
}

void WelcomeLayer::more(Object *sender) {
}

void WelcomeLayer::other(Object *sender) {
}

void WelcomeLayer::config(Object *sender) {
}