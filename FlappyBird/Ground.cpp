#include "Ground.h"
#include "ImageLoader.h"


Ground::Ground()
{
	auto ground1 = new ESprite(ImageLoader::getImage(L"land"));
	// 地面锚点设置在左下角
	ground1->setAnchor(0, 1);
	// 将地面放在屏幕底部
	ground1->setPos(0, EApp::getHeight());
	this->addChild(ground1);

	// 创建一块相同的地面，用于控制循环运动
	auto ground2 = new ESprite(ImageLoader::getImage(L"land"));
	ground2->setAnchor(0, 1);
	ground2->setPos(ground1->getWidth(), EApp::getHeight());
	this->addChild(ground2);

	// 创建定时器，移动地面
	auto timer = new ETimer([=](int) {
		// 移动地面
		ground1->move(-2, 0);
		ground2->move(-2, 0);
		// 地面出界时重置地面位置
		if (ground1->getPosX() <= -ground1->getWidth()) {
			ground1->setPosX(ground1->getWidth() - 1);
		}
		if (ground2->getPosX() <= -ground2->getWidth()) {
			ground2->setPosX(ground2->getWidth() - 1);
		}
	});
	// 将定时器绑定在节点上
	timer->bindWith(this);
}


Ground::~Ground()
{
}

void Ground::stop()
{
	ETimerManager::stopAllTimersBindedWith(this);
}
