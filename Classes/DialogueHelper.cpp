#include "DialogueHelper.h"
#include "tinyxml2/tinyxml2.h"
#include "GlobalData.h"

DialogueHelper* DialogueHelper::parseWithFile(const char *xmlFileName){
	DialogueHelper* dialogueHelper = new DialogueHelper();

	//读取文本
	auto xmlFileUrl = String::createWithFormat("data/dialogue/%s.xml", xmlFileName);
	auto doc = new tinyxml2::XMLDocument();
	log("is loading %s", xmlFileUrl->getCString());
	doc->LoadFile(xmlFileUrl->getCString());

	//解析
	auto dialogues = doc->RootElement();
	for (auto dialogue = dialogues->FirstChildElement("dialogue"); dialogue != NULL; dialogue = dialogue->NextSiblingElement()){
		//循环添加序列组
		std::vector<DialogueData> dialogueData;//对话序列组对象
		int dialogueId = std::atoi(dialogue->Attribute("id"));//该对话序列组对象
		const char* triggerPos = dialogue->Attribute("triggerPos");//暂时不保存

		if (dialogueId == 0){
			continue;//无id标识,跳过循环
		}

		for (auto content = dialogue->FirstChildElement(); content; content = content->NextSiblingElement()){
			//循环添加对话序列
			DialogueData data;//直接使用对象。由系统维护生命周期防止内存泄露
			std::string contentType = content->Name();
			if (contentType == "string"){
				data.type = DialogueType::string;
				data.speakerName = content->Attribute("name");
				data.content = content->GetText();
			}
			else if (contentType == "options")
			{
				data.type = DialogueType::option;
				std::vector<Option> options;
				for (auto option = content->FirstChildElement(); option; option = option->NextSiblingElement()){
					Option _option;
					_option.text = option->GetText();
					_option.toId = (int)option->Attribute("toId") || -1;
					options.push_back(_option);
				}
				data.options = options;
			}
			dialogueData.push_back(data);
			log("loading text: %s", content->GetText());
		}

		dialogueHelper->_dialogueList[dialogueId] = dialogueData;//重复id后面会覆盖前面的
	}

	return dialogueHelper;
}

std::vector<DialogueData>* DialogueHelper::getFirstDialogue(){
	return &(this->_dialogueList[0]);
}

std::unordered_map<int, std::vector<DialogueData>>* DialogueHelper::getDialogueList(){
	return &this->_dialogueList;
}

std::vector<DialogueData> DialogueHelper::getDialogueById(int id){
	return this->_dialogueList[id];
}

void DialogueHelper::updateDialogueText(const char *text){
	if (dialogueManager == NULL){ return; }

	dialogueManager->updateDialogueText(text);
}
void DialogueHelper::updateDialogueOptions(std::vector<Option> *options){

}


DialogueHelper::DialogueHelper(){

}
DialogueHelper::~DialogueHelper(){

}