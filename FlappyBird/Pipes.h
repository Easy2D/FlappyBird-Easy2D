#pragma once
#include "easy2d.h"

class Pipes :
	public ESprite
{
public:
	Pipes();
	~Pipes();

	void start();
	void stop();
	void addPipe();

public:
	int number = 0;
	ESprite* pipes[3][2];
};

