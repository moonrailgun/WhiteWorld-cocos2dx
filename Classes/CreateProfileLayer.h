#ifndef __CreateProfileLayer__H__
#define __CreateProfileLayer__H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CreateProfileLayer : public Layer
{
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(CreateProfileLayer);

private:
	char* username;
	void addEditBox(EditBox* editBox, Vec2 editPoint,const char * defaultValue, bool isPassword);
	void enterGame(CCObject *object, Control::EventType controlEvent);
};

#endif