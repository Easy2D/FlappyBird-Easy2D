//---------------------------------------------------------
// 程序名称：FlappyBird
// 作者：Nomango
// 最后更新：2018-3-13
// 编译环境：Visual Studio 2017 / Easy2D v2.0.0-beta6
// 项目类型：Win32 Console Application
//---------------------------------------------------------

#include <easy2d.h>
#include <fstream>
#include <map>

//---------------------------------------------------------
// 函数声明
//---------------------------------------------------------

void InitRes();					// 初始化图片和音乐资源
Image * GetImage(String name);	// 获取图片
void EnterSplash();				// 进入 Splash 场景
void EnterStart();				// 进入 Start 场景
void EnterPlay();				// 进入 Play 场景
Scene * CreatePlay();			// 创建 Play 场景
Node * CreateGround();			// 创建地面
Sprite * CreateBird();			// 创建小鸟
Node * CreatePanel();			// 创建得分板
double RandomPipeHeight();		// 随机产生水管高度
Node * CreatePipe();			// 创建一根水管
Node * CreatePipes();			// 创建水管
Animation * CreateBirdAction();	// 创建小鸟帧动画
Action * CreateBirdFly();		// 创建小鸟飞翔动画
Action * CreateBirdRotate();	// 创建小鸟旋转动画
void StartGame();				// 开始游戏
void PlaySceneTimer();			// 游戏场景定时器的执行函数
void GetInput();				// 获取用户按键
bool IsBirdDie();				// 判断小鸟是否死亡
void BirdJump();				// 小鸟跳跃
void BirdDie();					// 小鸟死亡
Image * GetModal(int score);	// 根据得分获取奖牌
void GameOver();				// 游戏结束

void ClickBtnStart();			// 点击开始按钮
void ClickBtnRestart();			// 点击重新开始按钮
void ClickBtnMenu();			// 点击返回主菜单按钮


//---------------------------------------------------------
// 全局变量
//---------------------------------------------------------

bool g_Started;				// 标志游戏是否开始
bool g_BirdDie;				// 标志小鸟是否死亡
int g_Score;				// 得分
Sprite * g_Bird;			// 小鸟
double g_BirdSpeed;			// 小鸟的下坠速度
Sprite * g_TextReady;		// 准备文本
Sprite * g_TextTutorial;	// 教程文本
Text * g_TextScore;			// 得分文本
Node * g_Ground;			// 地面
Node * g_Pipes;				// 水管
std::map<String, Image*> g_Images;	// 所有的图片


//---------------------------------------------------------
// 类声明
//---------------------------------------------------------

class MyScene : public Scene
{
public:
	// 重载 onEnter 函数
	void onEnter()
	{
		// 进入场景时自动播放音效
		MusicManager::play("res/sound/swoosh.wav");
	}
};


//---------------------------------------------------------
// 函数定义
//---------------------------------------------------------

int main()
{
	// 初始化窗口
	if (!Game::init("FlappyBird", 288, 512, NULL, "flappybird_nomango"))
	{
		return -1;	// 初始化失败退出游戏
	}

	// 加载图片和音乐资源
	InitRes();
	// 修改节点默认中心点，便于让图片居中显示
	Node::setDefaultPiovt(0.5, 0.5);
	// 进入 Splash 场景
	EnterSplash();

	// 开始游戏
	Game::run();
	// 回收游戏资源
	Game::uninit();
	return 0;
}

void InitRes()
{
	// 把音乐文件添加到音乐管理器
	MusicManager::preload("res/sound/fly.wav");
	MusicManager::preload("res/sound/hit.wav");
	MusicManager::preload("res/sound/click.wav");
	MusicManager::preload("res/sound/point.wav");
	MusicManager::preload("res/sound/swoosh.wav");

	// 预加载图片
	Image::preload("res/atlas.png");

	// 打开 atlas.txt 文件
	std::ifstream file("res/atlas.txt");
	// 读取图片信息
	while (!file.eof())
	{
		char name[21];
		double width, height, x, y;
		// 读取图片名称、宽高、起始点坐标
		file >> name >> width >> height >> x >> y;
		// 创建图片对象
		auto image = new Image("res/atlas.png", x, y, width, height);
		// 保留这个对象，防止引擎自动释放
		image->retain();
		// 将图片对象保存到 g_Images 中
		g_Images.insert(std::make_pair(name, image));
	}
}

