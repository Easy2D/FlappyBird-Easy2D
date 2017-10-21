#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <easy2d.h>


class ImageLoader
{
public:
	static void init();
	static ESpriteFrame* getImage(EString imageName);
};

