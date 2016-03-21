#include "SplashLayer.h"
#include "GlobalDefine.h"
#include "SimpleAudioEngine.h"
#include "StartLayer.h"

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
	this->schedule(schedule_selector(SplashLayer::nextScene), 1, 1, 1);

	return true;
}

void SplashLayer::loadingTextureCallBack(Texture2D *texture){

}

void SplashLayer::loadingAudio()
{
	
}

void SplashLayer::initUserData()
{
	setBoolToXML(SOUND_KEY, true);
	setBoolToXML(MUSIC_KEY, true);
	UserDefault::getInstance()->flush();//ˢ��
}

void SplashLayer::nextScene(float dt)
{
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, StartLayer::createScene()));
}

void SplashLayer::onExit()
{
	Layer::onExit();
	//_loadingAudioThread->join();
	//CC_SAFE_DELETE(_loadingAudioThread);
	this->unschedule(schedule_selector(SplashLayer::nextScene));
}