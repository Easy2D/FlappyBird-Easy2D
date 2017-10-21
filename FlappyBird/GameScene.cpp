#include "GameScene.h"
#include "ImageLoader.h"
#include "GameOverLayer.h"

GameScene::GameScene()
{
	// ��ӱ���
	auto background = new ESprite(ImageLoader::getImage(L"bg_day"));
	// ���ñ���ê��Ϊ���Ͻ�
	background->setAnchor(0, 0);
	this->add(background);
	// ���ˮ��
	pipes = new Pipes();
	this->add(pipes);
	// ���С��
	bird = new Bird();
	bird->setPos(60, EApp::getHeight() / 2);
	this->add(bird);
	// ��ӵ���
	ground = new Ground();
	this->add(ground);
	// ��ӵ÷�
	scoreImage = new Number();
	scoreImage->setPos(EApp::getWidth() / 2, 50);
	scoreImage->setNumber(0);
	this->add(scoreImage);
	// ��� ready ͼƬ
	ready = new ESprite(ImageLoader::getImage(L"text_ready"));
	ready->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2 - 70);
	this->add(ready);
	// ��ӽ̳�ͼƬ
	tutorial = new ESprite(ImageLoader::getImage(L"tutorial"));
	tutorial->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2 + 30);
	this->add(tutorial);

	// ��������Ϣ����
	auto mouseListener = new EMousePressListener([=](EPoint) {
		// ���������������µ���Ϣʱ��ִ�� onClick ����
		this->onClick();
	});
	// �󶨼�����
	mouseListener->bindWith(this);

	// ��Ӽ��̰�������
	auto keyboardListener = new EKeyboardPressListener([=] {
		// ���¿ո�ʱ��ִ�� onClick ����
		if (EKeyboardMsg::getVal() == EKeyboardMsg::KEY::SPACE) {
			this->onClick();
		}
	});
	// �󶨼�����
	keyboardListener->bindWith(this);
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
		// ����С��״̬Ϊ 3
		bird->setStatus(3);
		// ������Ч
		//MusicUtils::playMusic(_T("res/sound/fly.mp3"));
	}
}

void GameScene::onStart()
{
	// ���� ready ͼƬ
	ready->runAction(new EActionFadeOut(0.4f));
	tutorial->runAction(new EActionFadeOut(0.4f));
	// ����С��״̬Ϊ 2
	bird->setStatus(2);
	// ˮ�ܿ�ʼ�ƶ�
	pipes->start();
	// ��Ӷ�ʱ�����С��λ��
	auto timer = new ETimer([=](int) {
		// ģ��С������
		bird->move(0, bird->speed);
		// ģ��С����������
		bird->speed += 0.4f;
		// �ж��Ƿ�÷�
		if (pipes->pipes[0][0]->getPosX() <= bird->getPosX()) {
			static ESprite* temp = nullptr;
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
			/*if (pipes->isCollisionWith(bird)) {
				this->onBirdDie();
			}*/
		}
		// ��С��������С�ڵ��棬��Ϸ����
		if (EApp::getHeight() - bird->getPosY() <= 123) {
			// С������
			if (bird->living) {
				this->onBirdDie();
			}
			// ��Ϸ������ֹͣ�����ʱ��
			ETimerManager::stopAllTimers();
			// ��С��ֹͣ
			bird->setPosY(EApp::getHeight() - 123);
			bird->setStatus(0);
			// ��ʾ��Ϸ��������
			this->onGameOver();
		}
		// ��С��������С�� 0���������������Ϸ�
		if (bird->getPosY() < 0) {
			bird->setPosY(0);
			bird->speed = 0;
		}
	});
	timer->bindWith(this);
}

void GameScene::onBirdDie()
{
	// С������
	bird->living = false;
	// ��С��������
	bird->setRotation(90);
	// ������Ч
	//MusicUtils::playMusic(_T("res/sound/hit.mp3"));
	// ֹͣ����
	ground->stop();
	// ֹͣˮ��
	pipes->stop();
	// ֹͣ���Ͱ�������
	EMsgManager::stopAllMouseListenersBindedWith(this);
	EMsgManager::stopAllKeyboardListenersBindedWith(this);
	// ���ص÷�
	scoreImage->runAction(new EActionFadeOut(0.5f));
	// ��������
	auto white = new ESprite(ImageLoader::getImage(L"white"));
	white->setAnchor(0, 0);
	white->setOpacity(0);
	white->setScale(16, 16);
	white->runAction(new EActionTwo(new EActionFadeIn(0.1f), new EActionFadeOut(0.1f)));
	this->add(white);
}

void GameScene::onGameOver()
{
	this->add(new GameOverLayer(score));
}
