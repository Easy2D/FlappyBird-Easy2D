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
};

