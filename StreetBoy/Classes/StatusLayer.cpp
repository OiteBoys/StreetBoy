#include "StatusLayer.h"
#include "GameScene.h"
#include "WelcomeScene.h"

StatusLayer::StatusLayer() {
}

StatusLayer::~StatusLayer() {
}

bool StatusLayer::init() {
	if(Layer::init()) {
		this->menu = Menu::create();
		menu->setPosition(Point::ZERO);
		this->addChild(menu);
		return true;
	}else {
		return false;
	}
}

void StatusLayer::start() {
	// init the pause button
	Size winSize = Director::getInstance()->getWinSize();
	auto pauseNormal = SPRITE("pause.png");
	auto pauseActive = SPRITE("continue.png");
	this->pause = MenuItemSprite::create(pauseNormal,pauseActive,pauseNormal, CC_CALLBACK_1(StatusLayer::menuPauseCallback,this));
	this->pause->setPosition(pauseNormal->getContentSize().width/2, winSize.height - pauseNormal->getContentSize().height/2);
	this->menu->addChild(pause);

	this->scoreLabel = LabelBMFont::create("0", "number.fnt");
	this->scoreLabel->setPosition(winSize.width/2, winSize.height - scoreLabel->getContentSize().height);
	this->addChild(this->scoreLabel);
}

void StatusLayer::playing(int score) {
	char scoreStr[50] = {0};
	sprintf(scoreStr, "%d", score);
	this->scoreLabel->setString(scoreStr, true);
}

void StatusLayer::menuPauseCallback(Object* pSender) {
}

void StatusLayer::gameOver(int score){
	Size winSize = Director::getInstance()->getWinSize();
	this->pause->removeFromParent();
	this->scoreLabel->removeFromParent();

	//get the best score
	int bestScore = UserRecord::getInstance()->readIntegerFromUserDefault("best_score");
	//update the best score
	if(score > bestScore){
		UserRecord::getInstance()->saveIntegerToUserDefault("best_score", score);
	}

	// show score panel
	scorePanel = Node::create();
	scorePanel->setPosition(winSize.width/2, winSize.height/2);
	this->addChild(scorePanel);

	auto title = SPRITE("scores.png");
	title->setPosition(GAME_OVER_SCORE_POSITION);
	scorePanel->addChild(title);

	auto distanceTitle = SPRITE("distance.png");
	distanceTitle->setPosition(GAME_OVER_DISTANCE_POSITION);
	scorePanel->addChild(distanceTitle);

	auto bestTitle = SPRITE("personal_best.png");
	bestTitle->setPosition(GAME_OVER_BEST_POSITION);
	scorePanel->addChild(bestTitle);

	auto distanceBg = SPRITE("menu_none.png");
	char scoreStr[50] = {0};
	sprintf(scoreStr, "%d", score);
	auto distance = LabelBMFont::create(scoreStr, "number.fnt");
	distance->setPosition(distanceBg->getContentSize().width/2, distanceBg->getContentSize().height/2);
	distanceBg->addChild(distance);
	distanceBg->setPosition(GAME_OVER_DISTANCE_VALUE_POSITION);
	scorePanel->addChild(distanceBg);

	auto bestBg = SPRITE("menu_none.png");
	sprintf(scoreStr, "%d", bestScore);
	auto best = LabelBMFont::create(scoreStr, "number.fnt");
	best->setPosition(bestBg->getContentSize().width/2, bestBg->getContentSize().height/2);
	bestBg->addChild(best);
	bestBg->setPosition(GAME_OVER_BEST_VALUE_POSITION);
	scorePanel->addChild(bestBg);

	// show the button delay
	this->schedule(schedule_selector(StatusLayer::showHomeAndRestartButton), 1, 1, 2);
}
	

void StatusLayer::showHomeAndRestartButton(float dt) {
	Size winSize = Director::getInstance()->getWinSize();
	auto homeNormal = SPRITE("home.png");
	auto homeSelected = SPRITE("home_selected.png");
	home = MenuItemSprite::create(homeNormal, homeSelected, homeNormal, CC_CALLBACK_1(StatusLayer::menuHomeCallback, this));
	home->setPosition(homeNormal->getContentSize().width/2, homeNormal->getContentSize().height/2);
	this->menu->addChild(home);

	auto restartNormal = SPRITE("restart.png");
	auto restartSelected = SPRITE("restart_selected.png");
	restart = MenuItemSprite::create(restartNormal, restartSelected, restartNormal, CC_CALLBACK_1(StatusLayer::menuRestartCallback, this));
	restart->setPosition(winSize.width - restartNormal->getContentSize().width/2, restartNormal->getContentSize().height/2);
	this->menu->addChild(restart);
}

void StatusLayer::menuRestartCallback(Object* sender) {
	auto scene = GameScene::create();
	auto transition = CCTransitionSplitRows::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void StatusLayer::menuHomeCallback(Object* sender) {
	auto scene = WelcomeScene::create();
	auto transition = CCTransitionSplitRows::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}