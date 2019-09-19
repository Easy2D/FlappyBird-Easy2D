#include "Bird.h"
#include "ResLoader.h"


Bird::Bird()
{
	living = true;
	speed = 0;

	// 创建帧动画，0.1f 秒切换一次
	animation = gcnew Animation(0.1f);
	// 随机小鸟颜色
	int mode = Random::range(0, 2);
	// 为不同颜色的小鸟加载不同的帧动画
	if (mode == 0)
	{
		this->open(ResLoader::getImage(L"bird0_0"));
		animation->add(ResLoader::getImage(L"bird0_0"));
		animation->add(ResLoader::getImage(L"bird0_1"));
		animation->add(ResLoader::getImage(L"bird0_2"));
		animation->add(ResLoader::getImage(L"bird0_1"));
	}
	else if (mode == 1)
	{
		this->open(ResLoader::getImage(L"bird1_0"));
		animation->add(ResLoader::getImage(L"bird1_0"));
		animation->add(ResLoader::getImage(L"bird1_1"));
		animation->add(ResLoader::getImage(L"bird1_2"));
		animation->add(ResLoader::getImage(L"bird1_1"));
	}
	else
	{
		this->open(ResLoader::getImage(L"bird2_0"));
		animation->add(ResLoader::getImage(L"bird2_0"));
		animation->add(ResLoader::getImage(L"bird2_1"));
		animation->add(ResLoader::getImage(L"bird2_2"));
		animation->add(ResLoader::getImage(L"bird2_1"));
	}
	// 循环运行帧动画
	this->runAction(gcnew Loop(gcnew Animate(animation)));

	// 初始化飞翔动画（上下微微浮动）
	auto moveBy = gcnew MoveBy(0.4f, Vector2(0, 8));
	fly = gcnew Loop(gcnew Sequence({ moveBy, moveBy->reverse() }));

	// 初始化旋转动画（小鸟坠落时，先抬头，后低头）
	rotate = gcnew Sequence({
		gcnew RotateTo(0.2f, -15),	// 0.2f 秒内旋转至 -15 度
		gcnew Delay(0.2f),			// 等待 0.2f 秒
		gcnew RotateTo(0.5f, 90)	// 0.5f 秒内旋转至 90 度（小鸟头朝下）
	});
	// 保留这个动画，防止引擎自动回收
	rotate->retain();

	// 设置初始化状态为 1
	this->setStatus(1);
}

Bird::~Bird()
{
	// 释放曾经保留的动画
	rotate->release();
}

void Bird::setStatus(int status)
{
	// 小鸟一共有 4 种状态
	// 0 表示小鸟不动
	// 1 表示小鸟上下浮动
	// 2 表示游戏刚开始时，小鸟停止浮动，并开始旋转
	// 3 表示小鸟向上飞时，先抬头，后低头
	switch (status)
	{
	case 0:
		this->stopAllActions(); break;
	case 1:
		this->runAction(fly); break;
	case 2:
	{
		fly->stop();						// 停止上下晃动动画
		animation->setInterval(0.5f);		// 加速小鸟扇动翅膀的速度

		// break;
	}
	case 3:
	{
		this->stopAction(L"rotate");		// 停止前一个旋转动作

		auto newRotate = rotate->clone();
		newRotate->setName(L"rotate");
		this->runAction(newRotate);
		break;
	}
	default:
		break;
	}
}
