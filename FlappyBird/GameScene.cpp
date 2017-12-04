#include "GameScene.h"
#include "ResLoader.h"
#include "GameOverLayer.h"

GameScene::GameScene()
{
	// ��ӱ���
	auto background = new ESprite(ResLoader::getImage(L"bg_day"));
	// ���ñ���ê��Ϊ���Ͻ�
	background->setPivot(0, 0);
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
	ready = new ESprite(ResLoader::getImage(L"text_ready"));
	ready->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2 - 70);
	this->add(ready);
	// ��ӽ̳�ͼƬ
	tutorial = new ESprite(ResLoader::getImage(L"tutorial"));
	tutorial->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2 + 30);
	this->add(tutorial);

	// ��������Ϣ����
	auto mouseListener = new EListenerMousePress([=](EPoint) {
		// ���������������µ���Ϣʱ��ִ�� onClick ����
		this->onClick();
	});
	// �󶨼�����
	mouseListener->bindWith(this);

	// ��Ӽ��̰�������
	auto keyboardListener = new EListenerKeyboardPress([=] {
		// ���¿ո�ʱ��ִ�� onClick ����
		if (EKeyboardMsg::getKeyValue() == EKeyboardMsg::KEY::SPACE) {
			this->onClick();
		}
	});
	// �󶨼�����
	keyboardListener->bindWith(this);

	// �������Ӵ�������
	auto collisionListener = new EListenerPhysicsCollision([=]() {
		// ֻҪ�нӴ���Ϣ��������˵��С������
		if (bird->living) {
			this->onBirdDie();
		}
	});
	// �󶨼�����
	collisionListener->bindWith(this);
}

void GameScene::onEnter()
{
	// ���볡��ʱ������Ч
	ResLoader::playMusic(L"MUSIC_SWOOSH");
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
		ResLoader::playMusic(L"MUSIC_FLY");
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
		bird->movePosY(bird->speed);
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
				// ������Ч
				ResLoader::playMusic(L"MUSIC_POINT");
			}
		}
		// ��С��������С�ڵ��棬��Ϸ����
		if (EApp::getHeight() - bird->getPosY() <= 123) {
			// ��Ϸ������ֹͣ�����ʱ��
			ETimerManager::stopAllTimers();
			// ��С��ֹͣ
			bird->setPosY(EApp::getHeight() - 123);
			bird->setStatus(0);
			// ��С��������
			bird->setRotation(90);
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
	// ������Ч
	ResLoader::playMusic(L"MUSIC_HIT");
	// ֹͣ����
	ground->stop();
	// ֹͣˮ��
	pipes->stop();
	// ֹͣ���Ͱ�������
	EMsgManager::stopAllMouseListeners();
	EMsgManager::stopAllKeyboardListeners();
	// ֹͣ��ײ����
	EPhysicsManager::stopAllListeners();
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

void GameScene::onGameOver()
{
	this->add(new GameOverLayer(score));
}
