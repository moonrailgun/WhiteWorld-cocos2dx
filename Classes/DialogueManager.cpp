#include "DialogueManager.h"
#include "GlobalDefine.h"
#include "PointHelper.h"

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
	this->_dialogueText = LabelTTF::create("", "", 26);
	this->_dialogueText->setDimensions(this->_dialogueBg->getPreferredSize() - Size(40, 30));
	this->_dialogueText->setColor(Color3B(16, 16, 16));
	this->_dialogueText->setAnchorPoint(Vec2(0.5, 0.5));
	this->_dialogueText->setHorizontalAlignment(TextHAlignment::LEFT);
	this->_dialogueText->setPosition(this->_dialogueBg->getPosition());
	this->_dialogueText->retain();

	//选项
	this->_dialogueMenu = Menu::create();
	this->_dialogueMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->_dialogueMenu->setPosition(PointHelper::getNodeMiddleTopPoint(_dialogueBg) - Vec2(0, 30));
	this->_dialogueMenu->retain();

	return true;
}

void DialogueManager::showDialogue(Node* node){
	auto dialogueBg = node->getChildByName("dialogueBg");
	if (dialogueBg == NULL){
		node->addChild(this->_dialogueBg);
		node->addChild(this->_dialogueText);
		node->addChild(this->_dialogueMenu);
	}
}

void DialogueManager::hideDialogue(){
	auto parent = this->_dialogueBg->getParent();
	if (parent != NULL){
		parent->removeChild(this->_dialogueBg);
		parent->removeChild(this->_dialogueText);
		parent->removeChild(this->_dialogueMenu);
	}
	else{
		log("cant remove dialogue box because cant find parent node");
	}
}

void DialogueManager::updateDialogueText(const char* text){
	if (_dialogueText != NULL && _dialogueText->getParent() != NULL){
		_dialogueText->setString(text);
	}
	else{
		log("variable _dialogueText is null");
	}
}

void DialogueManager::updateDialogueOptions(std::vector<Option> options, std::function<void(const char*, int)> &onSelected){
	if (_dialogueText != NULL && _dialogueText->getParent() != NULL){
		_dialogueText->setString("");
	}
	else{
		log("variable _dialogueText is null");
	}

	Size labelDimensions = _dialogueBg->getContentSize();
	if (options.size() >= 3){
		labelDimensions.height /= options.size() + 1;
	}
	else {
		labelDimensions.height /= 4;
	}
	int itemIndex = 0;
	_dialogueMenu->removeAllChildren();//清空之前可能有的
	for (Option option : options ) {
		auto label = Label::create(option.text, "", labelDimensions.height - 10, labelDimensions, TextHAlignment::CENTER, TextVAlignment::CENTER);
		label->setColor(Color3B(16, 16, 16));

		MenuItemLabel* item = MenuItemLabel::create(label, ccMenuCallback([&, option, onSelected](Ref *ref){
			const char* text = option.text.c_str();
			int toId = option.toId;
			if (onSelected != NULL){
				onSelected(text, toId);
			}

			_dialogueMenu->removeAllChildren();
		}));
		item->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		item->setPosition(Vec2(0, -labelDimensions.height * itemIndex));
		item->setContentSize(labelDimensions);
		_dialogueMenu->addChild(item);

		itemIndex++;
	}
}

Scale9Sprite* DialogueManager::getDialogueBg() {
	return this->_dialogueBg;
}

DialogueManager::~DialogueManager(){
	this->_dialogueBg->release();
	this->_dialogueText->release();
	this->_dialogueMenu->release();
	this->release();
}