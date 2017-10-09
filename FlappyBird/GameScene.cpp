#include "GameScene.h"
#include "ImageLoader.h"
#include "GameOverLayer.h"

void GameScene::init()
{
	// ��ӱ���
	this->add(ImageLoader::getImage(_T("bg_day")));
	// ���ˮ��
	pipes = new Pipes();
	this->add(pipes);
	// ��ӵ���
	ground = new Ground();
	this->add(ground);
	// ���С��
	bird = new Bird();
	bird->setWindowCenterY();
	bird->setX(60);
	this->add(bird);
	// ��ӵ÷�
	scoreImage = new Number();
	scoreImage->setPos(App::getWidth() / 2, 50);
	scoreImage->setNumber(0);
	this->add(scoreImage);
	// ��� ready ͼƬ
	ready = new Sprite(ImageLoader::getImage(_T("text_ready")));
	ready->setWindowCenter();
	ready->move(0, -70);
	this->add(ready);
	// ��ӽ̳�ͼƬ
	tutorial = new Sprite(ImageLoader::getImage(_T("tutorial")));
	tutorial->setWindowCenter();
	tutorial->move(0, 30);
	this->add(tutorial);

	// ��������Ϣ����
	MouseMsg::addListener(_T("mouse_click"), [=] {
		// ���������������£���˫��������Ϣʱ��ִ�� onClick ����
		if (MouseMsg::getMsg() == MouseMsg::LBUTTON_DOWN ||
			MouseMsg::getMsg() == MouseMsg::LBUTTON_DBLCLK) {
			this->onClick();
		}
	});

	// ��Ӽ��̰�������
	KeyMsg::addListener(_T("key_click"), [=](VK_KEY key) {
		// ���¿ո�ʱ��ִ�� onClick ����
		if (key == KeyMsg::Space) {
			this->onClick();
		}
	});
}

void GameScene::onEnter()
{
	// ���볡��ʱ������Ч
	//MusicUtils::playMusic(_T("res/sound/swoosh.mp3"));
}

void GameScene::onClick()
{
	if (!m_bStart) {
		// ����Ϸ��û�п�ʼ
		m_bStart = true;
		onStart();
	}
	if (bird->living) {
		// ���С�񻹻��ţ���С��һ�����ϵ��ٶ�
		bird->speed = -7.2f;
		// ������Ч
		//MusicUtils::playMusic(_T("res/sound/fly.mp3"));
	}
}

void GameScene::onStart()
{
	// ���� ready ͼƬ
	ready->addAction(new ActionFadeOut(0.4f));
	tutorial->addAction(new ActionFadeOut(0.4f));
	// ����С��״̬Ϊ 2
	bird->setStatus(2);
	// ˮ�ܿ�ʼ�ƶ�
	pipes->start();
	// ��Ӷ�ʱ�����С��λ��
	Timer::addTimer(_T("game_timer"), [=] {
		// ģ��С������
		bird->move(0, (int)bird->speed);
		// ģ��С����������
		bird->speed += 0.4f;
		// �ж��Ƿ�÷�
		if (pipes->pipes[0][0]->getX() <= bird->getX()) {
			static Sprite* temp = nullptr;
			if (temp != pipes->pipes[0][0]) {
				// ��¼����÷ֵ�ˮ��
				temp = pipes->pipes[0][0];
				// �ӷ�
				score++;
				scoreImage->setNumber(score);
			}
		}
		// �ж�С���Ƿ��ˮ����ײ
		if (bird->living) {
			if (pipes->isCollisionWith(bird)) {
				this->onBirdDie();
			}
		}
		// ��С��������С�� 118����Ϸ����
		if (App::getHeight() - bird->getY() <= 135) {
			// С������
			if (bird->living) {
				this->onBirdDie();
			}
			// ��Ϸ������ֹͣ�����ʱ��
			Timer::stopTimer(_T("game_timer"));
			// ��С��ֹͣ
			bird->setY(App::getHeight() - 135);
			bird->setStatus(0);
			// ��ʾ��Ϸ��������
			this->onGameOver();
		}
		// ��С��������С�� 0���������������Ϸ�
		if (bird->getY() < 0) {
			bird->setY(0);
			bird->speed = 0;
		}
	});
}

void GameScene::onBirdDie()
{
	// С������
	bird->living = false;
	// ������Ч
	//MusicUtils::playMusic(_T("res/sound/hit.mp3"));
	// ֹͣ����
	ground->stop();
	// ֹͣˮ��
	pipes->stop();
	// ���ص÷�
	scoreImage->runAction(new ActionFadeOut(0.5f));
	// ��������
	auto white = new Sprite(ImageLoader::getImage(_T("white")));
	white->setOpacity(0);
	white->setScale(16, 16);
	white->addAction(new ActionTwo(new ActionFadeIn(0.1f), new ActionFadeOut(0.1f)));
	this->add(white);
}

void GameScene::onGameOver()
{
	this->add(new GameOverLayer(score));
}
