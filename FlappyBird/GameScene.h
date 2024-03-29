#pragma once
#include "Bird.h"
#include "Ground.h"
#include "Pipes.h"
#include "Number.h"

class GameScene :
	public Scene
{
public:
	GameScene();
	void onEnter() override;
	void onUpdate() override;

	void start();		// 开始游戏
	void hitHappend();	// 小鸟发生碰撞
	void gameover();	// 游戏结束

protected:
	bool started;
	int score;
	Bird*   bird;
	Ground* ground;
	Pipes*  pipes;
	Number* scoreImage;
	Sprite* ready;
	Sprite* tutorial;
};

