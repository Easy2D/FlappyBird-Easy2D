#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

// С����
class Bird :
	public Sprite
{
public:
	Bird();

	~Bird();

	void setStatus(int status);	// ����С��״̬

public:
	bool living;
	float speed;
	Action * fly;
	Animation * animation;
	Action * rotate;
};

