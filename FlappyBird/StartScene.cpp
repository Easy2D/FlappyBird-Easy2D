#include "StartScene.h"
#include "ImageLoader.h"
#include "GameScene.h"
#include "Bird.h"
#include "Ground.h"
#include "GameOverLayer.h"
#include <shellapi.h>

StartScene::StartScene()
{
	// 添加背景
	auto background = new ESprite(ImageLoader::getImage(L"bg_day"));
	// 设置背景锚点为左上角
	background->setAnchor(0, 0);
	this->add(background);
	// 添加地面
	this->add(new Ground());
	// 添加标题图片
	auto title = new ESprite(ImageLoader::getImage(L"title"));
	title->setPos(EApp::getWidth() / 2, 150);
	this->add(title);
	// 添加小鸟
	auto bird = new Bird();
	bird->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2);
	this->add(bird);
	// 创建开始按钮正常状态和按下状态时显示的精灵
	auto startBtnNormal = new ESprite(ImageLoader::getImage(L"button_play"));
	auto startBtnSelected = new ESprite(ImageLoader::getImage(L"button_play"));
	startBtnSelected->setPosY(5);	// 按钮被选中时向下移动一点点
	// 添加开始按钮
	auto startBtn = new EButton(
		startBtnNormal,
		startBtnSelected,
		[] {
		// 按下开始按钮，进入 Game 场景
		EApp::enterScene(new GameScene(), new ETransitionFade(0.3f, 0.3f));
	});
	startBtn->setPosX(EApp::getWidth() / 2);
	startBtn->setPosY(EApp::getHeight() - startBtnNormal->getHeight() - 100);
	this->add(startBtn);
	// 添加打开分享链接按钮
	auto shareBtnNormal = new ESprite(ImageLoader::getImage(L"button_share"));
	auto shareBtnSelected = new ESprite(ImageLoader::getImage(L"button_share"));
	shareBtnSelected->setPosY(5);
	auto shareBtn = new EButton(
		shareBtnNormal,
		shareBtnSelected,
		[] {
		// 按下按钮打开超链接
		//MusicUtils::playMusic(_T("res/sound/MenuClick.mp3"));
		ShellExecute(NULL, L"open", L"https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	shareBtn->setPosX(EApp::getWidth() / 2);
	shareBtn->setPosY(EApp::getHeight() - shareBtnNormal->getHeight() - 80);
	this->add(shareBtn);

	// 添加 copyright 图片
	auto copyright = new ESprite(ImageLoader::getImage(L"brand_copyright"));
	copyright->setPosX(EApp::getWidth() / 2);
	copyright->setPosY(EApp::getHeight() - 20);
	this->add(copyright);

	// 预加载音效
	/*MusicUtils::preloadMusic(_T("res/sound/fly.mp3"));
	MusicUtils::preloadMusic(_T("res/sound/hit.mp3"));
	MusicUtils::preloadMusic(_T("res/sound/point.mp3"));
	MusicUtils::preloadMusic(_T("res/sound/swoosh.mp3"));
	MusicUtils::preloadMusic(_T("res/sound/MenuClick.mp3"));*/
}

void StartScene::onEnter()
{
	// 进入场景时播放音效
	//MusicUtils::playMusic(_T("res/sound/swoosh.mp3"));
}
