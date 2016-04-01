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

class DialogueHelper : public Ref{
public:
	DialogueHelper();
	virtual ~DialogueHelper();

	static DialogueHelper* parseWithFile(const char *xmlFileName);

	bool initWithFile(const char *xmlFileName);
private:
	std::vector<std::vector<DialogueData>> dialogueList;
};

#endif