#include "GameScene.h"
#include "ImageLoader.h"


void GameScene::init()
{
	// 添加背景
	this->add(ImageLoader::getImage(_T("bg_day")));
	// 添加水管
	pipes = new Pipes();
	this->add(pipes);
	// 添加地面
	ground = new Ground();
	this->add(ground);
	// 添加小鸟
	bird = new Bird();
	bird->setWindowCenterY();
	bird->setX(60);
	this->add(bird);
	// 添加 ready 图片
	ready = new Sprite(ImageLoader::getImage(_T("text_ready")));
	ready->setWindowCenter();
	ready->move(0, -70);
	this->add(ready);
	// 添加教程图片
	tutorial = new Sprite(ImageLoader::getImage(_T("tutorial")));
	tutorial->setWindowCenter();
	tutorial->move(0, 30);
	this->add(tutorial);

	// 添加鼠标消息监听
	MouseMsg::addListener(_T("mouse_click"), [=] {
		// 监听到鼠标左键按下的消息时，执行 onClick 函数
		if (MouseMsg::getMsg() == MouseMsg::LBUTTON_DOWN) {
			this->onClick();
		}
	});

	// 添加键盘按键监听
	KeyMsg::addListener(_T("key_click"), [=](VK_KEY key) {
		// 按下空格时，执行 onClick 函数
		if (key == KeyMsg::Space) {
			this->onClick();
		}
	});
}

void GameScene::onClick()
{
	if (!m_bStart) {
		// 若游戏还没有开始
		m_bStart = true;
		onStart();
	}
	if (bird->living) {
		// 如果小鸟还活着，给小鸟一个向上的速度
		bird->speed = -7.2f;
	}
}

void GameScene::onStart()
{
	// 隐藏 ready 图片
	ready->addAction(new ActionFadeOut(0.4f));
	tutorial->addAction(new ActionFadeOut(0.4f));
	// 设置小鸟状态为 2
	bird->setStatus(2);
	// 水管开始移动
	pipes->start();
	// 添加定时器检测小鸟位置
	Timer::addTimer(_T("game_timer"), [=] {
		// 模拟小鸟下落
		bird->move(0, (int)bird->speed);
		// 模拟小鸟所受重力
		bird->speed += 0.4f;
		// 判断小鸟是否和水管碰撞
		if (bird->living) {
			if (pipes->isCollisionWith(bird)) {
				this->onBirdDie();
			}
		}
		// 若小鸟纵坐标小于 118，游戏结束
		if (App::getHeight() - bird->getY() <= 135) {
			// 小鸟死亡
			if (bird->living) {
				this->onBirdDie();
			}
			// 游戏结束，停止这个定时器
			Timer::stopTimer(_T("game_timer"));
			// 让小鸟停止
			bird->setY(App::getHeight() - 135);
			bird->setStatus(0);
			// 显示游戏结束界面
			this->onGameOver();
		}
		// 若小鸟纵坐标小于 0，限制它继续往上飞
		if (bird->getY() < 0) {
			bird->setY(0);
			bird->speed = 0;
		}
	});
}

void GameScene::onBirdDie()
{
	// 小鸟死亡
	bird->living = false;
	// 停止地面
	ground->stop();
	// 停止水管
	pipes->stop();
	// 闪动白屏
	auto white = ImageLoader::getImage(_T("white"));
	white->stretch(App::getWidth(), App::getHeight());
	auto whiteSprite = new Sprite(white);
	whiteSprite->setOpacity(0);
	whiteSprite->addAction(new ActionTwo(new ActionFadeIn(0.1f), new ActionFadeOut(0.1f)));
	this->add(whiteSprite);
}

void GameScene::onGameOver()
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
	restart->setClickedCallback([] {
		// 按下重新开始，进入一个新的 GameScene
		App::enterScene(new GameScene(), false);
	});
	// 按钮按下时
	restart->setSelectCallback([=] {
		restart->move(0, 5);
	});
	restart->setUnselectCallback([=] {
		restart->move(0, -5);
	});
	restart->setY(330);
	// 显示返回主菜单按钮
	auto menu = new ImageButton(ImageLoader::getImage(_T("button_menu")));
	menu->setWindowCenterX();
	menu->setClickedCallback([] {
		// 按下返回主菜单，返回上一个场景
		App::backScene();
	});
	// 按钮按下时
	menu->setSelectCallback([=] {
		menu->move(0, 5);
	});
	menu->setUnselectCallback([=] {
		menu->move(0, -5);
	});
	menu->setY(400);
	// 合并为一个节点
	auto all = new BatchNode();
	all->add(gameover);
	all->add(panel);
	all->add(restart);
	all->add(menu);
	all->setY(App::getHeight());
	this->add(all);
	// 用Timer实现简单的移动动画
	Timer::addTimer(_T("game_over"), [=] {
		if (all->getY() > 0) {
			all->move(0, -8);
		}
		else {
			Timer::stopTimer(_T("game_over"));
		}
	});
}
