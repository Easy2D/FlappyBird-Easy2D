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
	EApp app;
	// 创建窗口样式
	EWindowStyle wStyle((LPCTSTR)IDI_ICON1);
	// 初始化窗口
	if (app.init(L"FlappyBird", 288, 512, wStyle))
	{
		// 设置 AppName （用于保存得分）
		app.setAppName(L"flappybird_nomango");
		// 加载图片
		ResLoader::init();
		// 进入 Splash 场景
		app.enterScene(
			new SplashScene(),
			new ETransitionScaleEmerge(0.3f, ETransitionScaleEmerge::ENTER)
		);
		// 运行游戏
		app.run();
	}
	return 0;
}