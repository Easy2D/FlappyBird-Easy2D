#include "Bird.h"
#include "ImageLoader.h"


Bird::Bird()
{
	auto frames = new ActionFrames(90);
	this->addAction(new ActionNeverStop(frames));
	this->setStatus(1);

	int mode = random(0, 2);
	if (mode == 0)
	{
		this->setImage(ImageLoader::getImage(_T("bird0_0")));
		frames->addFrame(ImageLoader::getImage(_T("bird0_0")));
		frames->addFrame(ImageLoader::getImage(_T("bird0_1")));
		frames->addFrame(ImageLoader::getImage(_T("bird0_2")));
		frames->addFrame(ImageLoader::getImage(_T("bird0_1")));
	}
	else if (mode == 1)
	{
		this->setImage(ImageLoader::getImage(_T("bird1_0")));
		frames->addFrame(ImageLoader::getImage(_T("bird1_0")));
		frames->addFrame(ImageLoader::getImage(_T("bird1_1")));
		frames->addFrame(ImageLoader::getImage(_T("bird1_2")));
		frames->addFrame(ImageLoader::getImage(_T("bird1_1")));
	}
	else
	{
		this->setImage(ImageLoader::getImage(_T("bird2_0")));
		frames->addFrame(ImageLoader::getImage(_T("bird2_0")));
		frames->addFrame(ImageLoader::getImage(_T("bird2_1")));
		frames->addFrame(ImageLoader::getImage(_T("bird2_2")));
		frames->addFrame(ImageLoader::getImage(_T("bird2_1")));
	}
}


Bird::~Bird()
{
}

void Bird::setStatus(int status)
{
	switch (status)
	{
	case 0:
		this->stopAllActions();
		break;
	case 1:
		{
		auto fly = new ActionMoveBy(0.4f, CVector(0, 8));
		this->addAction(new ActionNeverStop(new ActionTwo(fly, fly->reverse())));
		break;
		}
	default:
		break;
	}
}
