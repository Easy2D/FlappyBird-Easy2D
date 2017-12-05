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
	// ���ñ���ê��Ϊ���Ͻ�
	background->setPivot(0, 0);
	this->add(background);
	// ��ӵ���
	this->add(new Ground());
	// ��ӱ���ͼƬ
	auto title = new ESprite(ResLoader::getImage(L"title"));
	title->setPos(EApp::getWidth() / 2, 150);
	this->add(title);
	// ���С��
	auto bird = new Bird();
	bird->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2);
	this->add(bird);
	// ������ʼ��ť����״̬�Ͱ���״̬ʱ��ʾ�ľ���
	auto startBtnNormal = new ESprite(ResLoader::getImage(L"button_play"));
	auto startBtnSelected = new ESprite(ResLoader::getImage(L"button_play"));
	startBtnNormal->setName(L"test");
	startBtnSelected->setPosY(5);	// ��ť��ѡ��ʱ�����ƶ�һ���
	// ��ӿ�ʼ��ť
	auto startBtn = new EButton(
		startBtnNormal,
		startBtnSelected,
		[] {
		// ���¿�ʼ��ť������ Game ����
		ResLoader::playMusic(L"MUSIC_MENU_CLICK");
		EApp::enterScene(new GameScene(), new ETransitionFade(0.3f, 0.3f));
	});
	startBtn->setPosX(EApp::getWidth() / 2);
	startBtn->setPosY(EApp::getHeight() - startBtnNormal->getHeight() - 100);
	this->add(startBtn);
	// ��Ӵ򿪷������Ӱ�ť
	auto shareBtnNormal = new ESprite(ResLoader::getImage(L"button_share"));
	auto shareBtnSelected = new ESprite(ResLoader::getImage(L"button_share"));
	shareBtnSelected->setPosY(5);
	auto shareBtn = new EButton(
		shareBtnNormal,
		shareBtnSelected,
		[] {
		// ���°�ť�򿪳�����
		ResLoader::playMusic(L"MUSIC_MENU_CLICK");
		ShellExecute(NULL, L"open", L"https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	shareBtn->setPosX(EApp::getWidth() / 2);
	shareBtn->setPosY(EApp::getHeight() - shareBtnNormal->getHeight() - 80);
	this->add(shareBtn);

	// ��� copyright ͼƬ
	auto copyright = new ESprite(ResLoader::getImage(L"brand_copyright"));
	copyright->setPosX(EApp::getWidth() / 2);
	copyright->setPosY(EApp::getHeight() - 20);
	this->add(copyright);
}

void StartScene::onEnter()
{
	// ���볡��ʱ������Ч
	ResLoader::playMusic(L"MUSIC_SWOOSH");
}
