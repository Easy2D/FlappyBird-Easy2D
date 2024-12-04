#include "SplashScene.h"
#include "ResLoader.h"
#include "StartScene.h"

void Start()
{
	// ���� StartScene
	auto scene = gcnew StartScene();
	// �������뵭��ʽ�л�����
	auto transition = gcnew FadeTransition(1);
	// ���� StartScene�����Ĳ��� false ��ʾ���ٷ��ص�ǰ����
	SceneManager::enter(scene, transition, false);
}

SplashScene::SplashScene()
{
	// ��ʾ��Ϸ�տ�ʼʱ�� LOGO
	auto splash = gcnew Sprite(ResLoader::getKeyFrame("splash"));
	this->addChild(splash);
	// ����ͼƬ������ʾ
	splash->setPos(Window::getSize() / 2);

	// 2 ���ִ�� Start ����
	Timer::runDelayed(2, Start);
}
