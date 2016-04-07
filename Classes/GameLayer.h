#ifndef __GameLayer__H__
#define __GameLayer__H__

#include "cocos2d.h"
#include "Player.h"
#include "GameMap.h"

USING_NS_CC;

class GameLayer : public Layer{
public:
	static Scene* createScene();
	bool init();
	CREATE_FUNC(GameLayer);

	void gamePause();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void update(float delta);
	GameMap* getGameMap();
private:
	//玩家信息
	Player* _player;
	GameMap* _gameMap;

	int _isKeyNum = 0;
};

#endif