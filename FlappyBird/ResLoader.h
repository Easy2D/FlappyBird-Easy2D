#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <easy2d.h>


class ResLoader
{
public:
	static void init();
	static void playMusic(const EString & musicName);
	static ESpriteFrame* getImage(const EString & imageName);
};

