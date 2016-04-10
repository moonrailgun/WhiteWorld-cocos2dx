#ifndef __DialogueManager__H__
#define __DialogueManager__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "DialogueHelper.h"

USING_NS_CC;
USING_NS_CC_EXT;

class DialogueManager : public Ref{
public:
	bool init();
	CREATE_FUNC(DialogueManager);

	void showDialogue(Node* node);
	void hideDialogue();
	void updateDialogueText(const char* text);
	void updateDialogueOptions(std::vector<Option> options, std::function<void(const char*, int)> &onSelected);
	Scale9Sprite* getDialogueBg();
	~DialogueManager();
private:
	Scale9Sprite* _dialogueBg;
	LabelTTF* _dialogueText;
	Menu* _dialogueMenu;
};

#endif