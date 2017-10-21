#pragma once
#include "easy2d.h"

class Bird :
	public ESprite
{
public:
	Bird();

	// ����С��״̬
	// 0 ������ȫ��ֹ��1 �������»ζ�
	void setStatus(int status);

public:
	bool living = true;
	float speed = 0;
	EAction * fly;
	EAnimation * animation;
	EAction * rotate;
	EAction * temp;
};

