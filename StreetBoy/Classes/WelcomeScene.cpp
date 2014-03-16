#include "WelcomeScene.h"

WelcomeScene::WelcomeScene(){}

WelcomeScene::~WelcomeScene(){}

bool WelcomeScene::init() {
	if(Scene::init()) {

		this->welcomeLayer = WelcomeLayer::create();
		if(this->welcomeLayer != NULL) {
			this->addChild(this->welcomeLayer);
		}
		return true;
	} else  {
		return false;
	}
}