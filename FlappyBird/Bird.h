#pragma once
#include "common.h"

// 小鸟类
class Bird :
	public Sprite
{
public:
	Bird();

	~Bird();

	// 小鸟状态
	enum class Status
	{
		Still,		// 小鸟不动
		Idle,		// 小鸟上下浮动
		StartToFly,	// 游戏刚开始时，小鸟停止浮动，并开始旋转
		Fly,		// 小鸟向上飞时，先抬头，后低头
	};

	// 设置小鸟状态
	void setStatus(Status status);

public:
	bool living;
	float speed;
	Action* fly;
	Animation* animation;
	Action* rotate;
};