Image * GetImage(String name)
{
	return g_Images[name];
}

void EnterSplash()
{
	// 创建场景
	auto scene = new Scene();

	// 显示游戏刚开始时的 LOGO
	auto splash = new Sprite(GetImage("过渡图片"));
	// 设置图片居中显示
	splash->setPos(Window::getSize() / 2);
	// 添加到场景中
	scene->add(splash);

	// 创建淡入淡出式的场景切换动画
	auto transition = new TransitionFade(0, 1);
	// 切换场景
	SceneManager::enter(scene, transition);

	// 2 秒后执行 EnterStart 函数
	TimerManager::start(2, EnterStart);
}

void EnterStart()
{
	// 创建场景
	auto scene = new MyScene();
	// 创建淡入淡出式切换动画
	auto transition = new TransitionFade(0.5, 0.5);
	// 切换场景，最后的参数 false 表示不再返回 Splash 场景
	SceneManager::enter(scene, transition, false);

	// 添加背景
	auto background = new Sprite(GetImage("背景_白天"));
	background->setPos(Window::getSize() / 2);
	scene->add(background);

	// 添加地面
	auto ground = CreateGround();
	scene->add(ground);

	// 添加标题图片
	auto title = new Sprite(GetImage("文本_标题"));
	title->setPos(Window::getWidth() / 2, 150);
	scene->add(title);

	// 添加小鸟
	auto bird = CreateBird();
	bird->setPos(Window::getSize() / 2);
	scene->add(bird);

	// 创建开始按钮正常状态和按下状态时显示的精灵
	auto startBtn1 = new Sprite(GetImage("按钮_开始"));
	auto startBtn2 = new Sprite(GetImage("按钮_开始"));
	// 按钮被选中时向下移动一点点
	startBtn2->setPosY(5);
	// 创建开始按钮
	auto startBtn = new Button(startBtn1, startBtn2);
	// 按下开始按钮，执行 ClickBtnStart 函数
	startBtn->setCallback(ClickBtnStart);
	// 设置按钮位置
	startBtn->setPosX(Window::getWidth() / 2);
	startBtn->setPosY(Window::getHeight() - startBtn1->getHeight() - 100);
	scene->add(startBtn);

	// 添加 copyright 图片
	auto copyright = new Sprite(GetImage("文本_版权"));
	copyright->setPos(Window::getWidth() / 2, Window::getHeight() - 20);
	scene->add(copyright);
}

void EnterPlay()
{
	// 创建 Play 场景
	auto scene = CreatePlay();
	// 切换场景
	SceneManager::enter(scene, new TransitionFade(0.3, 0.3));
}

Scene * CreatePlay()
{
	// 创建场景
	auto scene = new MyScene();

	// 添加背景
	auto background = new Sprite(GetImage("背景_白天"));
	background->setPos(Window::getSize() / 2);
	scene->add(background);

	// 添加水管
	g_Pipes = CreatePipes();
	scene->add(g_Pipes);

	// 添加地面
	g_Ground = CreateGround();
	scene->add(g_Ground);

	// 添加小鸟
	g_Bird = CreateBird();
	g_Bird->setPos(60, Window::getHeight() / 2);
	scene->add(g_Bird);

	// 添加得分显示
	g_TextScore = new Text("0", "", 28);
	g_TextScore->setName("得分");
	g_TextScore->setPos(Window::getWidth() / 2, 50);
	scene->add(g_TextScore);

	// 添加 ready 图片
	g_TextReady = new Sprite(GetImage("文本_准备"));
	g_TextReady->setPos(Window::getWidth() / 2, Window::getHeight() / 2 - 70);
	scene->add(g_TextReady);

	// 添加教程图片
	g_TextTutorial = new Sprite(GetImage("文本_教程"));
	g_TextTutorial->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 30);
	scene->add(g_TextTutorial);

	// 添加按键监听器
	Input::add(GetInput);

	// 初始化游戏变量
	g_Started = false;
	g_Score = 0;
	g_BirdDie = false;
	g_BirdSpeed = 0;

	return scene;
}

