#pragma once
#include "easy2d.h"

class Bird :
	public ESprite
{
public:
	Bird();

	// 设置小鸟状态
	// 0 代表完全静止，1 代表上下晃动
	void setStatus(int status);

public:
	bool living = true;
	float speed = 0;
	EAction * fly;
	EAnimation * animation;
	EAction * rotate;
	EAction * temp;
};

