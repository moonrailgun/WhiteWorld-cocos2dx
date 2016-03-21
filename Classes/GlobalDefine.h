#ifndef __GlobalDefine__H__
#define __GlobalDefine__H__

#include "cocos2d.h"

USING_NS_CC;

#define WINSIZE Director::getInstance()->getWinSize()

#define setIntToXML     UserDefault::getInstance()->setIntegerForKey
#define setFloatToXML   UserDefault::getInstance()->setFloatForKey
#define setBoolToXML    UserDefault::getInstance()->setBoolForKey
#define getIntFromXML   UserDefault::getInstance()->getIntegerForKey
#define getFloatFromXML UserDefault::getInstance()->getFloatForKey
#define getBoolFromXML  UserDefault::getInstance()->getBoolForKey
#define audioEngine		SimpleAudioEngine::getInstance()

#define SOUND_KEY       "soundClose"            // ������Ч
#define MUSIC_KEY       "musicClose"              // ��������
#define SOUNDVOL        "soundVolume"        // ��Ч����
#define MUSICVOL        "musicVolume"          // ��������
#define EXP_KEY         "heroCurrentExp"        // Ӣ�۵�ǰ����
#define HEROLEVEL_KEY   "heroLevel"          // ��ǰ�ȼ�
#define HEROCOIN_KEY    "heroCoin"            // Ӣ�۽��
#define HEROENERGY_KEY  "heroEnergy"   // Ӣ������
#define HEROHP_KEY      "heroHP"                // Ӣ��Ѫ��
#define HEROMP_KEY      "heroMP"               // Ӣ������
#define HEROAPOWER_KEY  "heroAPower"  // Ӣ���չ��˺�
#define HEROABILITY_KEY "heroAbility"        // Ӣ�������ȼ�
#define GAMEOVER        "gameOver"              // ��Ϸ�������

#endif