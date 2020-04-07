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

	// 数字高度
	float height = ResLoader::getImage(L"number_big_0")->getHeight();
	// 数字总宽度
	float totalWidth = 0;
	// 为数字的每一位添加相应图片
	// 对数字 0 作单独处理
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
			// 计算每一位上的数字
			int temp = number % 10;
			number /= 10;
			// 转换为字符串
			wsprintf(str, L"number_big_%d", temp);
			auto sprite = gcnew Sprite(ResLoader::getImage(str));
			totalWidth += sprite->getWidth();
			// 添加数字
			this->addChild(sprite);
		}
	}

	// 数字总宽度
	float temp = totalWidth / 2;
	// 对齐图片位置
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

	// 数字高度
	float height = ResLoader::getImage(L"number_medium_0")->getHeight();
	// 为数字的每一位添加相应图片
	// 对数字 0 作单独处理
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
			// 计算每一位上的数字
			int temp = number % 10;
			number /= 10;
			// 转换为字符串
			wsprintf(str, L"number_medium_%d", temp);
			auto sprite = gcnew Sprite(ResLoader::getImage(str));
			// 添加数字
			this->addChild(sprite);
		}
	}

	// 数字总宽度
	float temp = 0;
	// 右对齐图片位置
	for (auto child : this->getAllChildren())
	{
		child->setAnchor(0, 0);
		temp -= child->getWidth();
		child->setPos(temp, 0);
	}
}
