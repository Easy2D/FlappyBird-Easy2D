#pragma once
#include <easy2d.h>

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
	double speed;
	Action * fly;
	Animation * animation;
	Action * rotate;
};

