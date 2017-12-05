#include "GameOverLayer.h"
#include "GameScene.h"
#include "ResLoader.h"
#include <shellapi.h>


GameOverLayer::GameOverLayer(int score)
{
	// ��ȡ�÷ֺ���߷�
	this->score = 26;// score;
	this->bestScore = 26;// EFileUtils::getInt(L"best_score", 0);
	// �������
	this->setPosX(EApp::getWidth() / 2);
	// ���ڵ������Ƶ���Ļ�·�
	this->setPosY(EApp::getHeight());
	// ��ʾ GameOver ͼƬ
	auto gameover = new ESprite(ResLoader::getImage(L"text_game_over"));
	gameover->setPivot(0.5f, 0);
	gameover->setPosY(120);
	this->addChild(gameover);
	// ���ص÷ְ�
	initPanel();
	// ���ذ�ť
	initButtons();
	
	// λ�ƶ���
	auto actionMove = new EActionMoveBy(1, EVec(0, -EApp::getHeight()));
	auto actionShowScore = new EActionCallback([=] {
		// ������������ʾ�÷�
		this->showScore();
	});
	this->runAction(new EActionTwo(actionMove, actionShowScore));
}

void GameOverLayer::initPanel()
{
	// ��ʾ�÷ְ�
	auto panel = new ESprite(ResLoader::getImage(L"score_panel"));
	panel->setPosY(EApp::getHeight() / 2);
	this->addChild(panel);
	// ������߷�
	if (score >= bestScore) {
		EFileUtils::saveInt(L"best_score", score);
		bestScore = score;
		// ��� new ͼ��
		auto newImage = new ESprite(ResLoader::getImage(L"new"));
		newImage->setPos(26, 23);
		panel->addChild(newImage);
	}
	// ��ӽ���
	auto modalFrame = getModal();
	if (modalFrame) {
		auto modal = new ESprite(modalFrame);
		modal->setPos(-65, 5);
		panel->addChild(modal);
		// �������
		auto blink = new ESprite(ResLoader::getImage(L"blink_00"));
		// ����֡����
		auto frames = new EAnimation(130);
		frames->addFrame(ResLoader::getImage(L"blink_00"));
		frames->addFrame(ResLoader::getImage(L"blink_01"));
		frames->addFrame(ResLoader::getImage(L"blink_02"));
		frames->addFrame(ResLoader::getImage(L"blink_01"));
		frames->addFrame(ResLoader::getImage(L"blink_00"));
		// ִ��֡����ǰ����������λ��
		auto action = new EActionTwo(new EActionCallback([=] {
			float x = ERandom::between(-modal->getWidth() / 2, modal->getWidth() / 2);
			float y = ERandom::between(-modal->getHeight() / 2, modal->getHeight() / 2);
			blink->setPos(x, y);
		}), frames);
		// ִ��ѭ������
		blink->runAction(new EActionLoop(action));
		modal->addChild(blink);
	}
	// ��ʾ�÷�
	scoreImage = new Number();
	scoreImage->setPos(91, -27);
	scoreImage->setLittleNumber(0);
	panel->addChild(scoreImage);
	// ��ʾ��߷�
	bestScoreImage = new Number();
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
	auto restart = new EButton(
		restartBtnNormal,
		restartBtnSelected,
		[] {
		// �������¿�ʼ������һ���µ� GameScene
		ResLoader::playMusic(L"MUSIC_MENU_CLICK");
		EApp::enterScene(new GameScene(), new ETransitionFade(0.3f, 0.3f), false);
	});
	restart->setPosY(360);
	this->addChild(restart);
	// ��ʾ�������˵���ť
	auto menuBtnNormal = new ESprite(ResLoader::getImage(L"button_menu"));
	auto menuBtnSelected = new ESprite(ResLoader::getImage(L"button_menu"));
	menuBtnSelected->setPosY(5);
	auto menu = new EButton(
		menuBtnNormal,
		menuBtnSelected,
		[] {
		// ���·������˵���������һ������
		ResLoader::playMusic(L"MUSIC_MENU_CLICK");
		EApp::backScene(new ETransitionFade(0.3f, 0.3f));
	});
	menu->setPosY(420);
	this->addChild(menu);
	// ��ʾ���Ӱ�ť
	auto shareBtnNormal = new ESprite(ResLoader::getImage(L"button_share"));
	auto shareBtnSelected = new ESprite(ResLoader::getImage(L"button_share"));
	shareBtnSelected->setPosY(5);
	auto share = new EButton(
		shareBtnNormal,
		shareBtnSelected,
		[] {
		ResLoader::playMusic(L"MUSIC_MENU_CLICK");
		ShellExecute(NULL, L"open", L"https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	share->setPosY(455);
	this->addChild(share);
}

void GameOverLayer::showScore()
{
	// �����л����ֵ�ʱ�������1200������ʾ�궯��
	LONGLONG delay = (score > 12) ? LONGLONG(1200.0f / score) : 100;
	// �÷ֶ���
	auto timer = new ETimer(
		[=](int times) {
			// �÷��ϵ����ֱ仯
			scoreImage->setLittleNumber(times + 1);
		}, 
		score,	// ִ�� score ��
		delay,	// ÿ��ִ�м��ʱ��
		true	// ����ִ��
	);
	timer->bindWith(this);
}

ESpriteFrame* GameOverLayer::getModal()
{
	return ResLoader::getImage(L"medals_0");
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
