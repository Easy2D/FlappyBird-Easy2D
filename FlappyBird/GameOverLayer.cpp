#include "GameOverLayer.h"
#include "GameScene.h"
#include "Number.h"
#include "ResLoader.h"
#include "MyButton.h"
#include <shellapi.h>


GameOverLayer::GameOverLayer(int score)
{
	// ��ʾ GameOver ͼƬ
	auto gameover = gcnew Sprite(ResLoader::getKeyFrame("text_game_over"));
	gameover->setAnchor(0.5f, 0);
	gameover->setPosY(120);
	this->addChild(gameover);

	// ���ص÷ְ�
	initPanel(score);

	// ���ذ�ť
	initButtons();

	// �������
	this->setPosX(Window::getWidth() / 2);
	// ���ڵ������Ƶ���Ļ�·�
	this->setPosY(Window::getHeight());

	// ���������������˶����ڵĸ߶�
	auto vec = Vector2(0, -Window::getHeight());
	// λ�ƶ������õ÷����ӵײ��ƶ�����
	this->runAction(gcnew MoveBy(1, vec));
}

void GameOverLayer::initPanel(int score)
{
	// ��ʾ�÷ְ�
	auto panel = gcnew Sprite(ResLoader::getKeyFrame("score_panel"));
	panel->setPosY(Window::getHeight() / 2);
	this->addChild(panel);

	// ��ȡ��߷�
	int bestScore = Data::getInt("best_score", 0);

	// ������߷�
	if (score > bestScore)
	{
		bestScore = score;
		Data::saveInt("best_score", bestScore);
		// ��� gcnew ͼ��
		auto newImage = gcnew Sprite(ResLoader::getKeyFrame("new"));
		newImage->setPos(145, 86);
		panel->addChild(newImage);
	}

	// ��ӽ���
	auto modalFrame = getModal(score);
	if (modalFrame)
	{
		auto modal = gcnew Sprite(modalFrame);
		modal->setPos(54, 68);
		panel->addChild(modal);
		// �������
		auto blink = gcnew Sprite(ResLoader::getKeyFrame("blink_00"));
		// ���⶯��
		auto frames = gcnew FrameSequence(0.13f);
		frames->add(ResLoader::getKeyFrame("blink_00"));
		frames->add(ResLoader::getKeyFrame("blink_01"));
		frames->add(ResLoader::getKeyFrame("blink_02"));
		frames->add(ResLoader::getKeyFrame("blink_01"));
		frames->add(ResLoader::getKeyFrame("blink_00"));
		// �������λ�õĶ���
		auto action = gcnew CallFunc([=]
			{
				float x = Random::range(0, modal->getWidth());
				float y = Random::range(0, modal->getHeight());
				blink->setPos(x, y);
			});
		// ����������ѭ������
		blink->runAction(gcnew Loop(gcnew Sequence({ action, gcnew Animation(frames) })));
		modal->addChild(blink);
	}

	// ��ʾ�÷�
	auto scoreImage = gcnew Number();
	scoreImage->setPos(210, 36);
	scoreImage->setLittleNumber(score);
	panel->addChild(scoreImage);

	// ��ʾ��߷�
	auto bestScoreImage = gcnew Number();
	bestScoreImage->setPos(210, 77);
	bestScoreImage->setLittleNumber(bestScore);
	panel->addChild(bestScoreImage);
}

void GameOverLayer::initButtons()
{
	// ��ʾ���¿�ʼ��ť
	auto restartBtn = gcnew MyButton("button_restart", []() {
		ResLoader::playMusic(MusicType::Click);
		SceneManager::enter(gcnew GameScene(), gcnew FadeTransition(0.6f), false);
		});
	restartBtn->setPosY(360);
	this->addChild(restartBtn);

	// ��ʾ�������˵���ť
	auto menuBtn = gcnew MyButton("button_menu", []() {
		ResLoader::playMusic(MusicType::Click);
		SceneManager::back(gcnew FadeTransition(0.6f));
		});
	menuBtn->setPosY(420);
	this->addChild(menuBtn);

	// ��ʾ���Ӱ�ť
	auto shareBtn = gcnew MyButton("button_share", []() {
		ResLoader::playMusic(MusicType::Click);
		// �������Ӱ�ť��������
		ShellExecuteA(NULL, "open", "https://github.com/Easy2D/FlappyBird-Easy2D", NULL, NULL, SW_SHOWNORMAL);
		});
	shareBtn->setPosY(455);
	this->addChild(shareBtn);
}

KeyFrame* GameOverLayer::getModal(int score)
{
	if (score < 10)
	{
		return nullptr;
	}
	else if (score >= 10 && score < 20)
	{
		return ResLoader::getKeyFrame("medals_0");	// ͭ��
	}
	else if (score >= 20 && score < 30)
	{
		return ResLoader::getKeyFrame("medals_1");	// ����
	}
	else if (score >= 30 && score < 50)
	{
		return ResLoader::getKeyFrame("medals_2");	// ����
	}
	else
	{
		return ResLoader::getKeyFrame("medals_3");	// ��ʯ����
	}
}
