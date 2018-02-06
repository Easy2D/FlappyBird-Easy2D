#include "ResLoader.h"
#include <map>

struct Info
{
	float x, y, width, height;
};

std::map<EString, Info> m_Images;


void ResLoader::init()
{
	// �������ļ���ӵ����ֹ�����
	EMusicManager::add(L"res/sound/fly.wav");
	EMusicManager::add(L"res/sound/hit.wav");
	EMusicManager::add(L"res/sound/click.wav");
	EMusicManager::add(L"res/sound/point.wav");
	EMusicManager::add(L"res/sound/swoosh.wav");

	// Ԥ����ͼƬ
	EImage::preload(L"res/atlas.png");

	// �� atlas.bin �ļ�
	FILE * file = _wfopen(L"res/atlas.bin", L"r");
	// ����ͼƬ��ʽ��Ϣ
	while (true) 
	{
		TCHAR name[21];
		float width, height, x, y;
		// ��ȡͼƬ���ơ���ߡ���ʼ������
		if (5 != fwscanf(file, L"%s %f %f %f %f\n", name, &width, &height, &x, &y))
		{
			break;
		}
		// ���� Info
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