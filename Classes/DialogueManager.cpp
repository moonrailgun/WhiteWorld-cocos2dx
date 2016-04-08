#include "DialogueManager.h"
#include "GlobalDefine.h"

USING_NS_CC;

bool DialogueManager::init(){
	this->retain();

	//对话框
	this->_dialogueBg = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("textBox.png"));
	this->_dialogueBg->setName("dialogueBg");
	this->_dialogueBg->setPreferredSize(Size(WINSIZE.width * 0.8, WINSIZE.height * 0.25));
	this->_dialogueBg->setPosition(WINSIZE.width / 2, WINSIZE.height / 5);
	this->_dialogueBg->retain();

	//文本
	this->_dialogueText = LabelTTF::create("","",26);
	this->_dialogueText->setDimensions(this->_dialogueBg->getPreferredSize() - Size(40,30));
	this->_dialogueText->setColor(Color3B(16, 16, 16));
	this->_dialogueText->setAnchorPoint(Vec2(0.5, 0.5));
	this->_dialogueText->setHorizontalAlignment(TextHAlignment::LEFT);
	this->_dialogueText->setPosition(this->_dialogueBg->getPosition());
	this->_dialogueText->retain();

	return true;
}

void DialogueManager::showDialogue(Node* node){
	auto dialogueBg = node->getChildByName("dialogueBg");
	if (dialogueBg == NULL){
		node->addChild(this->_dialogueBg);
		node->addChild(this->_dialogueText);
	}
}

void DialogueManager::hideDialogue(){
	auto parent = this->_dialogueBg->getParent();
	if (parent != NULL){
		parent->removeChild(this->_dialogueBg);
		parent->removeChild(this->_dialogueText);
	}
	else{
		log("cant remove dialogue box because cant find parent node");
	}
}

void DialogueManager::updateDialogueText(const char* text){
	if (_dialogueText != NULL){
		_dialogueText->setString(text);
	}
	else{
		log("variable _dialogueText is null");
	}
}

Scale9Sprite* DialogueManager::getDialogueBg(){
	return this->_dialogueBg;
}

DialogueManager::~DialogueManager(){
	this->_dialogueBg->release();
	this->_dialogueText->release();
	this->release();
}