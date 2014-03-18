#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {}

bool GameScene::init() {
	if(Scene::initWithPhysics()) {
		// Add the background
		auto backgroundLayer = BackgroundLayer::create();
		if(backgroundLayer) {
			this->addChild(backgroundLayer);
		}

		// Add the game layer
		this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		this->getPhysicsWorld()->setGravity(Vect(0, -900));
		this->gameLayer = GameLayer::create();
		if(gameLayer) {
			gameLayer->setPhyWorld(this->getPhysicsWorld());
			this->addChild(gameLayer);
		}

		// Add operation layer to control the game
		auto optionLayer = OptionLayer::create();
		if(optionLayer) {
			optionLayer->setDelegator(gameLayer);
			this->addChild(optionLayer);
		}

		return true;
	}else {
		return false;
	}
}