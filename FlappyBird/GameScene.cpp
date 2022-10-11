#include "GameScene.h"
#include "ResLoader.h"
#include "GameOverLayer.h"

GameScene::GameScene()
{
	// ��ӱ���
	auto background = gcnew Sprite(ResLoader::getKeyFrame(L"bg_day"));
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
	ready = gcnew Sprite(ResLoader::getKeyFrame(L"text_ready"));
	ready->setPos(Window::getWidth() / 2, Window::getHeight() / 2 - 70);
	this->addChild(ready);

	// ��ӽ̳�ͼƬ
	tutorial = gcnew Sprite(ResLoader::getKeyFrame(L"tutorial"));
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
		if (!started)
		{
			// ����Ϸ��û�п�ʼ����ʼ��Ϸ
			started = true;
			start();
		}
		bird->jump();
	}

	// �ж���Ϸ�Ƿ��Ѿ���ʼ
	if (started)
	{
		// ģ��С������
		bird->fall();

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
					if (child->getBoundingBox().intersects(box))	// �ж�С���Χ���Ƿ��ˮ���ཻ���ཻ����ײ
					{
						this->hitHappend();
						break;
					}
				}
			}
		}

		// ��С��������С�ڵ��棬��Ϸ����
		if (Window::getHeight() - bird->getPosY() <= 123)
		{
			this->hitHappend();
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

void GameScene::hitHappend()
{
	if (!bird->living)
		return;

	// С������
	bird->die();
	// ֹͣ����
	ground->stop();
	// ֹͣˮ��
	pipes->stop();
	// ���ص÷�
	scoreImage->runAction(gcnew FadeOut(0.5f));
	// ��������
	auto white = gcnew Sprite(ResLoader::getKeyFrame(L"white"));
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
