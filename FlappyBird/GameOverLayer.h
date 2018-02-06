#pragma once
#include <easy2d.h>

class GameOverLayer :
	public ENode
{
public:
	GameOverLayer(int score);

	void initPanel(int score);
	void initButtons();
	EImage* getModal(int score);
};

