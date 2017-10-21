#include "GameScene.h"
#include "ImageLoader.h"
#include "GameOverLayer.h"

GameScene::GameScene()
{
	// 添加背景
	auto background = new ESprite(ImageLoader::getImage(L"bg_day"));
	// 设置背景锚点为左上角
	background->setAnchor(0, 0);
	this->add(background);
	// 添加水管
	pipes = new Pipes();
	this->add(pipes);
	// 添加小鸟
	bird = new Bird();
	bird->setPos(60, EApp::getHeight() / 2);
	this->add(bird);
	// 添加地面
	ground = new Ground();
	this->add(ground);
	// 添加得分
	scoreImage = new Number();
	scoreImage->setPos(EApp::getWidth() / 2, 50);
	scoreImage->setNumber(0);
	this->add(scoreImage);
	// 添加 ready 图片
	ready = new ESprite(ImageLoader::getImage(L"text_ready"));
	ready->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2 - 70);
	this->add(ready);
	// 添加教程图片
	tutorial = new ESprite(ImageLoader::getImage(L"tutorial"));
	tutorial->setPos(EApp::getWidth() / 2, EApp::getHeight() / 2 + 30);
	this->add(tutorial);

	// 添加鼠标消息监听
	auto mouseListener = new EMousePressListener([=](EPoint) {
		// 监听到鼠标左键按下的消息时，执行 onClick 函数
		this->onClick();
	});
	// 绑定监听器
	mouseListener->bindWith(this);

	// 添加键盘按键监听
	auto keyboardListener = new EKeyboardPressListener([=] {
		// 按下空格时，执行 onClick 函数
		if (EKeyboardMsg::getVal() == EKeyboardMsg::KEY::SPACE) {
			this->onClick();
		}
	});
	// 绑定监听器
	keyboardListener->bindWith(this);
}

void GameScene::onEnter()
{
	// 进入场景时播放音效
	//MusicUtils::playMusic(_T("res/sound/swoosh.mp3"));
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
		// 设置小鸟状态为 3
		bird->setStatus(3);
		// 播放音效
		//MusicUtils::playMusic(_T("res/sound/fly.mp3"));
	}
}

void GameScene::onStart()
{
	// 隐藏 ready 图片
	ready->runAction(new EActionFadeOut(0.4f));
	tutorial->runAction(new EActionFadeOut(0.4f));
	// 设置小鸟状态为 2
	bird->setStatus(2);
	// 水管开始移动
	pipes->start();
	// 添加定时器检测小鸟位置
	auto timer = new ETimer([=](int) {
		// 模拟小鸟下落
		bird->move(0, bird->speed);
		// 模拟小鸟所受重力
		bird->speed += 0.4f;
		// 判断是否得分
		if (pipes->pipes[0][0]->getPosX() <= bird->getPosX()) {
			static ESprite* temp = nullptr;
			if (temp != pipes->pipes[0][0]) {
				// 记录这个得分的水管
				temp = pipes->pipes[0][0];
				// 加分
				score++;
				scoreImage->setNumber(score);
			}
		}
		// 判断小鸟是否和水管碰撞
		if (bird->living) {
			/*if (pipes->isCollisionWith(bird)) {
				this->onBirdDie();
			}*/
		}
		// 若小鸟纵坐标小于地面，游戏结束
		if (EApp::getHeight() - bird->getPosY() <= 123) {
			// 小鸟死亡
			if (bird->living) {
				this->onBirdDie();
			}
			// 游戏结束，停止这个定时器
			ETimerManager::stopAllTimers();
			// 让小鸟停止
			bird->setPosY(EApp::getHeight() - 123);
			bird->setStatus(0);
			// 显示游戏结束界面
			this->onGameOver();
		}
		// 若小鸟纵坐标小于 0，限制它继续往上飞
		if (bird->getPosY() < 0) {
			bird->setPosY(0);
			bird->speed = 0;
		}
	});
	timer->bindWith(this);
}

void GameScene::onBirdDie()
{
	// 小鸟死亡
	bird->living = false;
	// 让小鸟脸朝下
	bird->setRotation(90);
	// 播放音效
	//MusicUtils::playMusic(_T("res/sound/hit.mp3"));
	// 停止地面
	ground->stop();
	// 停止水管
	pipes->stop();
	// 停止鼠标和按键监听
	EMsgManager::stopAllMouseListenersBindedWith(this);
	EMsgManager::stopAllKeyboardListenersBindedWith(this);
	// 隐藏得分
	scoreImage->runAction(new EActionFadeOut(0.5f));
	// 闪动白屏
	auto white = new ESprite(ImageLoader::getImage(L"white"));
	white->setAnchor(0, 0);
	white->setOpacity(0);
	white->setScale(16, 16);
	white->runAction(new EActionTwo(new EActionFadeIn(0.1f), new EActionFadeOut(0.1f)));
	this->add(white);
}

void GameScene::onGameOver()
{
	this->add(new GameOverLayer(score));
}
