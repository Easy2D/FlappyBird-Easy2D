#include "Number.h"
#include "ImageLoader.h"

Number::Number()
{
}


Number::~Number()
{
}

int Number::getNumber()
{
	return number;
}

void Number::setNumber(int number)
{
	this->number = number;
	this->clearAllSprites();

	// ���ָ߶�
	int height = ImageLoader::getImage(_T("number_big_0"))->getHeight();
	// �����ܿ��
	int totalWidth = 0;
	// Ϊ���ֵ�ÿһλ�����ӦͼƬ
	// ������ 0 ����������
	if (number == 0) {
		auto zero = new Sprite(ImageLoader::getImage(_T("number_big_0")));
		totalWidth = zero->getWidth();
		this->addSprite(zero);
	}
	else {
		TCHAR str[13];
		while (number) {
			// ����ÿһλ�ϵ�����
			int temp = number % 10;
			number /= 10;
			// ת��Ϊ�ַ���
			wsprintf(str, _T("number_big_%d"), temp);
			auto sprite = new Sprite(ImageLoader::getImage(str));
			totalWidth += sprite->getWidth();
			// �������
			this->addSprite(sprite);
		}
	}

	// �����ܿ��
	int temp = totalWidth / 2;
	// ����ͼƬλ��
	for (auto child : this->getChildren()) {
		temp -= child->getWidth();
		child->move(temp, 0);
	}
}

void Number::setLittleNumber(int number)
{
	this->number = number;
	this->clearAllSprites();

	// ���ָ߶�
	int height = ImageLoader::getImage(_T("number_medium_0"))->getHeight();
	// Ϊ���ֵ�ÿһλ�����ӦͼƬ
	// ������ 0 ����������
	if (number == 0) {
		auto zero = new Sprite(ImageLoader::getImage(_T("number_medium_0")));
		this->addSprite(zero);
	}
	else {
		TCHAR str[16];
		while (number) {
			// ����ÿһλ�ϵ�����
			int temp = number % 10;
			number /= 10;
			// ת��Ϊ�ַ���
			wsprintf(str, _T("number_medium_%d"), temp);
			auto sprite = new Sprite(ImageLoader::getImage(str));
			// �������
			this->addSprite(sprite);
		}
	}

	// �����ܿ��
	int temp = 0;
	// �Ҷ���ͼƬλ��
	for (auto child : this->getChildren()) {
		temp -= child->getWidth();
		child->move(temp, 0);
	}
}
