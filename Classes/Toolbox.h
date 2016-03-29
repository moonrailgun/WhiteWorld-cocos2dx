#ifndef __Toolbox__H__
#define __Toolbox__H__

#include "cocos2d.h"

USING_NS_CC;

class Toolbox : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(Toolbox);

	void setItemByIndex();//根据索引设置物品
	void getSelectItem();//获取选中物体
};

#endif