#ifndef __CreateProfileLayer__H__
#define __CreateProfileLayer__H__

#include "cocos2d.h"

USING_NS_CC;

class CreateProfileLayer : public Layer
{
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(CreateProfileLayer);

private:
	char* username;
};

#endif