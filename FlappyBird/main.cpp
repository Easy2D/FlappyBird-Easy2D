//---------------------------------------------------------
// 程序名称：FlappyBird
// 作者：Nomango
// 编译环境：Visual Studio 2019 / Easy2D v2.0.4
// 项目类型：Win32 Application
//---------------------------------------------------------

#include <easy2d/easy2d.h>
#include "SplashScene.h"
#include "ResLoader.h"
#include "resource.h"

using namespace easy2d;

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	// 初始化窗口
	if (Game::init(L"FlappyBird", 288, 512))
	{
		// 设置窗口图标
		Window::setIcon(IDI_ICON1);

		// 加载图片和音乐资源
		ResLoader::init();
		// 修改节点默认中心点，便于让图片居中显示
		Node::setDefaultAnchor(0.5f, 0.5f);

		// 创建 Splash 场景
		auto scene = gcnew SplashScene();
		// 创建淡入淡出式的场景切换动画
		auto transition = gcnew FadeTransition(1);
		// 进入 Splash 场景
		SceneManager::enter(scene, transition);

		// 开始游戏
		Game::start();
	}
	// 回收游戏资源
	Game::destroy();
	return 0;
}