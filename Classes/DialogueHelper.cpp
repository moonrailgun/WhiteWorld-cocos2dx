#include "DialogueHelper.h"
#include "tinyxml2/tinyxml2.h"

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
		std::vector<DialogueData> dialogueData;//数据对象
		int dialogueId = (int)dialogue->Attribute("id");//暂时不保存
		const char* triggerPos = dialogue->Attribute("triggerPos");//暂时不保存

		for (auto content = dialogue->FirstChildElement(); content; content = content->NextSiblingElement()){
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
			log("loading text：%s", content->GetText());
		}

		dialogueHelper->dialogueList.push_back(dialogueData);
	}

	return dialogueHelper;
}

DialogueHelper::DialogueHelper(){

}
DialogueHelper::~DialogueHelper(){

}