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

	void start();		// ��ʼ��Ϸ
	void jump();		// С����Ծ
	void die();			// С������
	void gameover();	// ��Ϸ����

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

