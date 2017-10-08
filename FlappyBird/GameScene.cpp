#include "GameScene.h"
#include "ImageLoader.h"
#include "Bird.h"

void GameScene::init()
{
	auto bird = new Bird();
	bird->setWindowCenterY();
	bird->setX(80);
	this->add(bird);
}
