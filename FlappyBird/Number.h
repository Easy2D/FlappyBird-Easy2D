#pragma once
#include "easy2d.h"

class Number :
	public BatchSprite
{
public:
	Number();
	~Number();

	void setNumber(int number);
	void setLittleNumber(int number);
};

