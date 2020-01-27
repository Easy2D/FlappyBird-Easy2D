#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

// 小鸟类
class Bird :
	public Sprite
{
public:
	Bird();

	~Bird();

	void setStatus(int status);	// 设置小鸟状态

public:
	bool living;
	float speed;
	Action * fly;
	Animation * animation;
	Action * rotate;
};

