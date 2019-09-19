#pragma once
#include <easy2d.h>
using namespace easy2d;

class GameOverLayer :
	public Node
{
public:
	GameOverLayer(int score);

	void initPanel(int score);
	void initButtons();
	Image* getModal(int score);
};

