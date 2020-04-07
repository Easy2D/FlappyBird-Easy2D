#include "Pipe.h"
#include "ResLoader.h"


Pipe::Pipe()
{
	scored = false;

	// 随机水管高度
	// 范围：与屏幕顶部最小距离不小于 100 像素
	// 与屏幕底部最小距离不小于地面上方 100 像素
	float landHeight = ResLoader::getImage(L"land")->getHeight();
	float height = Random::range(100, Window::getHeight() - landHeight - 100);

	// 创建上水管
	auto pipe1 = gcnew Sprite(ResLoader::getImage(L"pipe_above"));
	pipe1->setAnchor(1, 1);
	pipe1->setPosY(height - 60);

	// 创建下水管
	auto pipe2 = gcnew Sprite(ResLoader::getImage(L"pipe_below"));
	pipe2->setAnchor(1, 0);
	pipe2->setPosY(height + 60);

	// 把上下水管添加为子成员
	this->addChild(pipe1);
	this->addChild(pipe2);
}


Pipe::~Pipe()
{
}
