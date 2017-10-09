#include "StartScene.h"
#include "ImageLoader.h"
#include "GameScene.h"
#include "Bird.h"
#include "Ground.h"
#include "GameOverLayer.h"

void StartScene::init()
{
	// ��ӱ����͵���
	this->add(ImageLoader::getImage(_T("bg_day")));
	this->add(new Ground());
	// ��ӱ���ͼƬ
	auto title = ImageLoader::getImage(_T("title"));
	title->setWindowCenterX();
	title->setY(150);
	this->add(title);
	// ���С��
	auto bird = new Bird();
	bird->setWindowCenter();
	this->add(bird);
	// ��ӿ�ʼ��ť
	auto startBtn = new ImageButton(ImageLoader::getImage(_T("button_play")));
	startBtn->setWindowCenterX();
	startBtn->setY(App::getHeight() - startBtn->getHeight() - 120);
	// ��ť����ʱ�������ƶ�5����
	startBtn->setSelectCallback([=] {
		startBtn->move(0, 5);
	});
	startBtn->setUnselectCallback([=] {
		startBtn->move(0, -5);
	});
	// ���¿�ʼ��ť������ GameScene
	startBtn->setClickedCallback([] {
		//MusicUtils::playMusic(_T("res/sound/MenuClick.mp3"));
		App::enterScene(new GameScene());
	});
	this->add(startBtn);
	// ��Ӵ򿪷������Ӱ�ť
	auto shareBtn = new ImageButton(ImageLoader::getImage(_T("button_share")));
	shareBtn->setWindowCenterX();
	shareBtn->setY(App::getHeight() - shareBtn->getHeight() - 80);
	// ��ť����ʱ�������ƶ�5����
	shareBtn->setSelectCallback([=] {
		shareBtn->move(0, 5);
	});
	shareBtn->setUnselectCallback([=] {
		shareBtn->move(0, -5);
	});
	// ���°�ť�򿪳�����
	shareBtn->setClickedCallback([] {
		//MusicUtils::playMusic(_T("res/sound/MenuClick.mp3"));
		ShellExecute(NULL, _T("open"), _T("https://gitee.com/werelone/FlappyBird"), NULL, NULL, SW_SHOWNORMAL);
	});
	this->add(shareBtn);

	// ��� copyright ͼƬ
	auto copyright = ImageLoader::getImage(_T("brand_copyright"));
	copyright->setWindowCenterX();
	copyright->setY(App::getHeight() - 20);
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
