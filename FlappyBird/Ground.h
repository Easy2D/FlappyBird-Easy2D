#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

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

