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

	// 初始化logo精灵
	logoSprite = Sprite::create("logo.png");
	logoSprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(logoSprite);

	// 首次运行初始化用户数据
	if (!getBoolFromXML("_IS_EXISTED"))
	{
		initUserData();
		setBoolToXML("_IS_EXISTED", true);
		UserDefault::getInstance()->flush();
	}

	setFloatToXML(SOUNDVOL, 0.80f);
	setFloatToXML(MUSICVOL, 0.35f);
	UserDefault::getInstance()->flush();

	//todo 切换到下个场景

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