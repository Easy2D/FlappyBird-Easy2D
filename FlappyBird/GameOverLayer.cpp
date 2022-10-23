#include "GameOverLayer.h"
#include "GameScene.h"
#include "Number.h"
#include "ResLoader.h"
#include "MyButton.h"
#include <shellapi.h>


GameOverLayer::GameOverLayer(int score)
{
	// 显示 GameOver 图片
	auto gameover = gcnew Sprite(ResLoader::getKeyFrame("text_game_over"));
	gameover->setAnchor(0.5f, 0);
	gameover->setPosY(120);
	this->addChild(gameover);

	// 加载得分板
	initPanel(score);

	// 加载按钮
	initButtons();

	// 整体居中
	this->setPosX(Window::getWidth() / 2);
	// 将节点整体移到屏幕下方
	this->setPosY(Window::getHeight());

	// 创建向量，向上运动窗口的高度
	auto vec = Vector2(0, -Window::getHeight());
	// 位移动画，让得分面板从底部移动上来
	this->runAction(gcnew MoveBy(1, vec));
}

void GameOverLayer::initPanel(int score)
{
	// 显示得分板
	auto panel = gcnew Sprite(ResLoader::getKeyFrame("score_panel"));
	panel->setPosY(Window::getHeight() / 2);
	this->addChild(panel);

	// 获取最高分
	int bestScore = Data::getInt("best_score", 0);

	// 保存最高分
	if (score > bestScore)
	{
		bestScore = score;
		Data::saveInt("best_score", bestScore);
		// 添加 gcnew 图标
		auto newImage = gcnew Sprite(ResLoader::getKeyFrame("new"));
		newImage->setPos(145, 86);
		panel->addChild(newImage);
	}

	// 添加奖牌
	auto modalFrame = getModal(score);
	if (modalFrame)
	{
		auto modal = gcnew Sprite(modalFrame);
		modal->setPos(54, 68);
		panel->addChild(modal);
		// 添加闪光
		auto blink = gcnew Sprite(ResLoader::getKeyFrame("blink_00"));
		// 闪光动画
		auto frames = gcnew FrameSequence(0.13f);
		frames->add(ResLoader::getKeyFrame("blink_00"));
		frames->add(ResLoader::getKeyFrame("blink_01"));
		frames->add(ResLoader::getKeyFrame("blink_02"));
		frames->add(ResLoader::getKeyFrame("blink_01"));
		frames->add(ResLoader::getKeyFrame("blink_00"));
		// 随机闪光位置的动画
		auto action = gcnew CallFunc([=]
			{
				float x = Random::range(0, modal->getWidth());
				float y = Random::range(0, modal->getHeight());
				blink->setPos(x, y);
			});
		// 两动画交替循环运行
		blink->runAction(gcnew Loop(gcnew Sequence({ action, gcnew Animation(frames) })));
		modal->addChild(blink);
	}

	// 显示得分
	auto scoreImage = gcnew Number();
	scoreImage->setPos(210, 36);
	scoreImage->setLittleNumber(score);
	panel->addChild(scoreImage);

	// 显示最高分
	auto bestScoreImage = gcnew Number();
	bestScoreImage->setPos(210, 77);
	bestScoreImage->setLittleNumber(bestScore);
	panel->addChild(bestScoreImage);
}

void GameOverLayer::initButtons()
{
	// 显示重新开始按钮
	auto restartBtn = gcnew MyButton("button_restart", []() {
		ResLoader::playMusic(MusicType::Click);
		SceneManager::enter(gcnew GameScene(), gcnew FadeTransition(0.6f), false);
		});
	restartBtn->setPosY(360);
	this->addChild(restartBtn);

	// 显示返回主菜单按钮
	auto menuBtn = gcnew MyButton("button_menu", []() {
		ResLoader::playMusic(MusicType::Click);
		SceneManager::back(gcnew FadeTransition(0.6f));
		});
	menuBtn->setPosY(420);
	this->addChild(menuBtn);

	// 显示链接按钮
	auto shareBtn = gcnew MyButton("button_share", []() {
		ResLoader::playMusic(MusicType::Click);
		// 按下链接按钮，打开链接
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
		return ResLoader::getKeyFrame("medals_0");	// 铜牌
	}
	else if (score >= 20 && score < 30)
	{
		return ResLoader::getKeyFrame("medals_1");	// 银牌
	}
	else if (score >= 30 && score < 50)
	{
		return ResLoader::getKeyFrame("medals_2");	// 金牌
	}
	else
	{
		return ResLoader::getKeyFrame("medals_3");	// 钻石奖牌
	}
}
