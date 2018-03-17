#include "SplashScene.h"
#include "ResLoader.h"
#include "StartScene.h"

void Start()
{
	// ���� StartScene
	auto scene = new StartScene();
	// �������뵭��ʽ�л�����
	auto transition = new TransitionFade(0.5, 0.5);
	// ���� StartScene�����Ĳ��� false ��ʾ���ٷ��ص�ǰ����
	SceneManager::enter(scene, transition, false);
}

SplashScene::SplashScene()
{
	// ��ʾ��Ϸ�տ�ʼʱ�� LOGO
	auto splash = new Sprite(ResLoader::getImage("splash"));
	this->add(splash);
	// ����ͼƬ������ʾ
	splash->setPos(Window::getSize() / 2);

	// 2 ���ִ�� Start ����
	TimerManager::start(2, Start);
}
