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
	auto background = gcnew Sprite(ResLoader::getImage(L"bg_day"));
	background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(background);

	// ��ӵ���
	this->addChild(gcnew Ground());

	// ��ӱ���ͼƬ
	auto title = gcnew Sprite(ResLoader::getImage(L"title"));
	title->setPos(Window::getWidth() / 2, 150);
	this->addChild(title);

	// ���С��
	auto bird = gcnew Bird();
	bird->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(bird);

	// ������ʼ��ť����״̬�Ͱ���״̬ʱ��ʾ�ľ���
	auto startBtnNormal = gcnew Sprite(ResLoader::getImage(L"button_play"));
	auto startBtnSelected = gcnew Sprite(ResLoader::getImage(L"button_play"));
	startBtnSelected->setPosY(5);	// ��ť��ѡ��ʱ�����ƶ�һ���
	// ��ӿ�ʼ��ť
	auto startBtn = gcnew Button(startBtnNormal, startBtnSelected);
	// ���¿�ʼ��ť������ Game ����
	startBtn->setClickFunc([] {
		MusicPlayer::play(L"res/sound/click.wav");
		SceneManager::enter(gcnew GameScene(), gcnew FadeTransition(0.6f));
	});
	startBtn->setPosX(Window::getWidth() / 2);
	startBtn->setPosY(Window::getHeight() - startBtnNormal->getHeight() - 100);
	this->addChild(startBtn);

	// ��Ӵ򿪷������Ӱ�ť
	auto shareBtnNormal = gcnew Sprite(ResLoader::getImage(L"button_share"));
	auto shareBtnSelected = gcnew Sprite(ResLoader::getImage(L"button_share"));
	shareBtnSelected->setPosY(5);
	auto shareBtn = gcnew Button(shareBtnNormal, shareBtnSelected);
	// ���°�ť�򿪳�����
	shareBtn->setClickFunc([] {
		MusicPlayer::play(L"res/sound/click.wav");
		ShellExecute(NULL, L"open", L"https://github.com/Easy2D/FlappyBird-Easy2D", NULL, NULL, SW_SHOWNORMAL);
	});
	shareBtn->setPosX(Window::getWidth() / 2);
	shareBtn->setPosY(Window::getHeight() - shareBtnNormal->getHeight() - 80);
	this->addChild(shareBtn);

	// ��� copyright ͼƬ
	auto copyright = gcnew Sprite(ResLoader::getImage(L"brand_copyright"));
	copyright->setPos(Window::getWidth() / 2, Window::getHeight() - 20);
	this->addChild(copyright);
}

void StartScene::onEnter()
{
	// ���볡��ʱ������Ч
	MusicPlayer::play(L"res/sound/swoosh.wav");
}
