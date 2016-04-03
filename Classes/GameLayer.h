#ifndef __GameLayer__H__
#define __GameLayer__H__

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

enum EntityDirection{
	Up,Down,Left,Right
};

class GameLayer : public Layer{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameLayer);

	void gamePause();

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
private:
	//玩家信息
	Player* _player;
	EntityDirection _playerDirection;
	int _playerSpeed;
};

#endif