//---------------------------------------------------------
// �������ƣ�FlappyBird
// ���ߣ�Nomango
// ���뻷����Visual Studio 2019 / Easy2D v2.0.4
// ��Ŀ���ͣ�Win32 Application
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
	// ��ʼ������
	if (Game::init(L"FlappyBird", 288, 512))
	{
		// ���ô���ͼ��
		Window::setIcon(IDI_ICON1);

		// ����ͼƬ��������Դ
		ResLoader::init();
		// �޸Ľڵ�Ĭ�����ĵ㣬������ͼƬ������ʾ
		Node::setDefaultAnchor(0.5f, 0.5f);

		// ���� Splash ����
		auto scene = gcnew SplashScene();
		// �������뵭��ʽ�ĳ����л�����
		auto transition = gcnew FadeTransition(1);
		// ���� Splash ����
		SceneManager::enter(scene, transition);

		// ��ʼ��Ϸ
		Game::start();
	}
	// ������Ϸ��Դ
	Game::destroy();
	return 0;
}