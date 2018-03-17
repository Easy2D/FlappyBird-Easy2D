#include "GameOverLayer.h"
#include "GameScene.h"
#include "Number.h"
#include "ResLoader.h"
#include <shellapi.h>


GameOverLayer::GameOverLayer(int score)
{
	// ��ʾ GameOver ͼƬ
	auto gameover = new Sprite(ResLoader::getImage("text_game_over"));
	gameover->setPivot(0.5, 0);
	gameover->setPosY(120);
	this->addChild(gameover);

	// ���ص÷ְ�
	initPanel(score);

	// ���ذ�ť
	initButtons();

	// �������
	this->setPosX(Window::getWidth() / 2);
	// ���ڵ������Ƶ���Ļ�·�
	this->setPosY(Window::getHeight());
	
	// ���������������˶����ڵĸ߶�
	auto vec = Vector(0, -Window::getHeight());
	// λ�ƶ������õ÷����ӵײ��ƶ�����
	this->runAction(new ActionMoveBy(1, vec));
}

void GameOverLayer::initPanel(int score)
{
	// ��ʾ�÷ְ�
	auto panel = new Sprite(ResLoader::getImage("score_panel"));
	panel->setPosY(Window::getHeight() / 2);
	this->addChild(panel);

	// ��ȡ��߷�
	int bestScore = Data::getInt("best_score", 0);

	// ������߷�
	if (score > bestScore) {
		bestScore = score;
		Data::saveInt("best_score", bestScore);
		// ��� new ͼ��
		auto newImage = new Sprite(ResLoader::getImage("new"));
		newImage->setPos(26, 23);
		panel->addChild(newImage);
	}

	// ��ӽ���
	auto modalFrame = getModal(score);
	if (modalFrame) {
		auto modal = new Sprite(modalFrame);
		modal->setPos(-65, 5);
		panel->addChild(modal);
		// �������
		auto blink = new Sprite(ResLoader::getImage("blink_00"));
		// ���⶯��
		auto frames = new Animation(130);
		frames->addKeyframe(ResLoader::getImage("blink_00"));
		frames->addKeyframe(ResLoader::getImage("blink_01"));
		frames->addKeyframe(ResLoader::getImage("blink_02"));
		frames->addKeyframe(ResLoader::getImage("blink_01"));
		frames->addKeyframe(ResLoader::getImage("blink_00"));
		// �������λ�õĶ���
		auto action = new ActionCallback([=] {
			double x = Random::range(-modal->getWidth() / 2, modal->getWidth() / 2);
			double y = Random::range(-modal->getHeight() / 2, modal->getHeight() / 2);
			blink->setPos(x, y);
		});
		// ����������ѭ������
		blink->runAction(new ActionLoop(new ActionTwo(action, frames)));
		modal->addChild(blink);
	}

	// ��ʾ�÷�
	auto scoreImage = new Number();
	scoreImage->setPos(91, -27);
	scoreImage->setLittleNumber(score);
	panel->addChild(scoreImage);

	// ��ʾ��߷�
	auto bestScoreImage = new Number();
	bestScoreImage->setPos(91, 14);
	bestScoreImage->setLittleNumber(bestScore);
	panel->addChild(bestScoreImage);
}

void GameOverLayer::initButtons()
{
	// ��ʾ���¿�ʼ��ť
	auto restartBtnNormal = new Sprite(ResLoader::getImage("button_restart"));
	auto restartBtnSelected = new Sprite(ResLoader::getImage("button_restart"));
	restartBtnSelected->setPosY(5);
	auto restart = new Button(restartBtnNormal, restartBtnSelected);
	// �������¿�ʼ������һ���µ� GameScene
	restart->setCallback([] {
		MusicManager::play("res/sound/click.wav");
		SceneManager::enter(new GameScene(), new TransitionFade(0.3, 0.3), false);
	});
	restart->setPosY(360);
	this->addChild(restart);

	// ��ʾ�������˵���ť
	auto menuBtnNormal = new Sprite(ResLoader::getImage("button_menu"));
	auto menuBtnSelected = new Sprite(ResLoader::getImage("button_menu"));
	menuBtnSelected->setPosY(5);
	auto menu = new Button(menuBtnNormal, menuBtnSelected);
	// ���·������˵���������һ������
	menu->setCallback([] {
		MusicManager::play("res/sound/click.wav");
		SceneManager::back(new TransitionFade(0.3, 0.3));
	});
	menu->setPosY(420);
	this->addChild(menu);

	// ��ʾ���Ӱ�ť
	auto shareBtnNormal = new Sprite(ResLoader::getImage("button_share"));
	auto shareBtnSelected = new Sprite(ResLoader::getImage("button_share"));
	shareBtnSelected->setPosY(5);
	auto share = new Button(shareBtnNormal, shareBtnSelected);
	// �������Ӱ�ť��������
	share->setCallback([] {
		MusicManager::play("res/sound/click.wav");
		ShellExecuteA(NULL, "open", "https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	share->setPosY(455);
	this->addChild(share);
}

Image* GameOverLayer::getModal(int score)
{
	if (score < 10) {
		return nullptr;
	}
	else if (score >= 10 && score < 20) {
		return ResLoader::getImage("medals_0");	// ͭ��
	}
	else if (score >= 20 && score < 30) {
		return ResLoader::getImage("medals_1");	// ����
	}
	else if (score >= 30 && score < 50) {
		return ResLoader::getImage("medals_2");	// ����
	}
	else {
		return ResLoader::getImage("medals_3");	// ��ʯ����
	}
}
