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
	ESprite* ready;
	ESprite* tutorial;
};

