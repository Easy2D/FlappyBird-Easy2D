#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

// С����
class Bird :
	public Sprite
{
public:
	Bird();

	~Bird();

	// С��״̬
	enum class Status
	{
		Still,		// С�񲻶�
		Idle,		// С�����¸���
		StartToFly,	// ��Ϸ�տ�ʼʱ��С��ֹͣ����������ʼ��ת
		Fly,		// С�����Ϸ�ʱ����̧ͷ�����ͷ
	};

	// ����С��״̬
	void setStatus(Status status);

public:
	bool living;
	float speed;
	Action* fly;
	Animation* animation;
	Action* rotate;
};
