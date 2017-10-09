#include "GameScene.h"
#include "ImageLoader.h"


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
		// ���������������µ���Ϣʱ��ִ�� onClick ����
		if (MouseMsg::getMsg() == MouseMsg::LBUTTON_DOWN) {
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
	// ֹͣ����
	ground->stop();
	// ֹͣˮ��
	pipes->stop();
	// ��������
	auto white = ImageLoader::getImage(_T("white"));
	white->stretch(App::getWidth(), App::getHeight());
	auto whiteSprite = new Sprite(white);
	whiteSprite->setOpacity(0);
	whiteSprite->addAction(new ActionTwo(new ActionFadeIn(0.1f), new ActionFadeOut(0.1f)));
	this->add(whiteSprite);
}

void GameScene::onGameOver()
{
	// ��ʾ GameOver ͼƬ
	auto gameover = ImageLoader::getImage(_T("text_game_over"));
	gameover->setWindowCenterX();
	gameover->setY(120);
	// ��ʾ�÷ְ�
	auto panel = ImageLoader::getImage(_T("score_panel"));
	panel->setWindowCenter();
	// ��ʾ���¿�ʼ��ť
	auto restart = new ImageButton(ImageLoader::getImage(_T("button_restart")));
	restart->setWindowCenterX();
	restart->setClickedCallback([] {
		// �������¿�ʼ������һ���µ� GameScene
		App::enterScene(new GameScene(), false);
	});
	// ��ť����ʱ
	restart->setSelectCallback([=] {
		restart->move(0, 5);
	});
	restart->setUnselectCallback([=] {
		restart->move(0, -5);
	});
	restart->setY(330);
	// ��ʾ�������˵���ť
	auto menu = new ImageButton(ImageLoader::getImage(_T("button_menu")));
	menu->setWindowCenterX();
	menu->setClickedCallback([] {
		// ���·������˵���������һ������
		App::backScene();
	});
	// ��ť����ʱ
	menu->setSelectCallback([=] {
		menu->move(0, 5);
	});
	menu->setUnselectCallback([=] {
		menu->move(0, -5);
	});
	menu->setY(400);
	// �ϲ�Ϊһ���ڵ�
	auto all = new BatchNode();
	all->add(gameover);
	all->add(panel);
	all->add(restart);
	all->add(menu);
	all->setY(App::getHeight());
	this->add(all);
	// ��Timerʵ�ּ򵥵��ƶ�����
	Timer::addTimer(_T("game_over"), [=] {
		if (all->getY() > 0) {
			all->move(0, -8);
		}
		else {
			Timer::stopTimer(_T("game_over"));
		}
	});
}
