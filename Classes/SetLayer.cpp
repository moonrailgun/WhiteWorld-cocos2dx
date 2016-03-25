#include "SetLayer.h"
#include "GlobalDefine.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "ui/UICheckBox.h"
#include "XMLParser.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

Layer* SetLayer::createLayer(){
	Layer* layer = SetLayer::create();

	return layer;
}

bool SetLayer::init(){
	if (!Layer::init())
	{
		return false;
	}

	Vec2 startPos = Vec2(50, 70);

	float music = getFloatFromXML(MUSICVOL)*100.0f;
	float effect = getFloatFromXML(SOUNDVOL)*100.0f;

	//复选框
	auto musicOn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Unchecked.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Unchecked.png")));
	auto musicOff = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")));

	auto effectOn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Unchecked.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Unchecked.png")));
	auto effectOff = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")));

	auto musicToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetLayer::musicSet, this), musicOn, musicOff, NULL);
	musicToggle->setPosition(50 + startPos.x, 460 + startPos.y);
	auto effectToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetLayer::effectSet, this), effectOn, effectOff, NULL);
	effectToggle->setPosition(50 + startPos.x, 370 + startPos.y);

	if (getBoolFromXML(MUSIC_KEY)){
		musicToggle->setSelectedIndex(1);
	}
	else{
		musicToggle->setSelectedIndex(0);
	}
	if (getBoolFromXML(SOUND_KEY)){
		effectToggle->setSelectedIndex(1);
	}
	else{
		effectToggle->setSelectedIndex(0);
	}

	auto menu = Menu::create(musicToggle, effectToggle, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 2);

	//按钮背景
	auto musicBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Unchecked.png"));
	musicBg->setPosition(50 + startPos.x, 460 + startPos.y);
	this->addChild(musicBg, 1);
	auto effectBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Unchecked.png"));
	effectBg->setPosition(50 + startPos.x, 370 + startPos.y);
	this->addChild(effectBg, 1);

	//按钮文字
	auto musicLabel = LabelTTF::create(XMLParser::parseWithFile("data/base.xml")->getString("music")->getCString(), "", 26);
	musicLabel->setPosition(120 + startPos.x, 460 + startPos.y);
	this->addChild(musicLabel);
	auto effectLabel = LabelTTF::create(XMLParser::parseWithFile("data/base.xml")->getString("effect")->getCString(), "", 26);
	effectLabel->setPosition(120 + startPos.x, 370 + startPos.y);
	this->addChild(effectLabel);

	return true;
}


void SetLayer::changeMusicVol(Ref* pSender, Control::EventType type)
{
	auto temp = (ControlSlider*)pSender;
	setFloatToXML(MUSICVOL, temp->getValue() / 100.0f);
	UserDefault::getInstance()->flush();
	audioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
}

void SetLayer::changeEffectVol(Ref* pSender, Control::EventType type)
{
	auto temp = (ControlSlider*)pSender;
	setFloatToXML(SOUNDVOL, temp->getValue() / 100.0f);
	UserDefault::getInstance()->flush();
	audioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
}

void SetLayer::musicSet(Ref* pSender)
{
	auto musicTemp = (MenuItemToggle*)pSender;
	PLAYEFFECT;
	log("%d", musicTemp->getSelectedIndex());
	if (musicTemp->getSelectedIndex() == 0)
	{
		setBoolToXML(MUSIC_KEY, false);
		UserDefault::getInstance()->flush();
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	else
	{
		setBoolToXML(MUSIC_KEY, true);
		UserDefault::getInstance()->flush();
		audioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}

void SetLayer::effectSet(Ref* pSender)
{
	auto effectTemp = (MenuItemToggle*)pSender;
	log("%d", effectTemp->getSelectedIndex());
	if (effectTemp->getSelectedIndex() == 0)
	{
		setBoolToXML(SOUND_KEY, false);
		UserDefault::getInstance()->flush();
	}
	else
	{
		setBoolToXML(SOUND_KEY, true);
		UserDefault::getInstance()->flush();
	}
}