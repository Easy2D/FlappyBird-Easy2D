#pragma once
#include "common.h"
#include <map>

// ��Ƶ����
enum class MusicType
{
	Click,	// ��������
	Hit,	// С����������
	Fly,	// С���������
	Point,	// �÷�����
	Swoosh	// ת������
};

// ��Դ������
class ResLoader
{
public:
	static void init();

	// ��ȡͼƬ
	static Image* getImage(String imageName);

	// ������Ƶ
	static void playMusic(MusicType musicType);

private:
	// ͼƬ��Ϣ
	struct ImageInfo
	{
		float x, y, width, height;
	};

	// ͼƬ��ͼ
	static std::map<String, ImageInfo> imageMap;

	// ��Ƶ��ͼ
	static std::map<MusicType, Music*> musicMap;
};
