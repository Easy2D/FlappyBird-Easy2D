#include "GameOverLayer.h"
#include "GameScene.h"
#include "Number.h"
#include "ResLoader.h"
#include <shellapi.h>


GameOverLayer::GameOverLayer(int score)
{
	// ��ʾ GameOver ͼƬ
	auto gameover = new ESprite(ResLoader::getImage(L"text_game_over"));
	gameover->setPivot(0.5f, 0);
	gameover->setPosY(120);
	this->addChild(gameover);

	// ���ص÷ְ�
	initPanel(score);

	// ���ذ�ť
	initButtons();

	// �������
	this->setPosX(EWindow::getWidth() / 2);
	// ���ڵ������Ƶ���Ļ�·�
	this->setPosY(EWindow::getHeight());
	
	// ���������������˶����ڵĸ߶�
	auto vec = EVector2(0, -EWindow::getHeight());
	// λ�ƶ������õ÷����ӵײ��ƶ�����
	this->runAction(new EActionMoveBy(1, vec));
}

void GameOverLayer::initPanel(int score)
{
	// ��ʾ�÷ְ�
	auto panel = new ESprite(ResLoader::getImage(L"score_panel"));
	panel->setPosY(EWindow::getHeight() / 2);
	this->addChild(panel);

	// ��ȡ��߷�
	int bestScore = EData::getInt(L"best_score", 0);

	// ������߷�
	if (score > bestScore) {
		bestScore = score;
		EData::saveInt(L"best_score", bestScore);
		// ��� new ͼ��
		auto newImage = new ESprite(ResLoader::getImage(L"new"));
		newImage->setPos(26, 23);
		panel->addChild(newImage);
	}

	// ��ӽ���
	auto modalFrame = getModal(score);
	if (modalFrame) {
		auto modal = new ESprite(modalFrame);
		modal->setPos(-65, 5);
		panel->addChild(modal);
		// �������
		auto blink = new ESprite(ResLoader::getImage(L"blink_00"));
		// ����֡����
		auto frames = new EAnimation(130);
		frames->addKeyframe(ResLoader::getImage(L"blink_00"));
		frames->addKeyframe(ResLoader::getImage(L"blink_01"));
		frames->addKeyframe(ResLoader::getImage(L"blink_02"));
		frames->addKeyframe(ResLoader::getImage(L"blink_01"));
		frames->addKeyframe(ResLoader::getImage(L"blink_00"));
		// �������λ�õĶ���
		auto action = new EActionCallback([=] {
			float x = ERandom::range(-modal->getWidth() / 2, modal->getWidth() / 2);
			float y = ERandom::range(-modal->getHeight() / 2, modal->getHeight() / 2);
			blink->setPos(x, y);
		});
		// ����������ѭ������
		blink->runAction(new EActionLoop(new EActionTwo(action, frames)));
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
	auto restartBtnNormal = new ESprite(ResLoader::getImage(L"button_restart"));
	auto restartBtnSelected = new ESprite(ResLoader::getImage(L"button_restart"));
	restartBtnSelected->setPosY(5);
	auto restart = new EButton(restartBtnNormal, restartBtnSelected);
	// �������¿�ʼ������һ���µ� GameScene
	restart->setCallback([] {
		ResLoader::playMusic(L"res/sound/click.wav");
		ESceneManager::enterScene(new GameScene(), new ETransitionFade(0.3f, 0.3f), false);
	});
	restart->setPosY(360);
	this->addChild(restart);

	// ��ʾ�������˵���ť
	auto menuBtnNormal = new ESprite(ResLoader::getImage(L"button_menu"));
	auto menuBtnSelected = new ESprite(ResLoader::getImage(L"button_menu"));
	menuBtnSelected->setPosY(5);
	auto menu = new EButton(menuBtnNormal, menuBtnSelected);
	// ���·������˵���������һ������
	menu->setCallback([] {
		ResLoader::playMusic(L"res/sound/click.wav");
		ESceneManager::backScene(new ETransitionFade(0.3f, 0.3f));
	});
	menu->setPosY(420);
	this->addChild(menu);

	// ��ʾ���Ӱ�ť
	auto shareBtnNormal = new ESprite(ResLoader::getImage(L"button_share"));
	auto shareBtnSelected = new ESprite(ResLoader::getImage(L"button_share"));
	shareBtnSelected->setPosY(5);
	auto share = new EButton(shareBtnNormal, shareBtnSelected);
	// �������Ӱ�ť��������
	share->setCallback([] {
		ResLoader::playMusic(L"res/sound/click.wav");
		ShellExecute(NULL, L"open", L"https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	share->setPosY(455);
	this->addChild(share);
}

EImage* GameOverLayer::getModal(int score)
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
