#include "Bird.h"
#include "ImageLoader.h"


Bird::Bird()
{
	animation = new EAnimation(100);
	this->runAction(new EActionLoop(animation));

	// 随机小鸟颜色
	int mode = ERandom::between(0, 2);
	// 为不同的小鸟加载不同的帧动画
	if (mode == 0)
	{
		this->loadFrom(ImageLoader::getImage(L"bird0_0"));
		animation->addFrame(ImageLoader::getImage(L"bird0_0"));
		animation->addFrame(ImageLoader::getImage(L"bird0_1"));
		animation->addFrame(ImageLoader::getImage(L"bird0_2"));
		animation->addFrame(ImageLoader::getImage(L"bird0_1"));
	}
	else if (mode == 1)
	{
		this->loadFrom(ImageLoader::getImage(L"bird1_0"));
		animation->addFrame(ImageLoader::getImage(L"bird1_0"));
		animation->addFrame(ImageLoader::getImage(L"bird1_1"));
		animation->addFrame(ImageLoader::getImage(L"bird1_2"));
		animation->addFrame(ImageLoader::getImage(L"bird1_1"));
	}
	else
	{
		this->loadFrom(ImageLoader::getImage(L"bird2_0"));
		animation->addFrame(ImageLoader::getImage(L"bird2_0"));
		animation->addFrame(ImageLoader::getImage(L"bird2_1"));
		animation->addFrame(ImageLoader::getImage(L"bird2_2"));
		animation->addFrame(ImageLoader::getImage(L"bird2_1"));
	}

	// 初始化飞翔动画
	auto moveBy = new EActionMoveBy(0.4f, EVec(0, 8));
	fly = new EActionLoop(new EActionTwo(moveBy, moveBy->reverse()));

	// 初始化旋转动画
	rotate = new EActionSequence(3, new EActionRotateTo(0.2f, -15), new EActionDelay(0.2f), new EActionRotateTo(0.5f, 90));

	this->setStatus(1);
}

void Bird::setStatus(int status)
{
	switch (status)
	{
	case 0:
		this->stopAllActions(); break;
	case 1:
		this->runAction(fly); break;
	case 2:
		this->stopAction(fly);		// 停止上下晃动动画
		animation->setInterval(50);	// 加速小鸟扇动翅膀的速度
		temp = rotate->clone();		// 创建一个旋转动画的拷贝
		this->runAction(temp);		// 旋转小鸟
		break;
	case 3:
		this->stopAction(temp);		// 停止当前的旋转动作
		temp = rotate->clone();		// 创建一个旋转动画的拷贝
		this->runAction(temp);		// 旋转小鸟
		break;
	default:
		break;
	}
}
