#ifndef __SetLayer__H__
#define __SetLayer__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GlobalDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SetLayer : public Layer
{
public:
	virtual bool init();
	static Layer* createLayer();
	CREATE_FUNC(SetLayer);

	void changeMusicVol(Ref* pSender, Control::EventType type);
	void changeEffectVol(Ref* pSender, Control::EventType type);
	void musicSet(Ref* pSender);
	void effectSet(Ref* pSender);
private:

};

#endif