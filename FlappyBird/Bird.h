#pragma once
#include <easy2d.h>

// С����
class Bird :
	public ESprite
{
public:
	Bird();

	~Bird();

	void setStatus(int status);	// ����С��״̬

public:
	bool living;
	float speed;
	EAction * fly;
	EAnimation * animation;
	EAction * rotate;
};

