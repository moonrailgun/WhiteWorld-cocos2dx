#ifndef __SetLayer__H__
#define __SetLayer__H__

#include "cocos2d.h"
#include "GlobalDefine.h"

USING_NS_CC;

class SetLayer : public Layer
{
public:
	virtual bool init();
	static Layer* createLayer(int width = WINSIZE.width, int height = WINSIZE.height);
	CREATE_FUNC(SetLayer);

private:

};

#endif