#pragma once
#include "easy2d.h"
#include "Number.h"

class GameOverLayer :
	public ENode
{
public:
	GameOverLayer(int score);

	void initPanel();
	void initButtons();
	void showScore();
	ESpriteFrame* getModal();

public:
	int score = 0;
	int bestScore = 0;
	Number* scoreImage;
	Number* bestScoreImage;
};

