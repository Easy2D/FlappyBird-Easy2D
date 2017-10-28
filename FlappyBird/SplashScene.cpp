#include "SplashScene.h"
#include "ResLoader.h"
#include "StartScene.h"


SplashScene::SplashScene()
{
	auto splash = new ESprite(ResLoader::getImage(L"splash"));
	// 设置图片居中显示
	splash->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2);
	// 创建连续动画
	// 1. 等待 2 秒
	auto action1 = new EActionDelay(2);
	// 2. 同时执行缩放和淡出动画
	auto action2 = new EActionTwoAtSameTime(
		new EActionScaleTo(0.3f, 0.7f),
		new EActionFadeOut(0.3f)
	);
	// 3. 回调函数切换场景
	auto action3 = new EActionCallback([]() {
		EApp::enterScene(
			new StartScene(),				// 切换至 StartScene
			new ETransitionFade(0, 0.5f),	// 淡入淡出式切换动画
			false							// 不保存当前场景
		);
	});
	// 执行连续动画
	splash->runAction(new EActionSequence(3, action1, action2, action3));
	this->add(splash);
}
