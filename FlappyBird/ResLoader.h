#pragma once
#include <easy2d.h>
#include <fstream>

// С��ˮ�ܡ����������
#define BIRD_BITMASK	0x0001
#define PIPE_BITMASK	0x0010
#define GROUND_BITMASK	0x0100


// ��Դ��������
class ResLoader
{
public:
	static void init();
	static Image* getImage(String imageName);
};