Node * CreateGround()
{
	// 移动地面的实现方法：
	// 需要两张地面图片，一块放置在屏幕内，另一块紧挨着放在它的右边（屏幕外）
	// 两块同时向左移动，当第一块完全移出屏幕时，将它放到第二块的右边
	// 第二块完全移出屏幕时，再将它放到第一块右边
	// 交替运行，地面看上去就像一直在移动了

	// 创建一个空节点
	auto ground = new Node();

	// 创建第一块地面
	auto g1 = new Sprite(GetImage("地面"));
	// 地面锚点设置在左下角
	g1->setPivot(0, 1);
	// 将地面放在屏幕底部
	g1->setPos(0, Window::getHeight());
	// 添加到空节点中
	ground->addChild(g1);

	// 创建第二块地面
	auto g2 = new Sprite(GetImage("地面"));
	g2->setPivot(0, 1);
	g2->setPos(g1->getWidth(), Window::getHeight());
	ground->addChild(g2);

	// 创建一个定时器，不断移动地面
	auto timer = new Timer(L"地面移动定时器");
	// 创建一个移动地面的函数
	auto func = [=]()
	{
		// 把地面向左移动 2 像素
		g1->movePos(-2, 0);
		g2->movePos(-2, 0);
		// 地面完全移出屏幕时，重置地面位置
		if (g1->getPosX() <= -g1->getWidth()) {
			g1->setPosX(g1->getWidth() - 1);
		}
		if (g2->getPosX() <= -g2->getWidth()) {
			g2->setPosX(g2->getWidth() - 1);
		}
	};
	// 设置定时器执行函数
	timer->setCallback(func);
	// 启动定时器
	timer->start();

	return ground;
}

Sprite * CreateBird()
{
	auto bird = new Sprite(GetImage("小鸟0_0"));
	// 创建小鸟帧动画
	auto animation = CreateBirdAction();
	// 循环运行帧动画
	bird->runAction(new ActionLoop(animation));
	// 创建小鸟飞翔动画
	auto fly = CreateBirdFly();
	// 执行飞翔动画
	bird->runAction(fly);

	// 创建一个圆形
	auto circle = new Circle();
	// 设置小鸟形状为圆形
	bird->setShape(circle);

	return bird;
}

Animation * CreateBirdAction()
{
	// 创建小鸟帧动画
	auto animation = new Animation();
	animation->setName("小鸟帧动画");
	// 添加关键帧
	animation->addKeyframe(GetImage("小鸟0_0"));
	animation->addKeyframe(GetImage("小鸟0_1"));
	animation->addKeyframe(GetImage("小鸟0_2"));
	animation->addKeyframe(GetImage("小鸟0_1"));
	// 帧动画 0.1 秒切换一次
	animation->setInterval(0.1);
	return animation;
}

Action * CreateBirdFly()
{
	// 创建飞翔动画（上下微微浮动）
	auto moveBy = new ActionMoveBy(0.4, Vector(0, 8));
	auto moveTwo = new ActionTwo(moveBy, moveBy->reverse());
	auto fly = new ActionLoop(moveTwo);
	fly->setName("小鸟飞翔动画");
	return fly;
}

Action * CreateBirdRotate()
{
	// 创建旋转动画（小鸟坠落时，先抬头，后低头）
	auto rotate = new ActionSequence(
		4,								// 由 3 个动画组成
		new ActionRotateTo(0.2, -15),	// 0.2 秒内旋转至 -15 度
		new ActionDelay(0.2),			// 等待 0.2 秒
		new ActionRotateTo(0.5, 90),	// 0.5 秒内旋转至 90 度（小鸟头朝下）
		new ActionDelay(3)				// 等待 3 秒（防止动作结束，引擎自动释放内存）
	);
	rotate->setName("小鸟旋转动画");
	return rotate;
}

