#include "Number.h"
#include "ResLoader.h"

Number::Number()
{
	number = 0;
}

int Number::getNumber()
{
	return number;
}

void Number::setNumber(int number)
{
	this->number = number;
	this->removeAllChildren();

	// ���ָ߶�
	float height = ResLoader::getKeyFrame("number_big_0")->getHeight();
	// �����ܿ��
	float totalWidth = 0;
	// Ϊ���ֵ�ÿһλ�����ӦͼƬ
	// ������ 0 ����������
	if (number == 0)
	{
		auto zero = gcnew Sprite(ResLoader::getKeyFrame("number_big_0"));
		totalWidth = zero->getWidth();
		this->addChild(zero);
	}
	else
	{
		while (number)
		{
			// ����ÿһλ�ϵ�����
			int temp = number % 10;
			number /= 10;
			// �������
			auto sprite = gcnew Sprite(ResLoader::getKeyFrame("number_big_" + std::to_string(temp)));
			totalWidth += sprite->getWidth();
			this->addChild(sprite);
		}
	}

	// �����ܿ��
	float temp = totalWidth / 2;
	// ����ͼƬλ��
	for (auto child : this->getAllChildren())
	{
		child->setAnchor(0, 0);
		temp -= child->getWidth();
		child->setPos(temp, 0);
	}
}

void Number::setLittleNumber(int number)
{
	this->number = number;
	this->removeAllChildren();

	// ���ָ߶�
	float height = ResLoader::getKeyFrame("number_medium_0")->getHeight();
	// Ϊ���ֵ�ÿһλ�����ӦͼƬ
	// ������ 0 ����������
	if (number == 0)
	{
		auto zero = gcnew Sprite(ResLoader::getKeyFrame("number_medium_0"));
		this->addChild(zero);
	}
	else
	{
		while (number)
		{
			// ����ÿһλ�ϵ�����
			int temp = number % 10;
			number /= 10;
			// �������
			auto sprite = gcnew Sprite(ResLoader::getKeyFrame("number_medium_" + std::to_string(temp)));
			this->addChild(sprite);
		}
	}

	// �����ܿ��
	float temp = 0;
	// �Ҷ���ͼƬλ��
	for (auto child : this->getAllChildren())
	{
		child->setAnchor(0, 0);
		temp -= child->getWidth();
		child->setPos(temp, 0);
	}
}
