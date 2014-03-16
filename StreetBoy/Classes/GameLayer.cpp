#include "GameLayer.h"

GameLayer::GameLayer() {}

GameLayer::~GameLayer(){}

bool GameLayer::init() {
	if(Layer::init()) {
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