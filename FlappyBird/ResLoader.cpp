#include "ResLoader.h"
#include <map>

struct IMAGE_INFO
{
	float x, y, width, height;
};

std::map<EString, IMAGE_INFO> m_Images;
extern EString AtlasData;


void ResLoader::init()
{
	// 预加载音效
	EMusicUtils::preloadMusic(L"MUSIC_FLY", L"WAVE", L"wav");
	EMusicUtils::preloadMusic(L"MUSIC_HIT", L"WAVE", L"wav");
	EMusicUtils::preloadMusic(L"MUSIC_MENU_CLICK", L"WAVE", L"wav");
	EMusicUtils::preloadMusic(L"MUSIC_POINT", L"WAVE", L"wav");
	EMusicUtils::preloadMusic(L"MUSIC_SWOOSH", L"WAVE", L"wav");
	EMusicUtils::preloadMusic(L"res/sound/fly.wav");

	// 预加载图片
	ETexture::preload(L"IDB_PNG", L"IMAGE");
	// 加载图片格式信息
	int offset = 0;
	int count = 0;
	// 读取数据
	while (true) {
		if (AtlasData[offset + count] != '\n') {
			count++;
			continue;
		}
		TCHAR name[21];
		float width, height, x, y;
		EString s = AtlasData.substr(offset, count);
		// 读取图片名称、宽高、起始点坐标
		swscanf(AtlasData.substr(offset, count).c_str(), L"%s %f %f %f %f\n", name, &width, &height, &x, &y);
		// 创建 IMAGE_INFO
		IMAGE_INFO info = { x, y, width, height };
		m_Images.insert(make_pair(EString(name), info));
		offset += count + 1;
		count = 0;
		if (offset == AtlasData.size())
			break;
	}
}

void ResLoader::playMusic(const EString & musicName)
{
	EMusicUtils::playMusic(musicName, L"WAVE", L"wav");
}

ESpriteFrame * ResLoader::getImage(const EString & imageName)
{
	IMAGE_INFO info = m_Images.at(imageName);
	return new ESpriteFrame(L"IDB_PNG", L"IMAGE", info.x, info.y, info.width, info.height);
}

EString AtlasData = 
L"splash 288 512 292 515\n"
L"bg_day 288 512 0 0\n"
L"bg_night 288 512 292 0\n"
L"bird0_0 34 24 5 982\n"
L"bird0_1 34 24 61 982\n"
L"bird0_2 34 24 117 982\n"
L"bird1_0 34 24 173 982\n"
L"bird1_1 34 24 229 658\n"
L"bird1_2 34 24 229 710\n"
L"bird2_0 34 24 229 762\n"
L"bird2_1 34 24 229 814\n"
L"bird2_2 34 24 229 866\n"
L"black 32 32 584 412\n"
L"blink_00 10 10 276 682\n"
L"blink_01 10 10 276 734\n"
L"blink_02 10 10 276 786\n"
L"brand_copyright 126 14 884 182\n"
L"button_ok 80 28 924 84\n"
L"button_pause 26 28 242 612\n"
L"button_rate 74 48 924 0\n"
L"button_resume 26 28 668 284\n"
L"button_score 116 70 822 234\n"
L"button_restart 116 70 702 316\n"
L"button_share_big 116 70 822 316\n"
L"button_play 116 70 702 234\n"
L"button_menu 80 28 924 52\n"
L"button_share 80 28 584 284\n"
L"land 336 112 584 0\n"
L"medals_0 44 44 224 954\n"
L"medals_1 44 44 224 906\n"
L"medals_2 44 44 242 564\n"
L"medals_3 44 44 242 516\n"
L"new 32 14 224 1002\n"
L"number_big_0 24 36 992 120\n"
L"number_big_1 16 36 272 910\n"
L"number_big_2 24 36 584 320\n"
L"number_big_3 24 36 612 320\n"
L"number_big_4 24 36 640 320\n"
L"number_big_5 24 36 668 320\n"
L"number_big_6 24 36 584 368\n"
L"number_big_7 24 36 612 368\n"
L"number_big_8 24 36 640 368\n"
L"number_big_9 24 36 668 368\n"
L"number_medium_0 16 20 272 612\n"
L"number_medium_1 16 20 272 954\n"
L"number_medium_2 16 20 272 978\n"
L"number_medium_3 16 20 260 1002\n"
L"number_medium_4 16 20 1002 0\n"
L"number_medium_5 16 20 1002 24\n"
L"number_medium_6 16 20 1008 52\n"
L"number_medium_7 16 20 1008 84\n"
L"number_medium_8 16 20 584 484\n"
L"number_medium_9 16 20 620 412\n"
L"number_small_0 12 14 276 646\n"
L"number_small_1 12 14 276 664\n"
L"number_small_2 12 14 276 698\n"
L"number_small_3 12 14 276 716\n"
L"number_small_4 12 14 276 750\n"
L"number_small_5 12 14 276 768\n"
L"number_small_6 12 14 276 802\n"
L"number_small_7 12 14 276 820\n"
L"number_small_8 12 14 276 854\n"
L"number_small_9 12 14 276 872\n"
L"number_context_10 12 14 992 164\n"
L"pipe_above_2 52 320 0 646\n"
L"pipe_below_2 52 320 56 646\n"
L"pipe_above 52 320 112 646\n"
L"pipe_below 52 320 168 646\n"
L"score_panel 238 126 0 516\n"
L"text_game_over 204 54 784 116\n"
L"text_ready 196 62 584 116\n"
L"title 178 48 702 182\n"
L"tutorial 114 98 584 182\n"
L"white 32 32 584 448\n";