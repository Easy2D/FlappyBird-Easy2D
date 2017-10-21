#include "Ground.h"
#include "ImageLoader.h"


Ground::Ground()
{
	auto ground1 = new ESprite(ImageLoader::getImage(L"land"));
	// ����ê�����������½�
	ground1->setAnchor(0, 1);
	// �����������Ļ�ײ�
	ground1->setPos(0, EApp::getHeight());
	this->addChild(ground1);

	// ����һ����ͬ�ĵ��棬���ڿ���ѭ���˶�
	auto ground2 = new ESprite(ImageLoader::getImage(L"land"));
	ground2->setAnchor(0, 1);
	ground2->setPos(ground1->getWidth(), EApp::getHeight());
	this->addChild(ground2);

	// ������ʱ�����ƶ�����
	auto timer = new ETimer([=](int) {
		// �ƶ�����
		ground1->move(-2, 0);
		ground2->move(-2, 0);
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
