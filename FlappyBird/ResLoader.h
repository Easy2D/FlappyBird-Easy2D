#pragma once
#include "common.h"
#include <map>

// 音频类型
enum class MusicType
{
	Click,	// 按键声音
	Hit,	// 小鸟死亡声音
	Fly,	// 小鸟飞翔声音
	Point,	// 得分声音
	Swoosh	// 转场声音
};

// 资源管理工具
class ResLoader
{
public:
	static void init();

	// 获取图片
	static Image* getImage(String imageName);

	// 播放音频
	static void playMusic(MusicType musicType);

private:
	// 图片信息
	struct ImageInfo
	{
		float x, y, width, height;
	};

	// 图片地图
	static std::map<String, ImageInfo> imageMap;

	// 音频地图
	static std::map<MusicType, Music*> musicMap;
};
