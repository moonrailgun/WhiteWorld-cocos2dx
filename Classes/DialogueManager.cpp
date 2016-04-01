#include "DialogueManager.h"
#include "GlobalDefine.h"

USING_NS_CC;

bool DialogueManager::init(){
	//对话框
	this->_dialogueBg = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("textBox.png"));
	this->_dialogueBg->setName("dialogueBg");
	this->_dialogueBg->setPreferredSize(Size(WINSIZE.width * 0.8, WINSIZE.height * 0.25));
	this->_dialogueBg->setPosition(WINSIZE.width / 2, WINSIZE.height / 5);

	//文本
	this->_dialogueText = LabelTTF::create("","",26);
	this->_dialogueText->setDimensions(this->_dialogueBg->getPreferredSize() - Size(40,20));
	this->_dialogueText->setColor(Color3B(16, 16, 16));
	this->_dialogueText->setAnchorPoint(Vec2(0.5, 0.5));
	this->_dialogueText->setHorizontalAlignment(TextHAlignment::LEFT);
	this->_dialogueText->setPosition(this->_dialogueBg->getPosition());

	this->retain();

	return true;
}

bool DialogueManager::loadDialogueFromFile(char* fileName){
	auto fileUrl = String::createWithFormat("data/dialogue/%s.xml", fileName);

	log("is loading file %s", fileUrl);
	log("have not finished");

	return true;
}

void DialogueManager::showDialogue(Layer* layer){
	auto dialogueBg = layer->getChildByName("dialogueBg");
	if (dialogueBg == NULL){
		layer->addChild(this->_dialogueBg);
		layer->addChild(this->_dialogueText);
	}
}

void DialogueManager::updateDialogueText(char* text){
	if (_dialogueText != NULL){
		_dialogueText->setString(text);
	}
	else{
		log("variable _dialogueText is null");
	}
}