/**
* All const value is defined here.
*/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#define SPRITE(__NAME__) Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(__NAME__))
#define SPRITE_FRAME(__NAME__) SpriteFrameCache::getInstance()->getSpriteFrameByName(__NAME__)

// Menu in Welcome Scene
const auto WELCOME_PANEL_POSITION = Point(400.0f, 240.0f);
const auto WELCOME_START_POSITION = Point(400.0f, 240.0f);
const auto WELCOME_BOY1_POSITION = Point(-134.0f + 400.0f, -110.0f + 240.0f);
const auto WELCOME_BOY2_POSITION = Point(8.0f + 400.0f, -110.0f + 240.0f);
const auto WELCOME_BOY3_POSITION = Point(151.0f + 400.0f, -110.0f + 240.0f);
const auto WELCOME_CONFIG_POSITION = Point(54.0f, 50.0f);
const auto WELCOME_HELP_POSITION = Point(156.0f, 50.0f);
const auto WELCOME_MORE_POSITION = Point(755.0f, 50.0f);

// Ground height in the game scene
const auto GAME_GROUND_HEIGHT = 80.0f;
const auto GAME_BOY_POSITION_X = 150.0f;
