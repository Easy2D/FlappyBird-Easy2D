#include "GameScene.h"
#include "ResLoader.h"
#include "GameOverLayer.h"

GameScene::GameScene()
{
	// ��ӱ���
	auto background = gcnew Sprite(ResLoader::getImage(L"bg_day"));
	background->setAnchor(0, 0);
	this->addChild(background);

	// ���ˮ��
	pipes = gcnew Pipes();
	this->addChild(pipes);

	// ���С��
	bird = gcnew Bird();
	bird->setPos(60, Window::getHeight() / 2);
	this->addChild(bird);

	// ��ӵ���
	ground = gcnew Ground();
	this->addChild(ground);

	// ��ӵ÷�
	scoreImage = gcnew Number();
	scoreImage->setPos(Window::getWidth() / 2, 50);
	scoreImage->setNumber(0);
	this->addChild(scoreImage);

	// ��� ready ͼƬ
	ready = gcnew Sprite(ResLoader::getImage(L"text_ready"));
	ready->setPos(Window::getWidth() / 2, Window::getHeight() / 2 - 70);
	this->addChild(ready);

	// ��ӽ̳�ͼƬ
	tutorial = gcnew Sprite(ResLoader::getImage(L"tutorial"));
	tutorial->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 30);
	this->addChild(tutorial);

	started = false;
	score = 0;
}

void GameScene::onEnter()
{
	// ���볡��ʱ������Ч
	ResLoader::playMusic(MusicType::Swoosh);
}

void GameScene::onUpdate()
{
	// �������������¿ո��
	if (Input::isPress(MouseCode::Left) ||
		Input::isPress(KeyCode::Space))
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
		if (bird->getPosY() < 0)
		{
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
			ResLoader::playMusic(MusicType::Point);
		}

		// �ж���ײ
		if (bird->living)
		{
			for (auto pipe : pipes->pipes)
			{
				auto box = bird->getBoundingBox();  // ��ȡС�����Χ��
				for (auto child : pipe->getAllChildren())
				{
					if (child->getBoundingBox().intersects(box))
					{  // �ж�С���Χ���Ƿ��ˮ���ཻ
						this->die();
					}
				}
			}
		}

		// ��С��������С�ڵ��棬��Ϸ����
		if (Window::getHeight() - bird->getPosY() <= 123)
		{
			this->die();
			// ��С��ֹͣ
			bird->setPosY(Window::getHeight() - 123);
			bird->setStatus(Bird::Status::Still);
			// ��С��������
			bird->setRotation(90);
			// ��ʾ��Ϸ��������
			this->gameover();
		}
	}
}

void GameScene::start()
{
	// ���� ready ͼƬ
	ready->runAction(gcnew FadeOut(0.4f));
	tutorial->runAction(gcnew FadeOut(0.4f));
	// ��ʼ�ƶ�ˮ��
	pipes->start();
	// ����С��״̬
	bird->setStatus(Bird::Status::StartToFly);
}

void GameScene::jump()
{
	if (!started)
	{
		// ����Ϸ��û�п�ʼ����ʼ��Ϸ
		started = true;
		start();
	}
	if (bird->living)
	{
		// ���С�񻹻��ţ���С��һ�����ϵ��ٶ�
		bird->speed = -7.2f;
		// ����С��״̬
		bird->setStatus(Bird::Status::Fly);
		// ������Ч
		ResLoader::playMusic(MusicType::Fly);
	}
}

void GameScene::die()
{
	if (!bird->living) return;

	// С������
	bird->living = false;
	// ������Ч
	ResLoader::playMusic(MusicType::Hit);
	// ֹͣ����
	ground->stop();
	// ֹͣˮ��
	pipes->stop();
	// ���ص÷�
	scoreImage->runAction(gcnew FadeOut(0.5f));
	// ��������
	auto white = gcnew Sprite(ResLoader::getImage(L"white"));
	white->setAnchor(0, 0);
	white->setOpacity(0);
	white->setScale(16, 16);
	white->runAction(gcnew Sequence({ gcnew FadeIn(0.1f), gcnew FadeOut(0.1f) }));
	this->addChild(white);
}

void GameScene::gameover()
{
	started = false;
	this->setAutoUpdate(false);
	// ��ʾ�÷����
	this->addChild(gcnew GameOverLayer(score));
}
