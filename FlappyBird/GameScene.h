#pragma once
#include <easy2d.h>
#include "Bird.h"
#include "Ground.h"
#include "Pipes.h"

class GameScene :
	public Scene
{
protected:
	bool m_bStart = false;
	Bird*   bird;
	Ground* ground;
	Pipes*   pipes;
	Sprite* ready;
	Sprite* tutorial;

public:
	void init();
	void onClick();
	void onStart();
	void onBirdDie();
	void onGameOver();
};

