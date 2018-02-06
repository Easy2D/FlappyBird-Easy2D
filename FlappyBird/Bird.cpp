#include "Bird.h"
#include "ResLoader.h"


Bird::Bird()
{
	living = true;
	speed = 0;

	// ����֡������0.1 ���л�һ��
	animation = new EAnimation(0.1f);
	// ���С����ɫ
	int mode = ERandom::range(0, 2);
	// Ϊ��ͬ��ɫ��С����ز�ͬ��֡����
	if (mode == 0)
	{
		this->loadFrom(ResLoader::getImage(L"bird0_0"));
		animation->addKeyframe(ResLoader::getImage(L"bird0_0"));
		animation->addKeyframe(ResLoader::getImage(L"bird0_1"));
		animation->addKeyframe(ResLoader::getImage(L"bird0_2"));
		animation->addKeyframe(ResLoader::getImage(L"bird0_1"));
	}
	else if (mode == 1)
	{
		this->loadFrom(ResLoader::getImage(L"bird1_0"));
		animation->addKeyframe(ResLoader::getImage(L"bird1_0"));
		animation->addKeyframe(ResLoader::getImage(L"bird1_1"));
		animation->addKeyframe(ResLoader::getImage(L"bird1_2"));
		animation->addKeyframe(ResLoader::getImage(L"bird1_1"));
	}
	else
	{
		this->loadFrom(ResLoader::getImage(L"bird2_0"));
		animation->addKeyframe(ResLoader::getImage(L"bird2_0"));
		animation->addKeyframe(ResLoader::getImage(L"bird2_1"));
		animation->addKeyframe(ResLoader::getImage(L"bird2_2"));
		animation->addKeyframe(ResLoader::getImage(L"bird2_1"));
	}
	// ѭ������֡����
	this->runAction(new EActionLoop(animation));

	// ��ʼ�����趯��������΢΢������
	auto moveBy = new EActionMoveBy(0.4f, EVector2(0, 8));
	fly = new EActionLoop(new EActionTwo(moveBy, moveBy->reverse()));

	// ��ʼ����ת������С��׹��ʱ����̧ͷ�����ͷ��
	rotate = new EActionSequence(
		3,								// �� 3 ���������
		new EActionRotateTo(0.2f, -15),	// 0.2 ������ת�� -15 ��
		new EActionDelay(0.2f),			// �ȴ� 0.2 ��
		new EActionRotateTo(0.5f, 90)	// 0.5 ������ת�� 90 �ȣ�С��ͷ���£�
	);
	// ���������������ֹ�����Զ�����
	rotate->retain();

	// ���ó�ʼ��״̬Ϊ 1
	this->setStatus(1);

	// ΪС�������״
	// С��ˮ�ܡ�������������ֱ�����Ϊ 0x0001 0x0010 0x0100
	// С�����ײ��������Ϊˮ�ܺ͵�����������Ļ����㣬��С��������Ƿ�����ײ
	// ˮ�ܺ͵������ײ��������ΪС���������룬�����Ƕ�������С������ײ
	// ��ˮ�ܺ͵���֮�䲻�������ײ
	auto circle = new ECircle(this);
	circle->setCategoryBitmask(BIRD_BITMASK);
	circle->setCollisionBitmask(PIPE_BITMASK | GROUND_BITMASK);
	this->setShape(circle);
}

Bird::~Bird()
{
	// �ͷ����������Ķ���
	rotate->release();
}

void Bird::setStatus(int status)
{
	// С��һ���� 4 ��״̬
	// 0 ��ʾС�񲻶�
	// 1 ��ʾС�����¸���
	// 2 ��ʾ��Ϸ�տ�ʼʱ��С��ֹͣ����������ʼ��ת
	// 3 ��ʾС�����Ϸ�ʱ����̧ͷ�����ͷ
	switch (status)
	{
	case 0:
		this->stopAllActions(); break;
	case 1:
		this->runAction(fly); break;
	case 2:
		this->stopAction(fly);			// ֹͣ���»ζ�����
		animation->setInterval(0.05f);	// ����С���ȶ������ٶ�
		this->runAction(rotate);		// ��תС��
		break;
	case 3:
		this->runAction(rotate);		// ��תС��
		break;
	default:
		break;
	}
}
