#pragma once
#include <easy2d.h>
#include "Pipe.h"

// ����ˮ���˶�����
class Pipes :
	public ESprite
{
public:
	Pipes();
	~Pipes();

	void onUpdate() override;
	void addPipe();	// ���һ��ˮ��
	void start();	// ��ʼ�ƶ�
	void stop();	// ֹͣ�ƶ�

public:
	int number;		// ˮ������
	Pipe* pipes[3];	// ������ֻ��3��ˮ��
};
