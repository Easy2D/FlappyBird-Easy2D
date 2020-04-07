#include "Ground.h"
#include "ResLoader.h"


Ground::Ground()
{
	// 移动地面的实现方法：
	// 需要两块地面，一块放置在屏幕内，另一块紧挨着放在它的右边（屏幕外）
	// 两块同时向左移动，当第一块完全移出屏幕时，将它放到第二块的右边
	// 第二块完全移出屏幕时，再将它放到第一块右边
	// 交替运行，地面看上去就像一直在移动了

	// 创建第一块地面
	ground1 = gcnew Sprite(ResLoader::getImage(L"land"));
	// 地面锚点设置在左下角
	ground1->setAnchor(0, 1);
	// 将地面放在屏幕底部
	ground1->setPos(0, Window::getHeight());
	this->addChild(ground1);

	// 创建第二块地面
	ground2 = gcnew Sprite(ResLoader::getImage(L"land"));
	ground2->setAnchor(0, 1);
	ground2->setPos(ground1->getWidth(), Window::getHeight());
	this->addChild(ground2);
}

void Ground::onUpdate()
{
	// 把地面向左移动 2 像素
	ground1->movePos(-2, 0);
	ground2->movePos(-2, 0);
	// 地面完全移出屏幕时，重置地面位置
	if (ground1->getPosX() <= -ground1->getWidth())
	{
		ground1->setPosX(ground1->getWidth() - 1);
	}
	if (ground2->getPosX() <= -ground2->getWidth())
	{
		ground2->setPosX(ground2->getWidth() - 1);
	}
}

void Ground::stop()
{
	// 关闭 onUpdate 函数
	this->setAutoUpdate(false);
}
