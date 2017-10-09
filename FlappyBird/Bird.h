#pragma once
#include "easy2d.h"

class Bird :
	public Sprite
{
public:
	Bird();
	~Bird();

	// 设置小鸟状态
	// 0 代表完全静止，1 代表上下晃动
	void setStatus(int status);

public:
	bool living = true;
	float speed = 0;
	Action * fly;
	ActionFrames * frames;
};

