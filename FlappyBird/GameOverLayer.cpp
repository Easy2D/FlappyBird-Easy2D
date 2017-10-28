#include "GameOverLayer.h"
#include "GameScene.h"
#include "ResLoader.h"
#include <shellapi.h>


GameOverLayer::GameOverLayer(int score)
{
	// 获取得分和最高分
	this->score = score;
	this->bestScore = EFileUtils::getInt(L"best_score", 0);
	// 整体居中
	this->setPosX(EApp::getWidth() / 2);
	// 将节点整体移到屏幕下方
	this->setPosY(EApp::getHeight());
	// 显示 GameOver 图片
	auto gameover = new ESprite(ResLoader::getImage(L"text_game_over"));
	gameover->setAnchor(0.5f, 0);
	gameover->setPosY(120);
	this->addChild(gameover);
	// 加载得分板
	initPanel();
	// 加载按钮
	initButtons();
	
	// 位移动画
	auto actionMove = new EActionMoveBy(1, EVec(0, -EApp::getHeight()));
	auto actionShowScore = new EActionCallback([=] {
		// 动画结束后，显示得分
		this->showScore();
	});
	this->runAction(new EActionTwo(actionMove, actionShowScore));
}

void GameOverLayer::initPanel()
{
	// 显示得分板
	auto panel = new ESprite(ResLoader::getImage(L"score_panel"));
	panel->setAnchor(0.5f, 0.5f);
	panel->setPosY(EApp::getHeight() / 2);
	this->addChild(panel);
	// 保存最高分
	if (score > bestScore) {
		EFileUtils::saveInt(L"best_score", score);
		bestScore = score;
		// 添加 new 图标
		auto newImage = new ESprite(ResLoader::getImage(L"new"));
		newImage->setPos(145, 85);
		panel->addChild(newImage);
	}
	// 添加奖牌
	auto modalFrame = getModal();
	if (modalFrame) {
		auto modal = new ESprite(modalFrame);
		modal->setPos(54, 67);
		panel->addChild(modal);
		// 添加闪光
		auto blink = new ESprite(ResLoader::getImage(L"blink_00"));
		// 闪光帧动画
		auto frames = new EAnimation(130);
		frames->addFrame(ResLoader::getImage(L"blink_00"));
		frames->addFrame(ResLoader::getImage(L"blink_01"));
		frames->addFrame(ResLoader::getImage(L"blink_02"));
		frames->addFrame(ResLoader::getImage(L"blink_01"));
		frames->addFrame(ResLoader::getImage(L"blink_00"));
		// 执行帧动画前，随机闪光的位置
		auto action = new EActionTwo(new EActionCallback([=] {
			float x = ERandom::between(0, modal->getWidth());
			float y = ERandom::between(0, modal->getHeight());
			blink->setPos(x, y);
		}), frames);
		// 执行循环动画
		blink->runAction(new EActionLoop(action));
		modal->addChild(blink);
	}
	// 显示得分
	scoreImage = new Number();
	scoreImage->setPos(210, 35);
	scoreImage->setLittleNumber(0);
	panel->addChild(scoreImage);
	// 显示最高分
	bestScoreImage = new Number();
	bestScoreImage->setPos(210, 76);
	bestScoreImage->setLittleNumber(bestScore);
	panel->addChild(bestScoreImage);
}

void GameOverLayer::initButtons()
{
	// 显示重新开始按钮
	auto restartBtnNormal = new ESprite(ResLoader::getImage(L"button_restart"));
	restartBtnNormal->setAnchor(0.5f, 0.5f);
	auto restartBtnSelected = new ESprite(ResLoader::getImage(L"button_restart"));
	restartBtnSelected->setAnchor(0.5f, 0.5f);
	restartBtnSelected->setPosY(5);
	auto restart = new EButton(
		restartBtnNormal,
		restartBtnSelected,
		[] {
		// 按下重新开始，进入一个新的 GameScene
		ResLoader::playMusic(L"MUSIC_MENU_CLICK");
		EApp::enterScene(new GameScene(), new ETransitionFade(0.3f, 0.3f), false);
	});
	restart->setAnchorX(0.5f);
	restart->setPosY(360);
	this->addChild(restart);
	// 显示返回主菜单按钮
	auto menuBtnNormal = new ESprite(ResLoader::getImage(L"button_menu"));
	menuBtnNormal->setAnchor(0.5f, 0.5f);
	auto menuBtnSelected = new ESprite(ResLoader::getImage(L"button_menu"));
	menuBtnSelected->setAnchor(0.5f, 0.5f);
	menuBtnSelected->setPosY(5);
	auto menu = new EButton(
		menuBtnNormal,
		menuBtnSelected,
		[] {
		// 按下返回主菜单，返回上一个场景
		ResLoader::playMusic(L"MUSIC_MENU_CLICK");
		EApp::backScene(new ETransitionFade(0.3f, 0.3f));
	});
	menu->setAnchorX(0.5f);
	menu->setPosY(420);
	this->addChild(menu);
	// 显示链接按钮
	auto shareBtnNormal = new ESprite(ResLoader::getImage(L"button_share"));
	shareBtnNormal->setAnchor(0.5f, 0.5f);
	auto shareBtnSelected = new ESprite(ResLoader::getImage(L"button_share"));
	shareBtnSelected->setAnchor(0.5f, 0.5f);
	shareBtnSelected->setPosY(5);
	auto share = new EButton(
		shareBtnNormal,
		shareBtnSelected,
		[] {
		ResLoader::playMusic(L"MUSIC_MENU_CLICK");
		ShellExecute(NULL, L"open", L"https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	share->setAnchorX(0.5f);
	share->setPosY(455);
	this->addChild(share);
}

void GameOverLayer::showScore()
{
	// 计算切换数字的时间间隔，最长1200毫秒显示完动画
	LONGLONG delay = (score > 12) ? LONGLONG(1200.0f / score) : 100;
	// 得分动画
	auto timer = new ETimer(
		[=](int times) {
			// 得分上的数字变化
			scoreImage->setLittleNumber(times + 1);
		}, 
		score,	// 执行 score 次
		delay,	// 每次执行间隔时间
		true	// 立即执行
	);
	timer->bindWith(this);
}

ESpriteFrame* GameOverLayer::getModal()
{
	if (score < 10) {
		return nullptr;
	}
	else if (score >= 10 && score < 20) {
		return ResLoader::getImage(L"medals_0");	// 铜牌
	}
	else if (score >= 20 && score < 30) {
		return ResLoader::getImage(L"medals_1");	// 银牌
	}
	else if (score >= 30 && score < 50) {
		return ResLoader::getImage(L"medals_2");	// 金牌
	}
	else {
		return ResLoader::getImage(L"medals_3");	// 钻石奖牌
	}
}
