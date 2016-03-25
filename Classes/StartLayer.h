#ifndef __StartLayer__H__
#define __StartLayer__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

class StartLayer : public Layer
{
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(StartLayer);
private:
	// 开始主界面的按钮控件监控事件
	void touchNewGame(Ref* pSender);
	void touchContinueGame(Ref* pSender);
	void touchSet(Ref* pSender);
	void touchHelp(Ref* pSender);
	
	// 图片精灵
	//Sprite* title;
	Sprite* bgPic;

	DrawNode* addonBoard;
	void showAddonBoard();
};

#endif