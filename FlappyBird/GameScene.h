#pragma once
#include <easy2d.h>
#include "Bird.h"
#include "Ground.h"
#include "Pipes.h"
#include "Number.h"

class GameScene :
	public Scene
{
protected:
	bool m_bStart = false;
	int score = 0;
	Bird*   bird;
	Ground* ground;
	Pipes*  pipes;
	Number* scoreImage;
	Sprite* ready;
	Sprite* tutorial;

public:
	void init() override;
	void onEnter() override;
	void onClick();
	void onStart();
	void onBirdDie();
	void onGameOver();
};

