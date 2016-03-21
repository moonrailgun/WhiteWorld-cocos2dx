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
	// ��ʼ������İ�ť�ؼ�����¼�
	void touchSet(Ref* pSender);
	void touchLib(Ref* pSender);
	void touchMiJi(Ref* pSender);
	void touchCG(Ref* pSender);
	void touchTZ(Ref* pSender);
	void touchHelp(Ref* pSender);

	// ͼƬ����
	Sprite* title;
	Sprite* bgPic;

};

#endif