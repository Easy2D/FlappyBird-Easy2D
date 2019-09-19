#include "GameOverLayer.h"
#include "GameScene.h"
#include "Number.h"
#include "ResLoader.h"
#include <shellapi.h>


GameOverLayer::GameOverLayer(int score)
{
	// ��ʾ GameOver ͼƬ
	auto gameover = gcnew Sprite(ResLoader::getImage(L"text_game_over"));
	gameover->setAnchor(0.5f, 0);
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
	auto vec = Vector2(0, -Window::getHeight());
	// λ�ƶ������õ÷����ӵײ��ƶ�����
	this->runAction(gcnew MoveBy(1, vec));
}

void GameOverLayer::initPanel(int score)
{
	// ��ʾ�÷ְ�
	auto panel = gcnew Sprite(ResLoader::getImage(L"score_panel"));
	panel->setPosY(Window::getHeight() / 2);
	this->addChild(panel);

	// ��ȡ��߷�
	int bestScore = Data::getInt(L"best_score", 0);

	// ������߷�
	if (score > bestScore) {
		bestScore = score;
		Data::saveInt(L"best_score", bestScore);
		// ��� gcnew ͼ��
		auto newImage = gcnew Sprite(ResLoader::getImage(L"new"));
		newImage->setPos(145, 86);
		panel->addChild(newImage);
	}

	// ��ӽ���
	auto modalFrame = getModal(score);
	if (modalFrame) {
		auto modal = gcnew Sprite(modalFrame);
		modal->setPos(54, 68);
		panel->addChild(modal);
		// �������
		auto blink = gcnew Sprite(ResLoader::getImage(L"blink_00"));
		// ���⶯��
		auto frames = gcnew Animation(0.13f);
		frames->add(ResLoader::getImage(L"blink_00"));
		frames->add(ResLoader::getImage(L"blink_01"));
		frames->add(ResLoader::getImage(L"blink_02"));
		frames->add(ResLoader::getImage(L"blink_01"));
		frames->add(ResLoader::getImage(L"blink_00"));
		// �������λ�õĶ���
		auto action = gcnew CallFunc([=] {
			float x = Random::range(0, modal->getWidth());
			float y = Random::range(0, modal->getHeight());
			blink->setPos(x, y);
		});
		// ����������ѭ������
		blink->runAction(gcnew Loop(gcnew Sequence({ action, gcnew Animate(frames) })));
		modal->addChild(blink);
	}

	// ��ʾ�÷�
	auto scoreImage = gcnew Number();
	scoreImage->setPos(210, 36);
	scoreImage->setLittleNumber(score);
	panel->addChild(scoreImage);

	// ��ʾ��߷�
	auto bestScoreImage = gcnew Number();
	bestScoreImage->setPos(210, 77);
	bestScoreImage->setLittleNumber(bestScore);
	panel->addChild(bestScoreImage);
}

void GameOverLayer::initButtons()
{
	// ��ʾ���¿�ʼ��ť
	auto restartBtnNormal = gcnew Sprite(ResLoader::getImage(L"button_restart"));
	auto restartBtnSelected = gcnew Sprite(ResLoader::getImage(L"button_restart"));
	restartBtnSelected->setPosY(5);
	auto restart = gcnew Button(restartBtnNormal, restartBtnSelected);
	// �������¿�ʼ������һ���µ� GameScene
	restart->setClickFunc([] {
		Player::play(L"res/sound/click.wav");
		SceneManager::enter(gcnew GameScene(), gcnew FadeTransition(0.6f), false);
	});
	restart->setPosY(360);
	this->addChild(restart);

	// ��ʾ�������˵���ť
	auto menuBtnNormal = gcnew Sprite(ResLoader::getImage(L"button_menu"));
	auto menuBtnSelected = gcnew Sprite(ResLoader::getImage(L"button_menu"));
	menuBtnSelected->setPosY(5);
	auto menu = gcnew Button(menuBtnNormal, menuBtnSelected);
	// ���·������˵���������һ������
	menu->setClickFunc([] {
		Player::play(L"res/sound/click.wav");
		SceneManager::back(gcnew FadeTransition(0.6f));
	});
	menu->setPosY(420);
	this->addChild(menu);

	// ��ʾ���Ӱ�ť
	auto shareBtnNormal = gcnew Sprite(ResLoader::getImage(L"button_share"));
	auto shareBtnSelected = gcnew Sprite(ResLoader::getImage(L"button_share"));
	shareBtnSelected->setPosY(5);
	auto share = gcnew Button(shareBtnNormal, shareBtnSelected);
	// �������Ӱ�ť��������
	share->setClickFunc([] {
		Player::play(L"res/sound/click.wav");
		ShellExecute(NULL, L"open", L"https://github.com/Easy2D/FlappyBird-Easy2D", NULL, NULL, SW_SHOWNORMAL);
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
		return ResLoader::getImage(L"medals_0");	// ͭ��
	}
	else if (score >= 20 && score < 30) {
		return ResLoader::getImage(L"medals_1");	// ����
	}
	else if (score >= 30 && score < 50) {
		return ResLoader::getImage(L"medals_2");	// ����
	}
	else {
		return ResLoader::getImage(L"medals_3");	// ��ʯ����
	}
}
