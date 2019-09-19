#include "StartScene.h"
#include "ResLoader.h"
#include "GameScene.h"
#include "Bird.h"
#include "Ground.h"
#include "GameOverLayer.h"
#include <shellapi.h>

StartScene::StartScene()
{
	// 添加背景
	auto background = gcnew Sprite(ResLoader::getImage(L"bg_day"));
	background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(background);

	// 添加地面
	this->addChild(gcnew Ground());

	// 添加标题图片
	auto title = gcnew Sprite(ResLoader::getImage(L"title"));
	title->setPos(Window::getWidth() / 2, 150);
	this->addChild(title);

	// 添加小鸟
	auto bird = gcnew Bird();
	bird->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(bird);

	// 创建开始按钮正常状态和按下状态时显示的精灵
	auto startBtnNormal = gcnew Sprite(ResLoader::getImage(L"button_play"));
	auto startBtnSelected = gcnew Sprite(ResLoader::getImage(L"button_play"));
	startBtnSelected->setPosY(5);	// 按钮被选中时向下移动一点点
	// 添加开始按钮
	auto startBtn = gcnew Button(startBtnNormal, startBtnSelected);
	// 按下开始按钮，进入 Game 场景
	startBtn->setClickFunc([] {
		MusicPlayer::play(L"res/sound/click.wav");
		SceneManager::enter(gcnew GameScene(), gcnew FadeTransition(0.6f));
	});
	startBtn->setPosX(Window::getWidth() / 2);
	startBtn->setPosY(Window::getHeight() - startBtnNormal->getHeight() - 100);
	this->addChild(startBtn);

	// 添加打开分享链接按钮
	auto shareBtnNormal = gcnew Sprite(ResLoader::getImage(L"button_share"));
	auto shareBtnSelected = gcnew Sprite(ResLoader::getImage(L"button_share"));
	shareBtnSelected->setPosY(5);
	auto shareBtn = gcnew Button(shareBtnNormal, shareBtnSelected);
	// 按下按钮打开超链接
	shareBtn->setClickFunc([] {
		MusicPlayer::play(L"res/sound/click.wav");
		ShellExecute(NULL, L"open", L"https://github.com/Easy2D/FlappyBird-Easy2D", NULL, NULL, SW_SHOWNORMAL);
	});
	shareBtn->setPosX(Window::getWidth() / 2);
	shareBtn->setPosY(Window::getHeight() - shareBtnNormal->getHeight() - 80);
	this->addChild(shareBtn);

	// 添加 copyright 图片
	auto copyright = gcnew Sprite(ResLoader::getImage(L"brand_copyright"));
	copyright->setPos(Window::getWidth() / 2, Window::getHeight() - 20);
	this->addChild(copyright);
}

void StartScene::onEnter()
{
	// 进入场景时播放音效
	MusicPlayer::play(L"res/sound/swoosh.wav");
}
