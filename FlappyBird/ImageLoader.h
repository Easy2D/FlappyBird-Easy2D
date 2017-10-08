#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <easy2d.h>
#include <map>

class ImageLoader
{
public:
	static bool init();
	static Image* getImage(TString imageName);
};

