#include "StartScene.h"
#include "ResLoader.h"
#include "GameScene.h"
#include "Bird.h"
#include "Ground.h"
#include "GameOverLayer.h"
#include "MyButton.h"
#include <shellapi.h>

StartScene::StartScene()
{
	// ��ӱ���
	auto background = gcnew Sprite(ResLoader::getKeyFrame("bg_day"));
	background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(background);

	// ��ӵ���
	this->addChild(gcnew Ground());

	// ��ӱ���ͼƬ
	auto title = gcnew Sprite(ResLoader::getKeyFrame("title"));
	title->setPos(Window::getWidth() / 2, 150);
	this->addChild(title);

	// ���С��
	auto bird = gcnew Bird();
	bird->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(bird);

	// ��ӿ�ʼ��ť
	auto startBtn = gcnew MyButton("button_play", []() {
		ResLoader::playMusic(MusicType::Click);
		// ���¿�ʼ��ť������ Game ����
		SceneManager::enter(gcnew GameScene(), gcnew FadeTransition(0.6f));
		});
	startBtn->setPosX(Window::getWidth() / 2);
	startBtn->setPosY(Window::getHeight() - startBtn->getHeight() - 100);
	this->addChild(startBtn);

	// ��Ӵ򿪷������Ӱ�ť
	auto shareBtn = gcnew MyButton("button_share", []() {
		ResLoader::playMusic(MusicType::Click);
		// ���°�ť�򿪳�����
		ShellExecuteA(NULL, "open", "https://github.com/Easy2D/FlappyBird-Easy2D", NULL, NULL, SW_SHOWNORMAL);
		});
	shareBtn->setPosX(Window::getWidth() / 2);
	shareBtn->setPosY(Window::getHeight() - shareBtn->getHeight() - 80);
	this->addChild(shareBtn);

	// ��� copyright ͼƬ
	auto copyright = gcnew Sprite(ResLoader::getKeyFrame("brand_copyright"));
	copyright->setPos(Window::getWidth() / 2, Window::getHeight() - 20);
	this->addChild(copyright);
}

void StartScene::onEnter()
{
	// ���볡��ʱ������Ч
	ResLoader::playMusic(MusicType::Swoosh);
}
