#include "Bird.h"
#include "ResLoader.h"

namespace
{
	float gravity = 1440.f;	// 重力每秒加速度
	float jumpSpeed = 432.f;	// 小鸟跳跃获得的初速度
}

Bird::Bird()
{
	living = true;
	speed = 0;

	// 创建帧动画，0.1f 秒切换一次
	frames = gcnew FrameSequence(0.1f);
	// 随机小鸟颜色
	int mode = Random::range(0, 2);
	// 为不同颜色的小鸟加载不同的帧动画
	if (mode == 0)
	{
		frames->add(ResLoader::getKeyFrame("bird0_0"));
		frames->add(ResLoader::getKeyFrame("bird0_1"));
		frames->add(ResLoader::getKeyFrame("bird0_2"));
		frames->add(ResLoader::getKeyFrame("bird0_1"));
	}
	else if (mode == 1)
	{
		frames->add(ResLoader::getKeyFrame("bird1_0"));
		frames->add(ResLoader::getKeyFrame("bird1_1"));
		frames->add(ResLoader::getKeyFrame("bird1_2"));
		frames->add(ResLoader::getKeyFrame("bird1_1"));
	}
	else
	{
		frames->add(ResLoader::getKeyFrame("bird2_0"));
		frames->add(ResLoader::getKeyFrame("bird2_1"));
		frames->add(ResLoader::getKeyFrame("bird2_2"));
		frames->add(ResLoader::getKeyFrame("bird2_1"));
	}
	// 循环运行帧动画
	this->runAction(gcnew Loop(gcnew Animation(frames)));

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
	this->setStatus(Status::Idle);
}

Bird::~Bird()
{
	// 释放曾经保留的动画
	rotate->release();
}

void Bird::fall()
{
	movePosY(Time::getDeltaTime() * speed);
	// 模拟小鸟所受重力
	speed += Time::getDeltaTime() * gravity;
	// 若小鸟纵坐标小于 0，限制它继续往上飞
	if (getPosY() < 0)
	{
		setPosY(0);
		speed = 0;
	}
}

void Bird::jump()
{
	if (living)
	{
		// 如果小鸟还活着，给小鸟一个向上的速度
		speed = -jumpSpeed;
		// 设置小鸟状态
		setStatus(Bird::Status::Fly);
		// 播放音效
		ResLoader::playMusic(MusicType::Fly);
	}
}

void Bird::die()
{
	living = false;
	// 播放音效
	ResLoader::playMusic(MusicType::Hit);
}

void Bird::setStatus(Status status)
{
	switch (status)
	{
	case Status::Still:
	{
		this->stopAllActions();
		break;
	}
	case Status::Idle:
	{
		this->runAction(fly);
		break;
	}
	case Status::StartToFly:
	{
		fly->stop();						// 停止上下晃动动画
		frames->setInterval(0.5f);			// 加速小鸟扇动翅膀的速度
		// break;
	}
	case Status::Fly:
	{
		this->stopAction("rotate");		// 停止前一个旋转动作

		auto newRotate = rotate->clone();
		newRotate->setName("rotate");
		this->runAction(newRotate);
		break;
	}
	default:
		break;
	}
}
