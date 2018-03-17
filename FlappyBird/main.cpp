//---------------------------------------------------------
// �������ƣ�FlappyBird
// ���ߣ�Nomango
// �����£�2018-3-14
// ���뻷����Visual Studio 2017 / Easy2D v2.0.0-beta6
// ��Ŀ���ͣ�Win32 Application
//---------------------------------------------------------

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
	if (Game::init("FlappyBird", 288, 512, (LPCTSTR)IDI_ICON1, "flappybird_nomango"))
	{
		// ����ͼƬ��������Դ
		ResLoader::init();
		// �޸Ľڵ�Ĭ�����ĵ㣬������ͼƬ������ʾ
		Node::setDefaultPiovt(0.5, 0.5);
		// �ڵ㲻����Ĭ����״
		Node::setDefaultShapeEnable(false);
		// ����ײ���
		ShapeManager::setCollisionEnable(true);

		// ���� Splash ����
		auto scene = new SplashScene();
		// �������뵭��ʽ�ĳ����л�����
		auto transition = new TransitionFade(0, 1);
		// ���� Splash ����
		SceneManager::enter(scene, transition);

		// ��ʼ��Ϸ
		Game::run();
	}
	// ������Ϸ��Դ
	Game::uninit();
	return 0;
}