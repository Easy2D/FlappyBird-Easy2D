#pragma once
#include "easy2d.h"
#include "Number.h"

class GameOverLayer :
	public Layer
{
public:
	GameOverLayer(int score);
	~GameOverLayer();

	void showScore();
	Image* getModal();

public:
	int score = 0;
	int bestScore = 0;
	Number* scoreImage;
	Number* bestScoreImage;
};

