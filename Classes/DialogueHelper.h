#ifndef __DialogueHelper_H__
#define __DialogueHelper_H__

#include "cocos2d.h"

USING_NS_CC;

enum DialogueType{
	string, option, sound
};

//选项数据
struct Option{
	std::string text;
	int toId;
};

//会话数据
struct DialogueData{
	std::string speakerName;
	std::string content;
	DialogueType type;
	std::vector<Option> options;
};

//todo 后期内存管理可以优化
class DialogueHelper : public Ref{
public:
	DialogueHelper();
	virtual ~DialogueHelper();

	static DialogueHelper* parseWithFile(const char *xmlFileName);

	bool initWithFile(const char *xmlFileName);
	std::vector<DialogueData>* getDialogueAt(int index);
	std::vector<DialogueData>* getFirstDialogue();
	std::vector<std::vector<DialogueData>>* getDialogueList();
private:
	std::vector<std::vector<DialogueData>> _dialogueList;//todo 后期可以优化为Vector
};

#endif