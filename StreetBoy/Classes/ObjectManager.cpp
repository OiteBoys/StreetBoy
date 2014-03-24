#include "ObjectManager.h"

ObjectManager::ObjectManager(){}

ObjectManager::~ObjectManager(){}

bool ObjectManager::init() {
	return true;
}

Sprite* ObjectManager::createObstacle() {
	//int type = rand()%2;
	int type =0;
	if(type == 0) {
		auto obstacle = SPRITE("box.png");
		auto body = PhysicsBody::createBox(obstacle->getContentSize());
		body->setDynamic(false);
		obstacle->setPhysicsBody(body);
		return obstacle;
	}else{
		auto obstacle = Sprite::create();
		auto obstacle1 = SPRITE("box.png");
		auto obstacle2 = SPRITE("box.png");
		obstacle1->setPosition(0, obstacle1->getContentSize().height/2);
		obstacle2->setPosition(obstacle1->getContentSize().width + ObstacleSpaceDeviation, obstacle1->getContentSize().height/2);
		obstacle->addChild(obstacle1);
		obstacle->addChild(obstacle2);
		obstacle->setContentSize(Size(obstacle1->getContentSize().width*2 + ObstacleSpaceDeviation, obstacle1->getContentSize().height));

		auto body = PhysicsBody::create();
		body->setDynamic(false);
		body->addShape(PhysicsShapeBox::create(obstacle1->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT, Point(- obstacle1->getContentSize().width/2 - ObstacleSpaceDeviation/2, 0)));
		body->addShape(PhysicsShapeBox::create(obstacle1->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT, Point(obstacle1->getContentSize().width/2 + ObstacleSpaceDeviation/2, 0)));
		obstacle->setPhysicsBody(body);
		return obstacle;
	}
}

Vector<Sprite*> ObjectManager::generalObstacles(int number) {
	auto obstacles = Vector<Sprite*>(10);
	Size winSize = Director::getInstance()->getWinSize();
	for(int i=0;i<number;i++) {
		float height = (rand()%2)*ObstacleOverHeight;
		auto obstacle = this->createObstacle();
		obstacle->setPosition(winSize.width + i*ObstacleSpace + obstacle->getContentSize().width, ObstacleYPosition + obstacle->getContentSize().height/2 + height);
		obstacle->retain();
		obstacles.pushBack(obstacle);
	}
	return obstacles;
}