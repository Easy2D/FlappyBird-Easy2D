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
	// �������ļ���ӵ����ֹ�����
	MusicPlayer::preload(L"res/sound/fly.wav");
	MusicPlayer::preload(L"res/sound/hit.wav");
	MusicPlayer::preload(L"res/sound/click.wav");
	MusicPlayer::preload(L"res/sound/point.wav");
	MusicPlayer::preload(L"res/sound/swoosh.wav");

	// Ԥ����ͼƬ
	Image::preload(L"res/atlas.png");

	// �� atlas.bin �ļ�
	wifstream file(L"res/atlas.txt");
	// ��ȡͼƬ��Ϣ
	while (!file.eof())
	{
		WCHAR name[21];
		float width, height, x, y;
		// ��ȡͼƬ���ơ���ߡ���ʼ������
		file >> name >> width >> height >> x >> y;
		// ���� Info
		Info info = { x, y, width, height };
		s_ImageMap.insert(make_pair(name, info));
	}
}

Image * ResLoader::getImage(String imageName)
{
	Info info = s_ImageMap.at(imageName);
	return gcnew Image(L"res/atlas.png", Rect{ info.x, info.y, info.width, info.height });
}