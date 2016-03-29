#ifndef __Item_H__
#define __Item_H__

#include "cocos2d.h"

USING_NS_CC;

class Item :public Node{
public:
	void initItem(int id);
	Sprite* getSprite();

	void useItem();

private:
	Sprite* sprite;//物体图片
	char* itemName;//物品名字
	int itemNum;//持有数量
};

#endif