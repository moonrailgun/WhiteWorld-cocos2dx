#ifndef __Player__H__
#define __Player__H__

#include "cocos2d.h"
USING_NS_CC;

enum EntityDirection{
	Up, Down, Left, Right
};

class Player : public Node
{
public:
	// 根据图片名创建英雄
	bool init();
	// 返回当前玩家对象
	Sprite* getSprite();
	//设置玩家名
	void setName(char* playerName);
	// 返回玩家名
	char* getName();

	// 设置动画
	void setAnimation(const char *frameName, float delay);
	// 停止动画
	void stopAnimation();

	// HP & MP 值
	float currentHp;
	float totalHp;
	float currentMp;
	float totalMp;

	// 状态
	bool isHurt;
	bool isMove;
	EntityDirection direction;

	float percentage;

	float currentSpeed;
	float maxSpeed;

	CREATE_FUNC(Player);
private:
	Sprite* _playerSprite; // 精灵
	char* _playerName; 
};
#endif