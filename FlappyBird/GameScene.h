#pragma once
#include <easy2d.h>
#include "Bird.h"
#include "Ground.h"
#include "Pipes.h"
#include "Number.h"

class GameScene :
	public EScene
{
public:
	GameScene();
	void onEnter() override;
	void onUpdate() override;
	void onCollide(ENode * node1, ENode * node2) override;

	void start();		// 开始游戏
	void jump();		// 小鸟跳跃
	void die();			// 小鸟死亡
	void gameover();	// 游戏结束

protected:
	bool started;
	int score;
	Bird*   bird;
	Ground* ground;
	Pipes*  pipes;
	Number* scoreImage;
	ESprite* ready;
	ESprite* tutorial;
};

