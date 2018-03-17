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
	auto background = new Sprite(ResLoader::getImage("bg_day"));
	background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->add(background);

	// ��ӵ���
	this->add(new Ground());

	// ��ӱ���ͼƬ
	auto title = new Sprite(ResLoader::getImage("title"));
	title->setPos(Window::getWidth() / 2, 150);
	this->add(title);

	// ���С��
	auto bird = new Bird();
	bird->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->add(bird);

	// ������ʼ��ť����״̬�Ͱ���״̬ʱ��ʾ�ľ���
	auto startBtnNormal = new Sprite(ResLoader::getImage("button_play"));
	auto startBtnSelected = new Sprite(ResLoader::getImage("button_play"));
	startBtnSelected->setPosY(5);	// ��ť��ѡ��ʱ�����ƶ�һ���
	// ��ӿ�ʼ��ť
	auto startBtn = new Button(startBtnNormal, startBtnSelected);
	// ���¿�ʼ��ť������ Game ����
	startBtn->setCallback([] {
		MusicManager::play("res/sound/click.wav");
		SceneManager::enter(new GameScene(), new TransitionFade(0.3, 0.3));
	});
	startBtn->setPosX(Window::getWidth() / 2);
	startBtn->setPosY(Window::getHeight() - startBtnNormal->getHeight() - 100);
	this->add(startBtn);

	// ��Ӵ򿪷������Ӱ�ť
	auto shareBtnNormal = new Sprite(ResLoader::getImage("button_share"));
	auto shareBtnSelected = new Sprite(ResLoader::getImage("button_share"));
	shareBtnSelected->setPosY(5);
	auto shareBtn = new Button(shareBtnNormal, shareBtnSelected);
	// ���°�ť�򿪳�����
	shareBtn->setCallback([] {
		MusicManager::play("res/sound/click.wav");
		ShellExecuteA(NULL, "open", "https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	shareBtn->setPosX(Window::getWidth() / 2);
	shareBtn->setPosY(Window::getHeight() - shareBtnNormal->getHeight() - 80);
	this->add(shareBtn);

	// ��� copyright ͼƬ
	auto copyright = new Sprite(ResLoader::getImage("brand_copyright"));
	copyright->setPos(Window::getWidth() / 2, Window::getHeight() - 20);
	this->add(copyright);
}

void StartScene::onEnter()
{
	// ���볡��ʱ������Ч
	MusicManager::play("res/sound/swoosh.wav");
}
