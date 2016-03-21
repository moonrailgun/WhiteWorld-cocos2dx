#ifndef __SplashScene__H__
#define __SplashScene__H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class SplashLayer : public Layer
{
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(SplashLayer);

private:
	Sprite* logoSprite;
	// �����л�
	void nextScene(float dt);
	void loadingTextureCallBack(Texture2D * texture);
	void loadingAudio();
	void onExit();
	// ��ʼ���û�����
	void initUserData();
	int m_iNumOfLoad;
	std::thread* _loadingAudioThread;
};

#endif