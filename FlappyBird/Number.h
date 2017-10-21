#pragma once
#include "easy2d.h"

class Number :
	public ESprite
{
public:
	Number();
	~Number();

	int getNumber();
	void setNumber(int number);
	void setLittleNumber(int number);

protected:
	int number = 0;
};

