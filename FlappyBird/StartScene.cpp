#include "StartScene.h"
#include "ImageLoader.h"
#include "GameScene.h"
#include "Bird.h"
#include "Ground.h"
#include "GameOverLayer.h"
#include <shellapi.h>

StartScene::StartScene()
{
	// ��ӱ���
	auto background = new ESprite(ImageLoader::getImage(L"bg_day"));
	// ���ñ���ê��Ϊ���Ͻ�
	background->setAnchor(0, 0);
	this->add(background);
	// ��ӵ���
	this->add(new Ground());
	// ��ӱ���ͼƬ
	auto title = new ESprite(ImageLoader::getImage(L"title"));
	title->setPos(EApp::getWidth() / 2, 150);
	this->add(title);
	// ���С��
	auto bird = new Bird();
	bird->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2);
	this->add(bird);
	// ������ʼ��ť����״̬�Ͱ���״̬ʱ��ʾ�ľ���
	auto startBtnNormal = new ESprite(ImageLoader::getImage(L"button_play"));
	auto startBtnSelected = new ESprite(ImageLoader::getImage(L"button_play"));
	startBtnSelected->setPosY(5);	// ��ť��ѡ��ʱ�����ƶ�һ���
	// ��ӿ�ʼ��ť
	auto startBtn = new EButton(
		startBtnNormal,
		startBtnSelected,
		[] {
		// ���¿�ʼ��ť������ Game ����
		EApp::enterScene(new GameScene(), new ETransitionFade(0.3f, 0.3f));
	});
	startBtn->setPosX(EApp::getWidth() / 2);
	startBtn->setPosY(EApp::getHeight() - startBtnNormal->getHeight() - 100);
	this->add(startBtn);
	// ��Ӵ򿪷������Ӱ�ť
	auto shareBtnNormal = new ESprite(ImageLoader::getImage(L"button_share"));
	auto shareBtnSelected = new ESprite(ImageLoader::getImage(L"button_share"));
	shareBtnSelected->setPosY(5);
	auto shareBtn = new EButton(
		shareBtnNormal,
		shareBtnSelected,
		[] {
		// ���°�ť�򿪳�����
		//MusicUtils::playMusic(_T("res/sound/MenuClick.mp3"));
		ShellExecute(NULL, L"open", L"https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	shareBtn->setPosX(EApp::getWidth() / 2);
	shareBtn->setPosY(EApp::getHeight() - shareBtnNormal->getHeight() - 80);
	this->add(shareBtn);

	// ��� copyright ͼƬ
	auto copyright = new ESprite(ImageLoader::getImage(L"brand_copyright"));
	copyright->setPosX(EApp::getWidth() / 2);
	copyright->setPosY(EApp::getHeight() - 20);
	this->add(copyright);

	// Ԥ������Ч
	/*MusicUtils::preloadMusic(_T("res/sound/fly.mp3"));
	MusicUtils::preloadMusic(_T("res/sound/hit.mp3"));
	MusicUtils::preloadMusic(_T("res/sound/point.mp3"));
	MusicUtils::preloadMusic(_T("res/sound/swoosh.mp3"));
	MusicUtils::preloadMusic(_T("res/sound/MenuClick.mp3"));*/
}

void StartScene::onEnter()
{
	// ���볡��ʱ������Ч
	//MusicUtils::playMusic(_T("res/sound/swoosh.mp3"));
}
