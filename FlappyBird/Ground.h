#pragma once
#include <easy2d.h>

// ������
// ��Ϸ�����·�һֱ�����ƶ��ĵ���
class Ground :
	public ENode
{
public:
	Ground();

	void onUpdate() override;
	void stop();

public:
	ESprite * ground1;	// ��һ�����
	ESprite * ground2;	// �ڶ������
};

