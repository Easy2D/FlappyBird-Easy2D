#include "SplashScene.h"
#include "ImageLoader.h"
#include "StartScene.h"


void SplashScene::init()
{
	auto splash = new Sprite(ImageLoader::getImage(_T("splash")));
	splash->setOpacity(0);
	splash->addAction(new ActionSequence(4, new ActionFadeIn(0.5f), new ActionDelay(1), new ActionFadeOut(0.5f), new ActionCallback([]() {
		App::enterScene(new StartScene(), false);
	})));
	this->add(splash);
}
