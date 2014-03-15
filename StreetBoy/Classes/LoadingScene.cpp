#include "LoadingScene.h"
LoadingScene::LoadingScene(){}

LoadingScene::~LoadingScene(){}

bool LoadingScene::init() {
	if(Scene::init()){
		return true;
	} else {
		return false;
	}
}

void LoadingScene::onEnter(){
	// add background to current scene
	Sprite *background = Sprite::create("loading.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	background->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
	this->addChild(background);

	// start ansyc method load the atlas.png
	Director::getInstance()->getTextureCache()->addImageAsync("street_boy.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
}

void LoadingScene::loadingCallBack(Texture2D *texture){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("street_boy.plist", texture);

	// After loading the texture , preload all the sound

	// After load all the things, change the scene to new one
	//auto scene = HelloWorld::createScene();
	auto scene = HelloWorld::createScene();
	auto transition = CCTransitionSplitRows::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}