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
	float height = ResLoader::getImage(L"number_big_0")->getHeight();
	// �����ܿ��
	float totalWidth = 0;
	// Ϊ���ֵ�ÿһλ�����ӦͼƬ
	// ������ 0 ����������
	if (number == 0)
	{
		auto zero = gcnew Sprite(ResLoader::getImage(L"number_big_0"));
		totalWidth = zero->getWidth();
		this->addChild(zero);
	}
	else
	{
		WCHAR str[13];
		while (number)
		{
			// ����ÿһλ�ϵ�����
			int temp = number % 10;
			number /= 10;
			// ת��Ϊ�ַ���
			wsprintf(str, L"number_big_%d", temp);
			auto sprite = gcnew Sprite(ResLoader::getImage(str));
			totalWidth += sprite->getWidth();
			// �������
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
	float height = ResLoader::getImage(L"number_medium_0")->getHeight();
	// Ϊ���ֵ�ÿһλ�����ӦͼƬ
	// ������ 0 ����������
	if (number == 0)
	{
		auto zero = gcnew Sprite(ResLoader::getImage(L"number_medium_0"));
		this->addChild(zero);
	}
	else
	{
		WCHAR str[16];
		while (number)
		{
			// ����ÿһλ�ϵ�����
			int temp = number % 10;
			number /= 10;
			// ת��Ϊ�ַ���
			wsprintf(str, L"number_medium_%d", temp);
			auto sprite = gcnew Sprite(ResLoader::getImage(str));
			// �������
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
