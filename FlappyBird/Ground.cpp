#include "Ground.h"
#include "ImageLoader.h"


Ground::Ground()
{
	auto ground1 = new Sprite(ImageLoader::getImage(_T("land")));
	ground1->setPos(0, App::getHeight() - ground1->getHeight());
	this->addSprite(ground1);

	auto ground2 = new Sprite(ImageLoader::getImage(_T("land")));
	ground2->setPos(ground1->getWidth(), App::getHeight() - ground2->getHeight());
	this->addSprite(ground2);

	Timer::addTimer(_T("ground_move"), [=] {
		// 移动地面
		ground1->move(-2, 0);
		ground2->move(-2, 0);
		// 地面出界时重置地面位置
		if (ground1->getX() <= -ground1->getWidth()) {
			ground1->setX(ground1->getWidth());
		}
		if (ground2->getX() <= -ground2->getWidth()) {
			ground2->setX(ground2->getWidth());
		}
	});
}


Ground::~Ground()
{
}

void Ground::stop()
{
	Timer::stopTimer(_T("ground_move"));
}