double RandomPipeHeight()
{
	// 随机水管高度
	// 范围：与屏幕顶部最小距离不小于 40 像素
	// 与屏幕底部最小距离不小于地面上方 160 像素
	double landHeight = GetImage("地面")->getHeight();
	double minHeight = 40;
	double maxHeight = Window::getHeight() - landHeight - 160;
	double height = Random::range(minHeight, maxHeight);
	return height;
}

Node * CreatePipe()
{
	// 创建空节点
	auto pipe = new Node();

	// 随机产生水管高度
	double height = RandomPipeHeight();
	pipe->setPosY(height);

	// 创建上水管
	auto pipe1 = new Sprite(GetImage("水管_上"));
	pipe1->setPivot(1, 1);

	// 创建下水管
	auto pipe2 = new Sprite(GetImage("水管_下"));
	pipe2->setPivot(1, 0);
	// 下水管与上水管相距 120 像素
	pipe2->setPosY(120);

	// 把上下水管添加为子成员
	pipe->addChild(pipe1);
	pipe->addChild(pipe2);
	return pipe;
}

Node * CreatePipes()
{
	// 创建空节点
	auto pipes = new Node();
	// 创建三根水管
	auto pipe1 = CreatePipe();
	auto pipe2 = CreatePipe();
	auto pipe3 = CreatePipe();
	// 第一个水管在屏幕外130像素处
	pipe1->setPosX(Window::getWidth() + 130);
	// 其他水管在前一个水管后方200像素处
	pipe2->setPosX(pipe1->getPosX() + 200);
	pipe3->setPosX(pipe2->getPosX() + 200);
	// 添加到节点中
	pipes->addChild(pipe1);
	pipes->addChild(pipe2);
	pipes->addChild(pipe3);

	// 创建移动水管的函数
	auto MoveFunc = [=]()
	{
		// 移动所有水管
		for (auto pipe : pipes->getChildren())
		{
			pipe->movePos(-2, 0);
			// 判断水管是否移动到屏幕外
			if (pipe->getPosX() <= 0)
			{
				// 若水管在屏幕外，将它向右移动600像素
				pipe->movePosX(600);
				// 随机产生水管高度
				double height = RandomPipeHeight();
				// 修改水管高度
				pipe->setPosY(height);
			}
		}
	};
	// 创建定时器（但不启动）
	auto timer = new Timer("水管移动定时器");
	// 设置定时器的执行函数为 MoveFunc
	timer->setCallback(MoveFunc);

	return pipes;
}

void GetInput()
{
	// 按下鼠标左键或按下空格键
	if (Input::isMouseLButtonPress() ||
		Input::isKeyPress(KeyCode::SPACE))
	{
		if (!g_Started)
		{
			// 若游戏还没有开始，开始游戏
			StartGame();
		}
		// 让小鸟跳跃
		BirdJump();
	}
}

void StartGame()
{
	g_Started = true;

	// 隐藏准备和教程图片
	g_TextReady->runAction(new ActionFadeOut(0.4));
	g_TextTutorial->runAction(new ActionFadeOut(0.4));

	// 创建 PlaySceneTimer 函数的回调函数
	TimerCallback tcb = PlaySceneTimer;
	// 启动定时器，自动执行 PlaySceneTimer 函数
	auto timer = new Timer("游戏场景定时器", tcb);
	timer->start();

	// 启动水管移动定时器
	TimerManager::start("水管移动定时器");

	// 停止小鸟飞翔动画
	g_Bird->stopAction("小鸟飞翔动画");
	// 获取小鸟的帧动画
	auto animation = (Animation*)g_Bird->getAction("小鸟帧动画");
	// 帧动画时间间隔设置为 0.05 秒，加速小鸟扇动翅膀的速度
	animation->setInterval(0.05);
	// 创建旋转动画
	auto rotate = CreateBirdRotate();
	// 执行旋转动画
	g_Bird->runAction(rotate);
}

