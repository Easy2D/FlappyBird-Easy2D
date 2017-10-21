#include "Bird.h"
#include "ImageLoader.h"


Bird::Bird()
{
	animation = new EAnimation(100);
	this->runAction(new EActionLoop(animation));

	// ���С����ɫ
	int mode = ERandom::between(0, 2);
	// Ϊ��ͬ��С����ز�ͬ��֡����
	if (mode == 0)
	{
		this->loadFrom(ImageLoader::getImage(L"bird0_0"));
		animation->addFrame(ImageLoader::getImage(L"bird0_0"));
		animation->addFrame(ImageLoader::getImage(L"bird0_1"));
		animation->addFrame(ImageLoader::getImage(L"bird0_2"));
		animation->addFrame(ImageLoader::getImage(L"bird0_1"));
	}
	else if (mode == 1)
	{
		this->loadFrom(ImageLoader::getImage(L"bird1_0"));
		animation->addFrame(ImageLoader::getImage(L"bird1_0"));
		animation->addFrame(ImageLoader::getImage(L"bird1_1"));
		animation->addFrame(ImageLoader::getImage(L"bird1_2"));
		animation->addFrame(ImageLoader::getImage(L"bird1_1"));
	}
	else
	{
		this->loadFrom(ImageLoader::getImage(L"bird2_0"));
		animation->addFrame(ImageLoader::getImage(L"bird2_0"));
		animation->addFrame(ImageLoader::getImage(L"bird2_1"));
		animation->addFrame(ImageLoader::getImage(L"bird2_2"));
		animation->addFrame(ImageLoader::getImage(L"bird2_1"));
	}

	// ��ʼ�����趯��
	auto moveBy = new EActionMoveBy(0.4f, EVec(0, 8));
	fly = new EActionLoop(new EActionTwo(moveBy, moveBy->reverse()));

	// ��ʼ����ת����
	rotate = new EActionSequence(3, new EActionRotateTo(0.2f, -15), new EActionDelay(0.2f), new EActionRotateTo(0.5f, 90));

	this->setStatus(1);
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
