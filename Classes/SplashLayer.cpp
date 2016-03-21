#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
#include "SplashLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* SplashLayer::createScene()
{
	Scene* splashScene = Scene::create();
	SplashLayer* layer = SplashLayer::create();
	splashScene->addChild(layer);
	return splashScene;
}

bool SplashLayer::init(){
	if (!Layer::init())
	{
		return false;
	}

	// ��ʼ��logo����
	logoSprite = Sprite::create("logo.png");
	logoSprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(logoSprite);

	// �״����г�ʼ���û�����
	if (!getBoolFromXML("_IS_EXISTED"))
	{
		initUserData();
		setBoolToXML("_IS_EXISTED", true);
		UserDefault::getInstance()->flush();
	}

	setFloatToXML(SOUNDVOL, 0.80f);
	setFloatToXML(MUSICVOL, 0.35f);
	UserDefault::getInstance()->flush();

	//todo �л����¸�����

	return true;
}

void SplashLayer::loadingTextureCallBack(Texture2D *texture){

}

void SplashLayer::loadingAudio()
{

}

void SplashLayer::initUserData()
{

}

void SplashLayer::nextScene(float dt)
{

}

void SplashLayer::onExit()
{
	Layer::onExit();
	_loadingAudioThread->join();
	CC_SAFE_DELETE(_loadingAudioThread);
	this->unschedule(schedule_selector(SplashLayer::nextScene));
}