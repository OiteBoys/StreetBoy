#pragma once
#include "cocos2d.h"
#include "Constant.h"

using namespace cocos2d;
using namespace std;

typedef enum{
    ACTION_STATE_RUN,
	ACTION_STATE_SLIDE,
	ACTION_STATE_JUMP_UP,
	ACTION_STATE_JUMP_DOWN,
	ACTION_STATE_DIE
} ActionState;

// define the action tag
const int ACTION_STATE_RUN_TAG = 100;
const int ACTION_STATE_SLIDE_TAG = 101;
const int ACTION_STATE_JUMP_UP_TAG = 102;
const int ACTION_STATE_JUMP_DOWN_TAG = 103;
const int ACTION_STATE_DIE_TAG = 104;

// define the sprite tag
const int BOY_SPRITE_TAG = 10003;

// define the hero shape
#define NORMAL_SHAPE  PhysicsShapeBox::create(Size(40, 58))
#define SLIDE_SHAPE  PhysicsShapeBox::create(Size(47, 23))

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
	* The boy fly with swing, but do not effected by gravity.
	*/
	void run();

	/**
	* The boy fly drived by player, effected by gravity. need physical support.
	*/
	void slide();

	/**
	* The boy die
	*/
	void die();

	/**
	* The boy jump
	*/
	void jumpUp();

	/**
	* The boy jump
	*/
	void jumpDown();

	/**
	* There are three type of boy in this game, this method can change the type
	*/
	void changeBoyType(int type);

	/**
	* Return current boy's status
	*/
	ActionState getCurrentState();

	/**
	* need to called in the main loop, the change of boy drived by time
	*/
	void step(float dt);

	void setPhysical();
	
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

	/**
	* manage the shape of the hero
	*/
	void changeShape();

	Action* runningAction;

	Action* slideAction;

	Action* dieAction;

	Action* jumpUpAction;

	Action* jumpDownAction;

	ActionState currentStatus;

	int boyIndex;
};