void BirdJump()
{
	if (!g_BirdDie)
	{
		// 如果小鸟还活着，给小鸟一个向上的速度
		g_BirdSpeed = -7.2;
		// 获取小鸟的旋转动画
		auto rotate = g_Bird->getAction("小鸟旋转动画");
		// 重新执行旋转动画
		rotate->reset();
		// 播放音效
		MusicManager::play("res/sound/fly.wav");
	}
}

void PlaySceneTimer()
{
	// 模拟小鸟下落
	g_Bird->movePosY(g_BirdSpeed);
	// 模拟小鸟所受重力
	g_BirdSpeed += 0.4;
	// 若小鸟纵坐标小于 0，不让它继续往上飞
	if (g_Bird->getPosY() < 0)
	{
		g_Bird->setPosY(0);
		g_BirdSpeed = 0;
	}
	// 检测小鸟是否和地面水管发生碰撞
	if (IsBirdDie())
	{
		// 发生碰撞，小鸟死亡
		BirdDie();
	}
	
	// 判断小鸟是否飞过了水管
	for (auto pipe : g_Pipes->getChildren())
	{
		// 当水管坐标正好和小鸟坐标相同时，得分
		if (pipe->getPosX() == g_Bird->getPosX())
		{
			// 加分
			g_Score++;
			// 修改得分显示
			g_TextScore->setText(String::toString(g_Score));
			// 播放音效
			MusicManager::play("res/sound/point.wav");
		}
	}
	// 若小鸟纵坐标小于地面，游戏结束
	if (Window::getHeight() - g_Bird->getPosY() <= 123)
	{
		// 让小鸟停止
		g_Bird->setPosY(Window::getHeight() - 123);
		g_Bird->stopAllActions();
		// 让小鸟脸朝下
		g_Bird->setRotation(90);
		// 游戏结束
		GameOver();
	}
}

bool IsBirdDie()
{
	// 判断小鸟和地面是否碰撞
	if (g_Bird->isIntersectWith(g_Ground))
	{
		return true;
	}
	// 判断小鸟和水管是否碰撞
	if (g_Bird->isIntersectWith(g_Pipes))
	{
		return true;
	}
	return false;
}

void BirdDie()
{
	// 若小鸟已经死亡，直接返回
	if (g_BirdDie)
		return;

	// 小鸟死亡
	g_BirdDie = true;
	// 播放音效
	MusicManager::play("res/sound/hit.wav");

	// 获取当前场景
	auto scene = SceneManager::getCurrentScene();
	// 隐藏得分
	g_TextScore->runAction(new ActionFadeOut(0.5));

	// 闪动白屏
	// 创建一个白色的图片
	auto white = new Sprite(GetImage("白色"));
	white->setPivot(0, 0);
	// 透明度设置为 0
	white->setOpacity(0);
	// 整体放大 16 倍
	white->setScale(16);
	// 先执行一个 0.1 秒的淡入动画，再执行一个 0.1 秒的淡出动画
	white->runAction(new ActionTwo(new ActionFadeIn(0.1), new ActionFadeOut(0.1)));
	scene->add(white);

	// 停止水管移动定时器
	TimerManager::clear("水管移动定时器");
	// 让地面停止移动
	// 此时地面移动定时器有两个（另一个在 Start 场景中）
	// 将第二个（也就是 Play 场景中的）停止
	TimerManager::get("地面移动定时器")[1]->stopAndClear();
}

