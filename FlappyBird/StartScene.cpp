#include "StartScene.h"
#include "ResLoader.h"
#include "GameScene.h"
#include "Bird.h"
#include "Ground.h"
#include "GameOverLayer.h"
#include <shellapi.h>

StartScene::StartScene()
{
	// ��ӱ���
	auto background = new ESprite(ResLoader::getImage(L"bg_day"));
	background->setPos(EWindow::getWidth() / 2, EWindow::getHeight() / 2);
	this->add(background);

	// ��ӵ���
	this->add(new Ground());

	// ��ӱ���ͼƬ
	auto title = new ESprite(ResLoader::getImage(L"title"));
	title->setPos(EWindow::getWidth() / 2, 150);
	this->add(title);

	// ���С��
	auto bird = new Bird();
	bird->setPos(EWindow::getWidth() / 2, EWindow::getHeight() / 2);
	this->add(bird);

	// ������ʼ��ť����״̬�Ͱ���״̬ʱ��ʾ�ľ���
	auto startBtnNormal = new ESprite(ResLoader::getImage(L"button_play"));
	auto startBtnSelected = new ESprite(ResLoader::getImage(L"button_play"));
	startBtnSelected->setPosY(5);	// ��ť��ѡ��ʱ�����ƶ�һ���
	// ��ӿ�ʼ��ť
	auto startBtn = new EButton(startBtnNormal, startBtnSelected);
	// ���¿�ʼ��ť������ Game ����
	startBtn->setCallback([] {
		ResLoader::playMusic(L"res/sound/click.wav");
		ESceneManager::enterScene(new GameScene(), new ETransitionFade(0.3f, 0.3f));
	});
	startBtn->setPosX(EWindow::getWidth() / 2);
	startBtn->setPosY(EWindow::getHeight() - startBtnNormal->getHeight() - 100);
	this->add(startBtn);

	// ��Ӵ򿪷������Ӱ�ť
	auto shareBtnNormal = new ESprite(ResLoader::getImage(L"button_share"));
	auto shareBtnSelected = new ESprite(ResLoader::getImage(L"button_share"));
	shareBtnSelected->setPosY(5);
	auto shareBtn = new EButton(shareBtnNormal, shareBtnSelected);
	// ���°�ť�򿪳�����
	shareBtn->setCallback([] {
		ResLoader::playMusic(L"res/sound/click.wav");
		ShellExecute(NULL, L"open", L"https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	shareBtn->setPosX(EWindow::getWidth() / 2);
	shareBtn->setPosY(EWindow::getHeight() - shareBtnNormal->getHeight() - 80);
	this->add(shareBtn);

	// ��� copyright ͼƬ
	auto copyright = new ESprite(ResLoader::getImage(L"brand_copyright"));
	copyright->setPos(EWindow::getWidth() / 2, EWindow::getHeight() - 20);
	this->add(copyright);
}

void StartScene::onEnter()
{
	// ���볡��ʱ������Ч
	ResLoader::playMusic(L"res/sound/swoosh.wav");
}
