#include "SplashScene.h"
#include "ResLoader.h"
#include "StartScene.h"


SplashScene::SplashScene()
{
	// 显示游戏刚开始时的 LOGO
	auto splash = new ESprite(ResLoader::getImage(L"splash"));
	this->add(splash);
	// 设置图片居中显示
	splash->setPos(EWindow::getWidth() / 2, EWindow::getHeight() / 2);
	// 创建连续动画
	// 1. 等待 2 秒
	auto action1 = new EActionDelay(2);
	// 2. 开始游戏
	auto action2 = new EActionCallback([=]() {
		this->start();
	});
	// 把前两个动画组合成连续动画
	auto action = new EActionTwo(action1, action2);
	// 执行连续动画
	splash->runAction(action);
}

void SplashScene::start()
{
	// 创建 StartScene
	auto scene = new StartScene();
	// 创建淡入淡出式切换动画
	auto transition = new ETransitionFade(0.5f, 0.5f);
	// 进入 StartScene，最后的参数 false 表示不再返回当前场景
	ESceneManager::enterScene(scene, transition, false);
}
