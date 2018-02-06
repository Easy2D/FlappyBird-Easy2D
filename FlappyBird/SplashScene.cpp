#include "SplashScene.h"
#include "ResLoader.h"
#include "StartScene.h"


SplashScene::SplashScene()
{
	// ��ʾ��Ϸ�տ�ʼʱ�� LOGO
	auto splash = new ESprite(ResLoader::getImage(L"splash"));
	this->add(splash);
	// ����ͼƬ������ʾ
	splash->setPos(EWindow::getWidth() / 2, EWindow::getHeight() / 2);
	// ������������
	// 1. �ȴ� 2 ��
	auto action1 = new EActionDelay(2);
	// 2. ��ʼ��Ϸ
	auto action2 = new EActionCallback([=]() {
		this->start();
	});
	// ��ǰ����������ϳ���������
	auto action = new EActionTwo(action1, action2);
	// ִ����������
	splash->runAction(action);
}

void SplashScene::start()
{
	// ���� StartScene
	auto scene = new StartScene();
	// �������뵭��ʽ�л�����
	auto transition = new ETransitionFade(0.5f, 0.5f);
	// ���� StartScene�����Ĳ��� false ��ʾ���ٷ��ص�ǰ����
	ESceneManager::enterScene(scene, transition, false);
}
