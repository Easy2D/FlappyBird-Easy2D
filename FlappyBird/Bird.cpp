#include "Bird.h"
#include "ResLoader.h"


Bird::Bird()
{
	animation = new EAnimation(100);
	this->runAction(new EActionLoop(animation));

	// 随机小鸟颜色
	int mode = ERandom::between(0, 2);
	// 为不同的小鸟加载不同的帧动画
	if (mode == 0)
	{
		this->loadFrom(ResLoader::getImage(L"bird0_0"));
		animation->addFrame(ResLoader::getImage(L"bird0_0"));
		animation->addFrame(ResLoader::getImage(L"bird0_1"));
		animation->addFrame(ResLoader::getImage(L"bird0_2"));
		animation->addFrame(ResLoader::getImage(L"bird0_1"));
	}
	else if (mode == 1)
	{
		this->loadFrom(ResLoader::getImage(L"bird1_0"));
		animation->addFrame(ResLoader::getImage(L"bird1_0"));
		animation->addFrame(ResLoader::getImage(L"bird1_1"));
		animation->addFrame(ResLoader::getImage(L"bird1_2"));
		animation->addFrame(ResLoader::getImage(L"bird1_1"));
	}
	else
	{
		this->loadFrom(ResLoader::getImage(L"bird2_0"));
		animation->addFrame(ResLoader::getImage(L"bird2_0"));
		animation->addFrame(ResLoader::getImage(L"bird2_1"));
		animation->addFrame(ResLoader::getImage(L"bird2_2"));
		animation->addFrame(ResLoader::getImage(L"bird2_1"));
	}

	// 初始化飞翔动画
	auto moveBy = new EActionMoveBy(0.4f, EVec(0, 8));
	fly = new EActionLoop(new EActionTwo(moveBy, moveBy->reverse()));

	// 初始化旋转动画
	rotate = new EActionSequence(3, new EActionRotateTo(0.2f, -15), new EActionDelay(0.2f), new EActionRotateTo(0.5f, 90));
	// 保留这个动画，防止引擎自动释放
	rotate->retain();

	// 设置初始化状态为 1
	this->setStatus(1);

	// 为小鸟添加物理圆形
	// 小鸟、地面、水管的类别掩码分别为 0x0001 0x0010 0x0100
	// 设置小鸟接触掩码为 0x0110，所以它会和地面水管产生接触消息
	// 设置地面和水管的接触掩码为 0x0001，所以它们和小鸟也会产生接触消息
	auto circle = new ECircle(EPoint(this->getRealWidth() / 2, this->getRealWidth() / 2), this->getRealWidth() / 2);
	circle->setCategoryBitmask(0x0001);
	circle->setCollisionBitmask(0x0110);
	this->setGeometry(circle);
}

Bird::~Bird()
{
	// 让引擎释放曾保留的动画
	rotate->release();
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
