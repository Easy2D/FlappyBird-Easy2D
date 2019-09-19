#include "ResLoader.h"
#include <map>
using namespace std;

struct Info
{
	float x, y, width, height;
};

map<String, Info> s_ImageMap;


void ResLoader::init()
{
	// 把音乐文件添加到音乐管理器
	MusicPlayer::preload(L"res/sound/fly.wav");
	MusicPlayer::preload(L"res/sound/hit.wav");
	MusicPlayer::preload(L"res/sound/click.wav");
	MusicPlayer::preload(L"res/sound/point.wav");
	MusicPlayer::preload(L"res/sound/swoosh.wav");

	// 预加载图片
	Image::preload(L"res/atlas.png");

	// 打开 atlas.bin 文件
	wifstream file(L"res/atlas.txt");
	// 读取图片信息
	while (!file.eof())
	{
		WCHAR name[21];
		float width, height, x, y;
		// 读取图片名称、宽高、起始点坐标
		file >> name >> width >> height >> x >> y;
		// 创建 Info
		Info info = { x, y, width, height };
		s_ImageMap.insert(make_pair(name, info));
	}
}

Image * ResLoader::getImage(String imageName)
{
	Info info = s_ImageMap.at(imageName);
	return gcnew Image(L"res/atlas.png", Rect{ info.x, info.y, info.width, info.height });
}