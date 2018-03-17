#include "GameScene.h"
#include "ResLoader.h"
#include "GameOverLayer.h"

GameScene::GameScene()
{
	// ��ӱ���
	auto background = new Sprite(ResLoader::getImage("bg_day"));
	background->setPivot(0, 0);
	this->add(background);

	// ���ˮ��
	pipes = new Pipes();
	this->add(pipes);

	// ���С��
	bird = new Bird();
	bird->setPos(60, Window::getHeight() / 2);
	this->add(bird);

	// ��ӵ���
	ground = new Ground();
	this->add(ground);

	// ��ӵ÷�
	scoreImage = new Number();
	scoreImage->setPos(Window::getWidth() / 2, 50);
	scoreImage->setNumber(0);
	this->add(scoreImage);

	// ��� ready ͼƬ
	ready = new Sprite(ResLoader::getImage("text_ready"));
	ready->setPos(Window::getWidth() / 2, Window::getHeight() / 2 - 70);
	this->add(ready);

	// ��ӽ̳�ͼƬ
	tutorial = new Sprite(ResLoader::getImage("tutorial"));
	tutorial->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 30);
	this->add(tutorial);

	started = false;
	score = 0;
}

void GameScene::onEnter()
{
	// ���볡��ʱ������Ч
	MusicManager::play("res/sound/swoosh.wav");
}

void GameScene::onUpdate()
{
	// �������������¿ո��
	if (Input::isMouseLButtonPress() || 
		Input::isKeyPress(KeyCode::SPACE))
	{
		this->jump();
	}

	// �ж���Ϸ�Ƿ��Ѿ���ʼ
	if (started)
	{
		// ģ��С������
		bird->movePosY(bird->speed);
		// ģ��С����������
		bird->speed += 0.4;
		// ��С��������С�� 0���������������Ϸ�
		if (bird->getPosY() < 0) {
			bird->setPosY(0);
			bird->speed = 0;
		}
		// �ж�С���Ƿ�ɹ���ˮ��
		if (!pipes->pipes[0]->scored &&
			pipes->pipes[0]->getPosX() <= bird->getPosX())
		{
			// �ӷ�
			score++;
			scoreImage->setNumber(score);
			// ���
			pipes->pipes[0]->scored = true;
			// ������Ч
			MusicManager::play("res/sound/point.wav");
		}
		// ��С��������С�ڵ��棬��Ϸ����
		if (Window::getHeight() - bird->getPosY() <= 123) {
			// ��С��ֹͣ
			bird->setPosY(Window::getHeight() - 123);
			bird->setStatus(0);
			// ��С��������
			bird->setRotation(90);
			// ��ʾ��Ϸ��������
			this->gameover();
		}
	}
}

void GameScene::onCollide(Node * node1, Node * node2)
{
	// ֻҪ����ײ��������˵��С������
	if (bird->living) {
		this->die();
	}
}

void GameScene::start()
{
	// ���� ready ͼƬ
	ready->runAction(new ActionFadeOut(0.4));
	tutorial->runAction(new ActionFadeOut(0.4));
	// ��ʼ�ƶ�ˮ��
	pipes->start();
	// ����С��״̬Ϊ 2
	bird->setStatus(2);
}

void GameScene::jump()
{
	if (!started) {
		// ����Ϸ��û�п�ʼ����ʼ��Ϸ
		started = true;
		start();
	}
	if (bird->living) {
		// ���С�񻹻��ţ���С��һ�����ϵ��ٶ�
		bird->speed = -7.2;
		// ����С��״̬Ϊ 3
		bird->setStatus(3);
		// ������Ч
		MusicManager::play("res/sound/fly.wav");
	}
}

void GameScene::die()
{
	// С������
	bird->living = false;
	// ������Ч
	MusicManager::play("res/sound/hit.wav");
	// ֹͣ����
	ground->stop();
	// ֹͣˮ��
	pipes->stop();
	// ���ص÷�
	scoreImage->runAction(new ActionFadeOut(0.5));
	// ��������
	auto white = new Sprite(ResLoader::getImage("white"));
	white->setPivot(0, 0);
	white->setOpacity(0);
	white->setScale(16, 16);
	white->runAction(new ActionTwo(new ActionFadeIn(0.1), new ActionFadeOut(0.1)));
	this->add(white);
}

void GameScene::gameover()
{
	started = false;
	this->setAutoUpdate(false);
	// ��ʾ�÷����
	this->add(new GameOverLayer(score));
}
