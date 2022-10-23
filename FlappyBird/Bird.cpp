#include "Bird.h"
#include "ResLoader.h"

namespace
{
	float gravity = 1440.f;	// ����ÿ����ٶ�
	float jumpSpeed = 432.f;	// С����Ծ��õĳ��ٶ�
}

Bird::Bird()
{
	living = true;
	speed = 0;

	// ����֡������0.1f ���л�һ��
	frames = gcnew FrameSequence(0.1f);
	// ���С����ɫ
	int mode = Random::range(0, 2);
	// Ϊ��ͬ��ɫ��С����ز�ͬ��֡����
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
	// ѭ������֡����
	this->runAction(gcnew Loop(gcnew Animation(frames)));

	// ��ʼ�����趯��������΢΢������
	auto moveBy = gcnew MoveBy(0.4f, Vector2(0, 8));
	fly = gcnew Loop(gcnew Sequence({ moveBy, moveBy->reverse() }));

	// ��ʼ����ת������С��׹��ʱ����̧ͷ�����ͷ��
	rotate = gcnew Sequence({
		gcnew RotateTo(0.2f, -15),	// 0.2f ������ת�� -15 ��
		gcnew Delay(0.2f),			// �ȴ� 0.2f ��
		gcnew RotateTo(0.5f, 90)	// 0.5f ������ת�� 90 �ȣ�С��ͷ���£�
		});
	// ���������������ֹ�����Զ�����
	rotate->retain();

	// ���ó�ʼ��״̬Ϊ 1
	this->setStatus(Status::Idle);
}

Bird::~Bird()
{
	// �ͷ����������Ķ���
	rotate->release();
}

void Bird::fall()
{
	movePosY(Time::getDeltaTime() * speed);
	// ģ��С����������
	speed += Time::getDeltaTime() * gravity;
	// ��С��������С�� 0���������������Ϸ�
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
		// ���С�񻹻��ţ���С��һ�����ϵ��ٶ�
		speed = -jumpSpeed;
		// ����С��״̬
		setStatus(Bird::Status::Fly);
		// ������Ч
		ResLoader::playMusic(MusicType::Fly);
	}
}

void Bird::die()
{
	living = false;
	// ������Ч
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
		fly->stop();						// ֹͣ���»ζ�����
		frames->setInterval(0.5f);			// ����С���ȶ������ٶ�
		// break;
	}
	case Status::Fly:
	{
		this->stopAction("rotate");		// ֹͣǰһ����ת����

		auto newRotate = rotate->clone();
		newRotate->setName("rotate");
		this->runAction(newRotate);
		break;
	}
	default:
		break;
	}
}
