#include "GameOverLayer.h"
#include "GameScene.h"
#include "ImageLoader.h"


GameOverLayer::GameOverLayer(int score)
{
	// 显示 GameOver 图片
	auto gameover = ImageLoader::getImage(_T("text_game_over"));
	gameover->setWindowCenterX();
	gameover->setY(120);
	// 显示得分板
	auto panel = ImageLoader::getImage(_T("score_panel"));
	panel->setWindowCenter();
	// 显示重新开始按钮
	auto restart = new ImageButton(ImageLoader::getImage(_T("button_restart")));
	restart->setWindowCenterX();
	restart->setY(330);
	restart->setClickedCallback([] {
		// 按下重新开始，进入一个新的 GameScene
		App::enterScene(new GameScene(), false);
	});
	// 按钮按下时，向下移动5像素
	restart->setSelectCallback([=] {
		restart->move(0, 5);
	});
	restart->setUnselectCallback([=] {
		restart->move(0, -5);
	});
	// 显示返回主菜单按钮
	auto menu = new ImageButton(ImageLoader::getImage(_T("button_menu")));
	menu->setWindowCenterX();
	menu->setY(400);
	menu->setClickedCallback([] {
		// 按下返回主菜单，返回上一个场景
		App::backScene();
	});
	// 按钮按下时，向下移动5像素
	menu->setSelectCallback([=] {
		menu->move(0, 5);
	});
	menu->setUnselectCallback([=] {
		menu->move(0, -5);
	});
	// 显示链接按钮
	auto share = new ImageButton(ImageLoader::getImage(_T("button_share")));
	share->setWindowCenterX();
	share->setY(435);
	share->setClickedCallback([] {
		//MusicUtils::playMusic(_T("res/sound/MenuClick.mp3"));
		ShellExecute(NULL, _T("open"), _T("https://gitee.com/werelone/FlappyBird"), NULL, NULL, SW_SHOWNORMAL);
	});
	// 按钮按下时，向下移动5像素
	share->setSelectCallback([=] {
		share->move(0, 5);
	});
	share->setUnselectCallback([=] {
		share->move(0, -5);
	});
	// 合并为一个节点
	auto all = new BatchNode();
	all->add(gameover);
	all->add(panel);
	all->add(restart);
	all->add(menu);
	all->add(share);
	this->add(all);
	// 将节点整体移到屏幕下方
	all->setY(App::getHeight());
	// 用Timer实现简单的移动动画
	Timer::addTimer(_T("game_over"), [=] {
		if (all->getY() > 0) {
			all->move(0, -8);
		}
		else {
			// 动画结束后，显示得分
			showScore();
			Timer::stopTimer(_T("game_over"));
		}
	});
	
	// 获取得分和最高分
	this->score = score;
	this->bestScore = FileUtils::getInt(_T("best_score"), 0);
	// 保存最高分
	if (score >= bestScore) {
		FileUtils::saveInt(_T("best_score"), score);
		bestScore = score;
		// 添加 new 图标
		auto newImage = ImageLoader::getImage(_T("new"));
		newImage->setPos(155, 269);
		all->add(newImage);
	}
	// 添加奖牌
	auto modal = getModal();
	if (modal) {
		modal->setPos(57, 237);
		all->add(modal);
		// 添加闪光
		auto blink = new Sprite(ImageLoader::getImage(_T("blink_00")));
		// 闪光帧动画
		auto frames = new ActionFrames(130);
		frames->addFrame(ImageLoader::getImage(_T("blink_00")));
		frames->addFrame(ImageLoader::getImage(_T("blink_01")));
		frames->addFrame(ImageLoader::getImage(_T("blink_02")));
		frames->addFrame(ImageLoader::getImage(_T("blink_01")));
		frames->addFrame(ImageLoader::getImage(_T("blink_00")));
		// 执行帧动画前，随机闪光的位置
		auto action = new ActionTwo(new ActionCallback([=] {
			int x = random(modal->getX(), modal->getX() + modal->getWidth());
			int y = random(modal->getY(), modal->getY() + modal->getHeight());
			blink->setPos(x, y);
		}), frames);
		// 执行循环动画
		blink->runAction(new ActionNeverStop(action));
		all->add(blink);
	}
	// 显示得分
	scoreImage = new Number();
	scoreImage->setDisplay(false);
	scoreImage->setPos(235, 228);
	scoreImage->setLittleNumber(0);
	this->add(scoreImage);
	// 显示最高分
	bestScoreImage = new Number();
	bestScoreImage->setDisplay(false);
	bestScoreImage->setPos(235, 269);
	bestScoreImage->setLittleNumber(bestScore);
	this->add(bestScoreImage);
	// 播放音效
	//MusicUtils::playMusic(_T("res/sound/swoosh.mp3"));
}


GameOverLayer::~GameOverLayer()
{
}

void GameOverLayer::showScore()
{
	// 显示得分、最高分和奖牌
	scoreImage->setDisplay(true);
	bestScoreImage->setDisplay(true);
	// 计算切换数字的时间间隔，最长1200毫秒显示完动画
	UINT delay = (score > 12) ? UINT(1200.0f / score) : 100;
	// 得分动画
	Timer::addTimer(_T("show_score"), delay, [=] {
		if (scoreImage->getNumber() < score) {
			// 切换一个数字
			scoreImage->setLittleNumber(scoreImage->getNumber() + 1);
		}
		else {
			Timer::stopTimer(_T("show_score"));
		}
	});
}

Image* GameOverLayer::getModal()
{
	if (score < 10) {
		return nullptr;
	}
	else if (score >= 10 && score < 20) {
		return ImageLoader::getImage(_T("medals_0"));	// 铜牌
	}
	else if (score >= 20 && score < 30) {
		return ImageLoader::getImage(_T("medals_1"));	// 银牌
	}
	else if (score >= 30 && score < 50) {
		return ImageLoader::getImage(_T("medals_2"));	// 金牌
	}
	else {
		return ImageLoader::getImage(_T("medals_3"));	// 钻石奖牌
	}
}
