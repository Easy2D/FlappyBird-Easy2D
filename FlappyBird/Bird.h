#pragma once
#include <easy2d.h>

// 小鸟类
class Bird :
	public ESprite
{
public:
	Bird();

	~Bird();

	void setStatus(int status);	// 设置小鸟状态

public:
	bool living;
	float speed;
	EAction * fly;
	EAnimation * animation;
	EAction * rotate;
};

