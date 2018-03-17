#include "ResLoader.h"
#include <map>
using namespace std;

struct Info
{
	double x, y, width, height;
};

map<String, Info> s_ImageMap;


void ResLoader::init()
{
	// �������ļ���ӵ����ֹ�����
	MusicManager::preload("res/sound/fly.wav");
	MusicManager::preload("res/sound/hit.wav");
	MusicManager::preload("res/sound/click.wav");
	MusicManager::preload("res/sound/point.wav");
	MusicManager::preload("res/sound/swoosh.wav");

	// Ԥ����ͼƬ
	Image::preload("res/atlas.png");

	// �� atlas.bin �ļ�
	ifstream file("res/atlas.bin");
	// ��ȡͼƬ��Ϣ
	while (!file.eof())
	{
		char name[21];
		double width, height, x, y;
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
	return new Image("res/atlas.png", info.x, info.y, info.width, info.height);
}