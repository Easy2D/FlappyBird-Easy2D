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

	// 数字高度
	int height = ImageLoader::getImage(_T("number_big_0"))->getHeight();
	// 数字总宽度
	int totalWidth = 0;
	// 为数字的每一位添加相应图片
	// 对数字 0 作单独处理
	if (number == 0) {
		auto zero = new Sprite(ImageLoader::getImage(_T("number_big_0")));
		totalWidth = zero->getWidth();
		this->addSprite(zero);
	}
	else {
		TCHAR str[13];
		while (number) {
			// 计算每一位上的数字
			int temp = number % 10;
			number /= 10;
			// 转换为字符串
			wsprintf(str, _T("number_big_%d"), temp);
			auto sprite = new Sprite(ImageLoader::getImage(str));
			totalWidth += sprite->getWidth();
			// 添加数字
			this->addSprite(sprite);
		}
	}

	// 数字总宽度
	int temp = totalWidth / 2;
	// 对齐图片位置
	for (auto child : this->getChildren()) {
		temp -= child->getWidth();
		child->move(temp, 0);
	}
}

void Number::setLittleNumber(int number)
{
	this->number = number;
	this->clearAllSprites();

	// 数字高度
	int height = ImageLoader::getImage(_T("number_medium_0"))->getHeight();
	// 为数字的每一位添加相应图片
	// 对数字 0 作单独处理
	if (number == 0) {
		auto zero = new Sprite(ImageLoader::getImage(_T("number_medium_0")));
		this->addSprite(zero);
	}
	else {
		TCHAR str[16];
		while (number) {
			// 计算每一位上的数字
			int temp = number % 10;
			number /= 10;
			// 转换为字符串
			wsprintf(str, _T("number_medium_%d"), temp);
			auto sprite = new Sprite(ImageLoader::getImage(str));
			// 添加数字
			this->addSprite(sprite);
		}
	}

	// 数字总宽度
	int temp = 0;
	// 右对齐图片位置
	for (auto child : this->getChildren()) {
		temp -= child->getWidth();
		child->move(temp, 0);
	}
}
