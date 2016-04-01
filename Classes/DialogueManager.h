#ifndef __DialogueManager__H__
#define __DialogueManager__H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class DialogueManager : public Ref{
public:
	bool init();
	CREATE_FUNC(DialogueManager);

	bool loadDialogueFromFile(char* fileName);
	void showDialogue(Layer* layer);
	void updateDialogueText(char* text);
private:
	Scale9Sprite* _dialogueBg;
	LabelTTF* _dialogueText;
};

#endif