void GameOver()
{
	// 标志游戏已经结束
	g_Started = false;
	// 小鸟死亡
	BirdDie();
	// 停止按键监听
	Input::clearAll();
	// 停止游戏场景定时器
	TimerManager::clear("游戏场景定时器");

	// 获取当前场景
	auto scene = SceneManager::getCurrentScene();
	// 创建一个空节点
	auto layer = new Node();
	// 添加到场景中
	scene->add(layer);

	// 显示 GameOver 图片
	auto gameover = new Sprite(GetImage("文本_游戏结束"));
	gameover->setPivot(0.5, 0);
	gameover->setPosY(120);
	layer->addChild(gameover);

	// 创建得分板
	auto panel = CreatePanel();
	layer->addChild(panel);

	// 显示重新开始按钮
	auto restartBtn1 = new Sprite(GetImage("按钮_重新开始"));
	auto restartBtn2 = new Sprite(GetImage("按钮_重新开始"));
	restartBtn2->setPosY(5);
	auto restartBtn = new Button(restartBtn1, restartBtn2);
	// 按下重新开始按钮，执行 ClickBtnRestart 函数
	restartBtn->setCallback(ClickBtnRestart);
	restartBtn->setPosY(360);
	layer->addChild(restartBtn);

	// 显示返回主菜单按钮
	auto menuBtn1 = new Sprite(GetImage("按钮_菜单"));
	auto menuBtn2 = new Sprite(GetImage("按钮_菜单"));
	menuBtn2->setPosY(5);
	auto menuBtn = new Button(menuBtn1, menuBtn2);
	// 按下返回主菜单按钮，执行 ClickBtnMenu 函数
	menuBtn->setCallback(ClickBtnMenu);
	menuBtn->setPosY(420);
	layer->addChild(menuBtn);

	// 整体居中
	layer->setPosX(Window::getWidth() / 2);
	// 将节点整体移到屏幕下方
	layer->setPosY(Window::getHeight());

	// 创建向量，向上运动窗口的高度
	auto vec = Vector(0, -Window::getHeight());
	// 位移动画，让得分面板从底部移动上来
	layer->runAction(new ActionMoveBy(1, vec));
}

Node * CreatePanel()
{
	// 创建得分板
	auto panel = new Sprite(GetImage("得分板"));
	panel->setPosY(Window::getHeight() / 2);

	// 获取最高分
	int bestScore = Data::getInt("最高分", 0);

	// 保存最高分
	if (g_Score > bestScore)
	{
		bestScore = g_Score;
		Data::saveInt("最高分", bestScore);
		// 添加 new 图标
		auto newImage = new Sprite(GetImage("新成绩"));
		newImage->setPos(26, 23);
		panel->addChild(newImage);
	}

	// 添加奖牌
	auto modalFrame = GetModal(g_Score);
	if (modalFrame)
	{
		auto modal = new Sprite(modalFrame);
		modal->setPos(-65, 5);
		panel->addChild(modal);
	}

	// 显示得分
	auto scoreImage = new Text("", "", 20, Color::BLACK);
	scoreImage->setText(String::toString(g_Score));
	scoreImage->setPivot(1, 0.5);
	scoreImage->setPos(91, -20);
	panel->addChild(scoreImage);

	// 显示最高分
	auto bestScoreImage = new Text("", "", 20, Color::BLACK);
	bestScoreImage->setText(String::toString(bestScore));
	bestScoreImage->setPivot(1, 0.5);
	bestScoreImage->setPos(91, 21);
	panel->addChild(bestScoreImage);
	return panel;
}

Image * GetModal(int score)
{
	if (score < 10) return nullptr;
	else if (score >= 10 && score < 20) return GetImage("铜牌");
	else if (score >= 20 && score < 30) return GetImage("银牌");
	else if (score >= 30 && score < 50) return GetImage("金牌");
	else return GetImage("铂金牌");
}

void ClickBtnStart()
{
	// 播放按钮音效
	MusicManager::play("res/sound/click.wav");
	// 执行 EnterPlay 函数
	EnterPlay();
}

void ClickBtnRestart()
{
	// 播放按钮音效
	MusicManager::play("res/sound/click.wav");
	// 创建新的 Play 场景
	auto scene = CreatePlay();
	// 切换场景
	SceneManager::enter(scene, new TransitionFade(0.3, 0.3), false);
}

void ClickBtnMenu()
{
	// 播放按钮音效
	MusicManager::play("res/sound/click.wav");
	// 返回 Start 场景
	SceneManager::back(new TransitionFade(0.3, 0.3));
}