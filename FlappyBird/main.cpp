#include <easy2d.h>
#include "SplashScene.h"
#include "ResLoader.h"
#include "resource.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	// 初始化窗口
	if (EGame::init(L"FlappyBird", 288, 512, (LPCTSTR)IDI_ICON1), L"flappybird_nomango")
	{
		// 加载图片和音乐资源
		ResLoader::init();
		// 修改节点默认中心点，便于让图片居中显示
		ENode::setDefaultPiovt(0.5f, 0.5f);

		// 创建 Splash 场景
		auto scene = new SplashScene();
		// 创建淡入淡出式的场景切换动画
		auto transition = new ETransitionFade(0, 1);
		// 进入 Splash 场景
		ESceneManager::enterScene(scene, transition);

		// 开始游戏
		EGame::run();
	}
	// 回收游戏资源
	EGame::uninit();
	return 0;
}