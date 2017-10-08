#include "StartScene.h"
#include "ImageLoader.h"
#include "GameScene.h"
#include "Bird.h"
#include "Ground.h"

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
	// ��ť����ʱ
	startBtn->setSelectCallback([=] {
		startBtn->move(0, 5);
	});
	startBtn->setUnselectCallback([=] {
		startBtn->move(0, -5);
	});
	startBtn->setClickedCallback([] {
		App::enterScene(new GameScene());
	});
	this->add(startBtn);

	auto copyright = ImageLoader::getImage(_T("brand_copyright"));
	copyright->setWindowCenterX();
	copyright->setY(App::getHeight() - 20);
	this->add(copyright);
}
