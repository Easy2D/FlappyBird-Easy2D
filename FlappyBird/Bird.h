#pragma once
#include "easy2d.h"

class Bird :
	public Sprite
{
public:
	Bird();
	~Bird();

	// ����С��״̬
	// 0 ������ȫ��ֹ��1 �������»ζ�
	void setStatus(int status);

public:
	bool living = true;
	float speed = 0;
	Action * fly;
	ActionFrames * frames;
};

