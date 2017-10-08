#include "StartScene.h"
#include "ImageLoader.h"
#include "GameScene.h"
#include "Bird.h"

void StartScene::init()
{
	this->add(ImageLoader::getImage(_T("bg_day")));

	auto title = ImageLoader::getImage(_T("title"));
	title->setWindowCenterX();
	title->setY(150);
	this->add(title);

	auto bird = new Bird();
	bird->setWindowCenter();
	this->add(bird);

	auto startBtn = new ImageButton(ImageLoader::getImage(_T("button_play")));
	startBtn->setWindowCenterX();
	startBtn->setY(App::getHeight() - startBtn->getHeight() - 90);
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
