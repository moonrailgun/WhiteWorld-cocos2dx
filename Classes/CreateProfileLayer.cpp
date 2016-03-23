#include "CreateProfileLayer.h"
#include "cocos2d.h"
#include "GlobalDefine.h"

using namespace cocos2d;

Scene* CreateProfileLayer::createScene()
{
	Scene* createProfileScene = Scene::create();
	CreateProfileLayer* layer = CreateProfileLayer::create();
	createProfileScene->addChild(layer);

	return createProfileScene;
}

bool CreateProfileLayer::init(){
	if (!Layer::init())
	{
		return false;
	}



	return true;
}