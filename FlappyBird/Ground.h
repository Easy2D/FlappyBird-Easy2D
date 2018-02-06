#pragma once
#include <easy2d.h>

// 地面类
// 游戏中最下方一直向左移动的地面
class Ground :
	public ENode
{
public:
	Ground();

	void onUpdate() override;
	void stop();

public:
	ESprite * ground1;	// 第一块地面
	ESprite * ground2;	// 第二块地面
};

