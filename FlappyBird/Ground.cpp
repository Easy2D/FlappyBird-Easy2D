#include "Ground.h"
#include "ResLoader.h"


Ground::Ground()
{
	auto ground1 = new ESprite(ResLoader::getImage(L"land"));
	// ����ê�����������½�
	ground1->setPivot(0, 1);
	// �����������Ļ�ײ�
	ground1->setPos(0, EApp::getHeight());
	this->addChild(ground1);
	// Ϊ��������������
	auto rt1 = new ERectangle(ground1);
	rt1->setCategoryBitmask(0x0010);
	rt1->setCollisionBitmask(0x0001);
	ground1->setGeometry(rt1);
	// ����һ����ͬ�ĵ��棬���ڿ���ѭ���˶�
	auto ground2 = new ESprite(ResLoader::getImage(L"land"));
	ground2->setPivot(0, 1);
	// �����������Ļ�ײ�
	ground2->setPos(ground1->getWidth(), EApp::getHeight());
	this->addChild(ground2);
	// Ϊ��������������
	auto rt2 = new ERectangle(ground2);
	rt2->setCategoryBitmask(0x0010);
	rt2->setCollisionBitmask(0x0001);
	ground2->setGeometry(rt2);

	// ������ʱ�����ƶ�����
	auto timer = new ETimer([=](int) {
		// �ƶ�����
		ground1->movePos(-2, 0);
		ground2->movePos(-2, 0);
		// �������ʱ���õ���λ��
		if (ground1->getPosX() <= -ground1->getWidth()) {
			ground1->setPosX(ground1->getWidth() - 1);
		}
		if (ground2->getPosX() <= -ground2->getWidth()) {
			ground2->setPosX(ground2->getWidth() - 1);
		}
	});
	// ����ʱ�����ڽڵ���
	timer->bindWith(this);
}


Ground::~Ground()
{
}

void Ground::stop()
{
	ETimerManager::stopAllTimersBindedWith(this);
}
