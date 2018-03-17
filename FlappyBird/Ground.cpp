#include "Ground.h"
#include "ResLoader.h"


Ground::Ground()
{
	// �ƶ������ʵ�ַ�����
	// ��Ҫ������棬һ���������Ļ�ڣ���һ������ŷ��������ұߣ���Ļ�⣩
	// ����ͬʱ�����ƶ�������һ����ȫ�Ƴ���Ļʱ�������ŵ��ڶ�����ұ�
	// �ڶ�����ȫ�Ƴ���Ļʱ���ٽ����ŵ���һ���ұ�
	// �������У����濴��ȥ����һֱ���ƶ���

	// ������һ�����
	ground1 = new Sprite(ResLoader::getImage("land"));
	// ����ê�����������½�
	ground1->setPivot(0, 1);
	// �����������Ļ�ײ�
	ground1->setPos(0, Window::getHeight());
	this->addChild(ground1);

	// ���õ�����״
	// ����������ײ���������ԭ��ο� Bird.cpp
	auto rt1 = new Rect(ground1);
	rt1->setCategoryBitmask(GROUND_BITMASK);// �����������
	rt1->setCollisionBitmask(BIRD_BITMASK);	// ������ײ����
	ground1->setShape(rt1);					// ������״

	// �����ڶ������
	ground2 = new Sprite(ResLoader::getImage("land"));
	ground2->setPivot(0, 1);
	ground2->setPos(ground1->getWidth(), Window::getHeight());
	this->addChild(ground2);

	// ���õ�����״
	auto rt2 = new Rect(ground2);
	rt2->setCategoryBitmask(GROUND_BITMASK);
	rt2->setCollisionBitmask(BIRD_BITMASK);
	ground2->setShape(rt2);
}

void Ground::onUpdate()
{
	// �ѵ��������ƶ� 2 ����
	ground1->movePos(-2, 0);
	ground2->movePos(-2, 0);
	// ������ȫ�Ƴ���Ļʱ�����õ���λ��
	if (ground1->getPosX() <= -ground1->getWidth()) {
		ground1->setPosX(ground1->getWidth() - 1);
	}
	if (ground2->getPosX() <= -ground2->getWidth()) {
		ground2->setPosX(ground2->getWidth() - 1);
	}
}

void Ground::stop()
{
	// �ر� onUpdate ����
	this->setAutoUpdate(false);
}
