#include "GameScene.h"
#include "ResLoader.h"
#include "GameOverLayer.h"

GameScene::GameScene()
{
	// ��ӱ���
	auto background = new ESprite(ResLoader::getImage(L"bg_day"));
	background->setPivot(0, 0);
	this->add(background);

	// ���ˮ��
	pipes = new Pipes();
	this->add(pipes);

	// ���С��
	bird = new Bird();
	bird->setPos(60, EWindow::getHeight() / 2);
	this->add(bird);

	// ��ӵ���
	ground = new Ground();
	this->add(ground);

	// ��ӵ÷�
	scoreImage = new Number();
	scoreImage->setPos(EWindow::getWidth() / 2, 50);
	scoreImage->setNumber(0);
	this->add(scoreImage);

	// ��� ready ͼƬ
	ready = new ESprite(ResLoader::getImage(L"text_ready"));
	ready->setPos(EWindow::getWidth() / 2, EWindow::getHeight() / 2 - 70);
	this->add(ready);

	// ��ӽ̳�ͼƬ
	tutorial = new ESprite(ResLoader::getImage(L"tutorial"));
	tutorial->setPos(EWindow::getWidth() / 2, EWindow::getHeight() / 2 + 30);
	this->add(tutorial);

	started = false;
	score = 0;
}

void GameScene::onEnter()
{
	// ���볡��ʱ������Ч
	ResLoader::playMusic(L"res/sound/swoosh.wav");
}

void GameScene::onUpdate()
{
	// �������������¿ո��
	if (EInput::isMouseLButtonPress() || 
		EInput::isKeyPress(EKeyCode::SPACE))
	{
		this->jump();
	}

	// �ж���Ϸ�Ƿ��Ѿ���ʼ
	if (started)
	{
		// ģ��С������
		bird->movePosY(bird->speed);
		// ģ��С����������
		bird->speed += 0.4f;
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
			ResLoader::playMusic(L"res/sound/point.wav");
		}
		// ��С��������С�ڵ��棬��Ϸ����
		if (EWindow::getHeight() - bird->getPosY() <= 123) {
			// ��С��ֹͣ
			bird->setPosY(EWindow::getHeight() - 123);
			bird->setStatus(0);
			// ��С��������
			bird->setRotation(90);
			// ��ʾ��Ϸ��������
			this->gameover();
		}
	}
}

void GameScene::onCollide(ENode * node1, ENode * node2)
{
	// ֻҪ����ײ��������˵��С������
	if (bird->living) {
		this->die();
	}
}

void GameScene::start()
{
	// ���� ready ͼƬ
	ready->runAction(new EActionFadeOut(0.4f));
	tutorial->runAction(new EActionFadeOut(0.4f));
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
		bird->speed = -7.2f;
		// ����С��״̬Ϊ 3
		bird->setStatus(3);
		// ������Ч
		ResLoader::playMusic(L"res/sound/fly.wav");
	}
}

void GameScene::die()
{
	// С������
	bird->living = false;
	// ������Ч
	ResLoader::playMusic(L"res/sound/hit.wav");
	// ֹͣ����
	ground->stop();
	// ֹͣˮ��
	pipes->stop();
	// ���ص÷�
	scoreImage->runAction(new EActionFadeOut(0.5f));
	// ��������
	auto white = new ESprite(ResLoader::getImage(L"white"));
	white->setPivot(0, 0);
	white->setOpacity(0);
	white->setScale(16, 16);
	white->runAction(new EActionTwo(new EActionFadeIn(0.1f), new EActionFadeOut(0.1f)));
	this->add(white);
}

void GameScene::gameover()
{
	started = false;
	this->setAutoUpdate(false);
	// ��ʾ�÷����
	this->add(new GameOverLayer(score));
}
