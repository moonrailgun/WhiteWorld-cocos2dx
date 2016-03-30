#include "CreateProfileLayer.h"
#include "cocos2d.h"
#include "GlobalDefine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "GameLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

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

	if (getBoolFromXML(MUSIC_KEY))
	{
		float music = getFloatFromXML(MUSICVOL)*100.0f;
		audioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
		if (audioEngine->isBackgroundMusicPlaying())
		{
			audioEngine->pauseBackgroundMusic();
			audioEngine->playBackgroundMusic("sound/Field2.mp3", true);
		}
		else{
			audioEngine->playBackgroundMusic("sound/Field2.mp3", true);
		}
	}
	else
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}

	LabelTTF* title = LabelTTF::create(XMLGetString("data/base.xml", "askName"), "", 20);
	title->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 + 60);
	addChild(title);

	auto inputBox = EditBox::create(Size(360, 40), Scale9Sprite::create());
	inputBox->setName("input");
	addEditBox(inputBox, Vec2(WINSIZE.width / 2, WINSIZE.height / 2), XMLGetString("data/base.xml", "inputName"), false);

	Scale9Sprite* psc9Selected = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Unchecked.png"));
	LabelTTF* label = LabelTTF::create("enter", "", 30);
	ControlButton* button = ControlButton::create(label, psc9Selected);

	button->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2 - 100));
	button->setTitleColorForState(Color3B(255, 255, 255), Control::State::NORMAL);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(CreateProfileLayer::enterGame), Control::EventType::TOUCH_DOWN);

	this->addChild(button);

	return true;
}

void CreateProfileLayer::addEditBox(EditBox* editBox, Vec2 editPoint,const char* defaultValue, bool isPassword)
{

	editBox->setPosition(Vec2(editPoint.x, editPoint.y)); //位置
	editBox->setFontColor(Color3B(255,255,255)); //文字颜色
	editBox->setPlaceHolder(defaultValue); //输入框缺省文字
	editBox->setPlaceholderFontColor(Color3B(255, 255, 255)); //缺省文字颜色
	editBox->setMaxLength(20); //最大长度
	editBox->setReturnType(EditBox::KeyboardReturnType::DONE); //默认使用键盘return类型为Done
	if (isPassword) {
		editBox->setInputFlag(EditBox::InputFlag::PASSWORD); //输入密码时的替代符
	}
	//editBox->setDelegate(this); //设置委托代理对象为当前类
	this->addChild(editBox);
}

void CreateProfileLayer::enterGame(CCObject *object, Control::EventType controlEvent){
	auto input = this->getChildByName("input");
	EditBox* editbox = (EditBox*)input;
	const char* playerName = editbox->getText();
	
	log("playername: %s", playerName);
	log("is creating profile");

	log("have not finished.");

	Director::getInstance()->replaceScene(GameLayer::createScene());
}