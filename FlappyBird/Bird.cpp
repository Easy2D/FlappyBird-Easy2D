#include "Bird.h"
#include "ResLoader.h"


Bird::Bird()
{
	animation = new EAnimation(100);
	this->runAction(new EActionLoop(animation));

	// ���С����ɫ
	int mode = ERandom::between(0, 2);
	// Ϊ��ͬ��С����ز�ͬ��֡����
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

	// ��ʼ�����趯��
	auto moveBy = new EActionMoveBy(0.4f, EVec(0, 8));
	fly = new EActionLoop(new EActionTwo(moveBy, moveBy->reverse()));

	// ��ʼ����ת����
	rotate = new EActionSequence(3, new EActionRotateTo(0.2f, -15), new EActionDelay(0.2f), new EActionRotateTo(0.5f, 90));
	// ���������������ֹ�����Զ��ͷ�
	rotate->retain();

	// ���ó�ʼ��״̬Ϊ 1
	this->setStatus(1);

	// ΪС���������Բ��
	// С�񡢵��桢ˮ�ܵ��������ֱ�Ϊ 0x0001 0x0010 0x0100
	// ����С��Ӵ�����Ϊ 0x0110����������͵���ˮ�ܲ����Ӵ���Ϣ
	// ���õ����ˮ�ܵĽӴ�����Ϊ 0x0001���������Ǻ�С��Ҳ������Ӵ���Ϣ
	auto circle = new ECircle(EPoint(this->getRealWidth() / 2, this->getRealWidth() / 2), this->getRealWidth() / 2);
	circle->setCategoryBitmask(0x0001);
	circle->setCollisionBitmask(0x0110);
	this->setGeometry(circle);
}

Bird::~Bird()
{
	// �������ͷ��������Ķ���
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
		this->stopAction(fly);		// ֹͣ���»ζ�����
		animation->setInterval(50);	// ����С���ȶ������ٶ�
		temp = rotate->clone();		// ����һ����ת�����Ŀ���
		this->runAction(temp);		// ��תС��
		break;
	case 3:
		this->stopAction(temp);		// ֹͣ��ǰ����ת����
		temp = rotate->clone();		// ����һ����ת�����Ŀ���
		this->runAction(temp);		// ��תС��
		break;
	default:
		break;
	}
}
