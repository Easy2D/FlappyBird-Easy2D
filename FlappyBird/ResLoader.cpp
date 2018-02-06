#include "ResLoader.h"
#include <map>

struct Info
{
	float x, y, width, height;
};

std::map<EString, Info> m_Images;


void ResLoader::init()
{
	// 把音乐文件添加到音乐管理器
	EMusicManager::add(L"res/sound/fly.wav");
	EMusicManager::add(L"res/sound/hit.wav");
	EMusicManager::add(L"res/sound/click.wav");
	EMusicManager::add(L"res/sound/point.wav");
	EMusicManager::add(L"res/sound/swoosh.wav");

	// 预加载图片
	EImage::preload(L"res/atlas.png");

	// 打开 atlas.bin 文件
	FILE * file = _wfopen(L"res/atlas.bin", L"r");
	// 加载图片格式信息
	while (true) 
	{
		TCHAR name[21];
		float width, height, x, y;
		// 读取图片名称、宽高、起始点坐标
		if (5 != fwscanf(file, L"%s %f %f %f %f\n", name, &width, &height, &x, &y))
		{
			break;
		}
		// 创建 Info
		Info info = { x, y, width, height };
		m_Images.insert(std::make_pair(EString(name), info));
	}
}

void ResLoader::playMusic(const EString & musicName)
{
	EMusicManager::get(musicName)->play(0);
}

EImage * ResLoader::getImage(const EString & imageName)
{
	Info info = m_Images.at(imageName);
	return new EImage(L"res/atlas.png", info.x, info.y, info.width, info.height);
}