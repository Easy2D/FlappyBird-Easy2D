#pragma once
#include <easy2d.h>

// ������
// ��Ϸ�����·�һֱ�����ƶ��ĵ���
class Ground :
	public Node
{
public:
	Ground();

	void onUpdate() override;
	void stop();

public:
	Sprite * ground1;	// ��һ�����
	Sprite * ground2;	// �ڶ������
};

