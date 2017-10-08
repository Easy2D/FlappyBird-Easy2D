#pragma once
#include "easy2d.h"

class Pipes :
	public BatchSprite
{
public:
	Pipes();
	~Pipes();

	void start();
	void stop();
	void addPipe();

public:
	int number = 0;
	Sprite* pipes[3][2];
};

