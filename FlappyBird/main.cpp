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
	// ��ʼ������
	if (EGame::init(L"FlappyBird", 288, 512, (LPCTSTR)IDI_ICON1), L"flappybird_nomango")
	{
		// ����ͼƬ��������Դ
		ResLoader::init();
		// �޸Ľڵ�Ĭ�����ĵ㣬������ͼƬ������ʾ
		ENode::setDefaultPiovt(0.5f, 0.5f);

		// ���� Splash ����
		auto scene = new SplashScene();
		// �������뵭��ʽ�ĳ����л�����
		auto transition = new ETransitionFade(0, 1);
		// ���� Splash ����
		ESceneManager::enterScene(scene, transition);

		// ��ʼ��Ϸ
		EGame::run();
	}
	// ������Ϸ��Դ
	EGame::uninit();
	return 0;
}