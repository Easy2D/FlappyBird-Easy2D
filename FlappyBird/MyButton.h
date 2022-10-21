#pragma once
#include "ResLoader.h"

class MyButton
	: public Sprite
{
public:
	MyButton(const String& imageName, Function<void()> callback)
		: Sprite(ResLoader::getKeyFrame(imageName))
		, _originPosY(0)
		, _callback(callback)
	{
		auto lis = gcnew ButtonListener(std::bind(&MyButton::handle, this, std::placeholders::_1));
		this->addListener(lis);
	}

private:
	void handle(ButtonEvent evt)
	{
		if (!_originPosY)
		{
			_originPosY = this->getPosY();
		}

		if (evt == ButtonEvent::Pressed)
			this->setPosY(_originPosY + 5);	// 按钮按下时下移一小段
		else
			this->setPosY(_originPosY);

		if (evt == ButtonEvent::Clicked)
		{
			_callback();
		}
	}

	float _originPosY;
	Function<void()> _callback;
};
