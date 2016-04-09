#ifndef __DialogueHelper_H__
#define __DialogueHelper_H__

#include "cocos2d.h"
#include <unordered_map>

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
	std::unordered_map<int, std::vector<DialogueData>>* getDialogueList();
	std::vector<DialogueData> getDialogueById(int id);

	//更新操作
	static void updateDialogueText(const char *text);
	static void updateDialogueOptions(std::vector<Option> options);
private:
	std::unordered_map<int, std::vector<DialogueData>> _dialogueList;//<对话列表ID， 对话序列>
};

#endif