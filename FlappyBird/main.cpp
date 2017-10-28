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
	// ����������ʽ
	EWindowStyle wStyle((LPCTSTR)IDI_ICON1);
	// ��ʼ������
	if (app.init(L"FlappyBird", 288, 512, wStyle))
	{
		// ���� AppName �����ڱ���÷֣�
		app.setAppName(L"flappybird_nomango");
		// ����ͼƬ
		ResLoader::init();
		// ���� Splash ����
		app.enterScene(
			new SplashScene(),
			new ETransitionScaleEmerge(0.3f, ETransitionScaleEmerge::ENTER)
		);
		// ������Ϸ
		app.run();
	}
	return 0;
}