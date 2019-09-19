#include "SplashScene.h"
#include "ResLoader.h"
#include "StartScene.h"

void Start()
{
	// 创建 StartScene
	auto scene = gcnew StartScene();
	// 创建淡入淡出式切换动画
	auto transition = gcnew FadeTransition(1);
	// 进入 StartScene，最后的参数 false 表示不再返回当前场景
	SceneManager::enter(scene, transition, false);
}

SplashScene::SplashScene()
{
	// 显示游戏刚开始时的 LOGO
	auto splash = gcnew Sprite(ResLoader::getImage(L"splash"));
	this->addChild(splash);
	// 设置图片居中显示
	splash->setPos(Window::getSize() / 2);

	// 2 秒后执行 Start 函数
	Timer::start(2, Start);
}
