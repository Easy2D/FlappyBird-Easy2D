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
	auto background = new ESprite(ResLoader::getImage(L"bg_day"));
	// 设置背景锚点为左上角
	background->setPivot(0, 0);
	this->add(background);
	// 添加地面
	this->add(new Ground());
	// 添加标题图片
	auto title = new ESprite(ResLoader::getImage(L"title"));
	title->setPos(EApp::getWidth() / 2, 150);
	this->add(title);
	// 添加小鸟
	auto bird = new Bird();
	bird->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2);
	this->add(bird);
	// 创建开始按钮正常状态和按下状态时显示的精灵
	auto startBtnNormal = new ESprite(ResLoader::getImage(L"button_play"));
	auto startBtnSelected = new ESprite(ResLoader::getImage(L"button_play"));
	startBtnNormal->setName(L"test");
	startBtnSelected->setPosY(5);	// 按钮被选中时向下移动一点点
	// 添加开始按钮
	auto startBtn = new EButton(
		startBtnNormal,
		startBtnSelected,
		[] {
		// 按下开始按钮，进入 Game 场景
		ResLoader::playMusic(L"MUSIC_MENU_CLICK");
		EApp::enterScene(new GameScene(), new ETransitionFade(0.3f, 0.3f));
	});
	startBtn->setPosX(EApp::getWidth() / 2);
	startBtn->setPosY(EApp::getHeight() - startBtnNormal->getHeight() - 100);
	this->add(startBtn);
	// 添加打开分享链接按钮
	auto shareBtnNormal = new ESprite(ResLoader::getImage(L"button_share"));
	auto shareBtnSelected = new ESprite(ResLoader::getImage(L"button_share"));
	shareBtnSelected->setPosY(5);
	auto shareBtn = new EButton(
		shareBtnNormal,
		shareBtnSelected,
		[] {
		// 按下按钮打开超链接
		ResLoader::playMusic(L"MUSIC_MENU_CLICK");
		ShellExecute(NULL, L"open", L"https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	shareBtn->setPosX(EApp::getWidth() / 2);
	shareBtn->setPosY(EApp::getHeight() - shareBtnNormal->getHeight() - 80);
	this->add(shareBtn);

	// 添加 copyright 图片
	auto copyright = new ESprite(ResLoader::getImage(L"brand_copyright"));
	copyright->setPosX(EApp::getWidth() / 2);
	copyright->setPosY(EApp::getHeight() - 20);
	this->add(copyright);
}

void StartScene::onEnter()
{
	// 进入场景时播放音效
	ResLoader::playMusic(L"MUSIC_SWOOSH");
}
