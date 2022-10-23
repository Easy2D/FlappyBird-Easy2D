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
	// 添加背景
	auto background = gcnew Sprite(ResLoader::getKeyFrame("bg_day"));
	background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(background);

	// 添加地面
	this->addChild(gcnew Ground());

	// 添加标题图片
	auto title = gcnew Sprite(ResLoader::getKeyFrame("title"));
	title->setPos(Window::getWidth() / 2, 150);
	this->addChild(title);

	// 添加小鸟
	auto bird = gcnew Bird();
	bird->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(bird);

	// 添加开始按钮
	auto startBtn = gcnew MyButton("button_play", []() {
		ResLoader::playMusic(MusicType::Click);
		// 按下开始按钮，进入 Game 场景
		SceneManager::enter(gcnew GameScene(), gcnew FadeTransition(0.6f));
		});
	startBtn->setPosX(Window::getWidth() / 2);
	startBtn->setPosY(Window::getHeight() - startBtn->getHeight() - 100);
	this->addChild(startBtn);

	// 添加打开分享链接按钮
	auto shareBtn = gcnew MyButton("button_share", []() {
		ResLoader::playMusic(MusicType::Click);
		// 按下按钮打开超链接
		ShellExecuteA(NULL, "open", "https://github.com/Easy2D/FlappyBird-Easy2D", NULL, NULL, SW_SHOWNORMAL);
		});
	shareBtn->setPosX(Window::getWidth() / 2);
	shareBtn->setPosY(Window::getHeight() - shareBtn->getHeight() - 80);
	this->addChild(shareBtn);

	// 添加 copyright 图片
	auto copyright = gcnew Sprite(ResLoader::getKeyFrame("brand_copyright"));
	copyright->setPos(Window::getWidth() / 2, Window::getHeight() - 20);
	this->addChild(copyright);
}

void StartScene::onEnter()
{
	// 进入场景时播放音效
	ResLoader::playMusic(MusicType::Swoosh);
}
