#pragma once
#include "cocos2d.h"
#include "Constant.h"

using namespace cocos2d;
using namespace std;

typedef enum{
    ACTION_STATE_RUN,
	ACTION_STATE_SLIDE,
	ACTION_STATE_DIE
} ActionState;

const int BOY_SPRITE_TAG = 10003;

class BoySprite : public Sprite {
public:
	/**
	* Default construct
	*/
	BoySprite();

	/**
	* Default distruct
	*/
	~BoySprite();

	/**
	 * Get instance
	 */
	static BoySprite* getInstance();

	/**
	* Cocos2d construct
	*/
	bool virtual init();

	/**
	 * create && init the bird
	 */
	bool createBoy();

	//CREATE_FUNC(BoySprite);

	/**
	* The bird fly with swing, but do not effected by gravity.
	*/
	void run();

	/**
	* The bird fly drived by player, effected by gravity. need physical support.
	*/
	void slide();

	/**
	* The bird die
	*/
	void die();

	/**
	* There are three type of boy in this game, this method can change the type
	*/
	void changeBoyType(int type);
	
protected:
	/**
	* This method can create a frame animation with the likey name texture.
	*/
    static cocos2d::Animation *createAnimation(const char *fmt, int boyIndex, int count, float fps);

private:
	static BoySprite* shareBoySprite;
	/**
	* This method change current status. called by fly and idle etc.
	*/
	bool changeState(ActionState state);

	Action* runningAction;

	Action* slideAction;

	Action* dieAction;

	ActionState currentStatus;

	int boyIndex;
};