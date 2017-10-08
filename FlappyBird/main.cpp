#include <easy2d.h>
#include "SplashScene.h"
#include "ImageLoader.h"

int main()
{
	App app;
	app.createWindow(_T("Flappy Bird"), 288, 512, App::SHOW_CONSOLE);
	if (ImageLoader::init())
	{
		app.enterScene(new SplashScene());
		return app.run();
	}
	return 0;
}