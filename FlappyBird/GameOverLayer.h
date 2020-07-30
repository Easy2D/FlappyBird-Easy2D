#pragma once
#include "common.h"

class GameOverLayer :
	public Node
{
public:
	GameOverLayer(int score);

	void initPanel(int score);
	void initButtons();
	Image* getModal(int score);
};

