#ifndef __GameLayer__H__
#define __GameLayer__H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
#include "GlobalData.h"
#include "MapManager.h"

USING_NS_CC;

class GameLayer : public Layer{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameLayer);

	void gamePause();
};

#endif