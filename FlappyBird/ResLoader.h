#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <easy2d.h>

// С��ˮ�ܡ����������
#define BIRD_BITMASK	0x0001
#define PIPE_BITMASK	0x0010
#define GROUND_BITMASK	0x0100


// ��Դ������
class ResLoader
{
public:
	static void init();
	static void playMusic(const EString & musicName);
	static EImage* getImage(const EString & imageName);
};
