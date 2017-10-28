#include "SplashScene.h"
#include "ResLoader.h"
#include "StartScene.h"


SplashScene::SplashScene()
{
	auto splash = new ESprite(ResLoader::getImage(L"splash"));
	// ����ͼƬ������ʾ
	splash->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2);
	// ������������
	// 1. �ȴ� 2 ��
	auto action1 = new EActionDelay(2);
	// 2. ͬʱִ�����ź͵�������
	auto action2 = new EActionTwoAtSameTime(
		new EActionScaleTo(0.3f, 0.7f),
		new EActionFadeOut(0.3f)
	);
	// 3. �ص������л�����
	auto action3 = new EActionCallback([]() {
		EApp::enterScene(
			new StartScene(),				// �л��� StartScene
			new ETransitionFade(0, 0.5f),	// ���뵭��ʽ�л�����
			false							// �����浱ǰ����
		);
	});
	// ִ����������
	splash->runAction(new EActionSequence(3, action1, action2, action3));
	this->add(splash);
}
