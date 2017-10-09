#include "StartScene.h"
#include "ImageLoader.h"
#include "GameScene.h"
#include "Bird.h"
#include "Ground.h"
#include "GameOverLayer.h"

void StartScene::init()
{
	// 添加背景和地面
	this->add(ImageLoader::getImage(_T("bg_day")));
	this->add(new Ground());
	// 添加标题图片
	auto title = ImageLoader::getImage(_T("title"));
	title->setWindowCenterX();
	title->setY(150);
	this->add(title);
	// 添加小鸟
	auto bird = new Bird();
	bird->setWindowCenter();
	this->add(bird);
	// 添加开始按钮
	auto startBtn = new ImageButton(ImageLoader::getImage(_T("button_play")));
	startBtn->setWindowCenterX();
	startBtn->setY(App::getHeight() - startBtn->getHeight() - 120);
	// 按钮按下时，向下移动5像素
	startBtn->setSelectCallback([=] {
		startBtn->move(0, 5);
	});
	startBtn->setUnselectCallback([=] {
		startBtn->move(0, -5);
	});
	// 按下开始按钮，进入 GameScene
	startBtn->setClickedCallback([] {
		//MusicUtils::playMusic(_T("res/sound/MenuClick.mp3"));
		App::enterScene(new GameScene());
	});
	this->add(startBtn);
	// 添加打开分享链接按钮
	auto shareBtn = new ImageButton(ImageLoader::getImage(_T("button_share")));
	shareBtn->setWindowCenterX();
	shareBtn->setY(App::getHeight() - shareBtn->getHeight() - 80);
	// 按钮按下时，向下移动5像素
	shareBtn->setSelectCallback([=] {
		shareBtn->move(0, 5);
	});
	shareBtn->setUnselectCallback([=] {
		shareBtn->move(0, -5);
	});
	// 按下按钮打开超链接
	shareBtn->setClickedCallback([] {
		//MusicUtils::playMusic(_T("res/sound/MenuClick.mp3"));
		ShellExecute(NULL, _T("open"), _T("https://gitee.com/werelone/FlappyBird"), NULL, NULL, SW_SHOWNORMAL);
	});
	this->add(shareBtn);

	// 添加 copyright 图片
	auto copyright = ImageLoader::getImage(_T("brand_copyright"));
	copyright->setWindowCenterX();
	copyright->setY(App::getHeight() - 20);
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
