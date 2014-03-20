#pragma once
#include "cocos2d.h"
#include "Constant.h"
#include <cstdlib>
using namespace cocos2d;
using namespace std;

const auto ObstacleSpace = 200.0f;
const auto ObstacleSpaceDeviation = 10.0f;
const auto ObstacleOverHeight = 45.0f;
const auto ObstacleYPosition = GAME_GROUND_HEIGHT + 27;


class ObjectManager : public Object{
public:
	ObjectManager();

	~ObjectManager();

	bool virtual init();

	CREATE_FUNC(ObjectManager);

	Vector<Sprite*> generalObstacles(int number = 10);

	Sprite* createObstacle();
private:
	
};