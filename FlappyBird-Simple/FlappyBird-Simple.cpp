//---------------------------------------------------------
// �������ƣ�FlappyBird
// ���ߣ�Nomango
// �����£�2018-3-13
// ���뻷����Visual Studio 2017 / Easy2D v2.0.0-beta6
// ��Ŀ���ͣ�Win32 Console Application
//---------------------------------------------------------

#include <easy2d.h>
#include <fstream>
#include <map>

//---------------------------------------------------------
// ��������
//---------------------------------------------------------

void InitRes();					// ��ʼ��ͼƬ��������Դ
Image * GetImage(String name);	// ��ȡͼƬ
void EnterSplash();				// ���� Splash ����
void EnterStart();				// ���� Start ����
void EnterPlay();				// ���� Play ����
Scene * CreatePlay();			// ���� Play ����
Node * CreateGround();			// ��������
Sprite * CreateBird();			// ����С��
Node * CreatePanel();			// �����÷ְ�
double RandomPipeHeight();		// �������ˮ�ܸ߶�
Node * CreatePipe();			// ����һ��ˮ��
Node * CreatePipes();			// ����ˮ��
Animation * CreateBirdAction();	// ����С��֡����
Action * CreateBirdFly();		// ����С����趯��
Action * CreateBirdRotate();	// ����С����ת����
void StartGame();				// ��ʼ��Ϸ
void PlaySceneTimer();			// ��Ϸ������ʱ����ִ�к���
void GetInput();				// ��ȡ�û�����
bool IsBirdDie();				// �ж�С���Ƿ�����
void BirdJump();				// С����Ծ
void BirdDie();					// С������
Image * GetModal(int score);	// ���ݵ÷ֻ�ȡ����
void GameOver();				// ��Ϸ����

void ClickBtnStart();			// �����ʼ��ť
void ClickBtnRestart();			// ������¿�ʼ��ť
void ClickBtnMenu();			// ����������˵���ť


//---------------------------------------------------------
// ȫ�ֱ���
//---------------------------------------------------------

bool g_Started;				// ��־��Ϸ�Ƿ�ʼ
bool g_BirdDie;				// ��־С���Ƿ�����
int g_Score;				// �÷�
Sprite * g_Bird;			// С��
double g_BirdSpeed;			// С�����׹�ٶ�
Sprite * g_TextReady;		// ׼���ı�
Sprite * g_TextTutorial;	// �̳��ı�
Text * g_TextScore;			// �÷��ı�
Node * g_Ground;			// ����
Node * g_Pipes;				// ˮ��
std::map<String, Image*> g_Images;	// ���е�ͼƬ


//---------------------------------------------------------
// ������
//---------------------------------------------------------

class MyScene : public Scene
{
public:
	// ���� onEnter ����
	void onEnter()
	{
		// ���볡��ʱ�Զ�������Ч
		MusicManager::play("res/sound/swoosh.wav");
	}
};


//---------------------------------------------------------
// ��������
//---------------------------------------------------------

int main()
{
	// ��ʼ������
	if (!Game::init("FlappyBird", 288, 512, NULL, "flappybird_nomango"))
	{
		return -1;	// ��ʼ��ʧ���˳���Ϸ
	}

	// ����ͼƬ��������Դ
	InitRes();
	// �޸Ľڵ�Ĭ�����ĵ㣬������ͼƬ������ʾ
	Node::setDefaultPiovt(0.5, 0.5);
	// ���� Splash ����
	EnterSplash();

	// ��ʼ��Ϸ
	Game::run();
	// ������Ϸ��Դ
	Game::uninit();
	return 0;
}

void InitRes()
{
	// �������ļ���ӵ����ֹ�����
	MusicManager::preload("res/sound/fly.wav");
	MusicManager::preload("res/sound/hit.wav");
	MusicManager::preload("res/sound/click.wav");
	MusicManager::preload("res/sound/point.wav");
	MusicManager::preload("res/sound/swoosh.wav");

	// Ԥ����ͼƬ
	Image::preload("res/atlas.png");

	// �� atlas.txt �ļ�
	std::ifstream file("res/atlas.txt");
	// ��ȡͼƬ��Ϣ
	while (!file.eof())
	{
		char name[21];
		double width, height, x, y;
		// ��ȡͼƬ���ơ���ߡ���ʼ������
		file >> name >> width >> height >> x >> y;
		// ����ͼƬ����
		auto image = new Image("res/atlas.png", x, y, width, height);
		// ����������󣬷�ֹ�����Զ��ͷ�
		image->retain();
		// ��ͼƬ���󱣴浽 g_Images ��
		g_Images.insert(std::make_pair(name, image));
	}
}

Image * GetImage(String name)
{
	return g_Images[name];
}

void EnterSplash()
{
	// ��������
	auto scene = new Scene();

	// ��ʾ��Ϸ�տ�ʼʱ�� LOGO
	auto splash = new Sprite(GetImage("����ͼƬ"));
	// ����ͼƬ������ʾ
	splash->setPos(Window::getSize() / 2);
	// ��ӵ�������
	scene->add(splash);

	// �������뵭��ʽ�ĳ����л�����
	auto transition = new TransitionFade(0, 1);
	// �л�����
	SceneManager::enter(scene, transition);

	// 2 ���ִ�� EnterStart ����
	TimerManager::start(2, EnterStart);
}

void EnterStart()
{
	// ��������
	auto scene = new MyScene();
	// �������뵭��ʽ�л�����
	auto transition = new TransitionFade(0.5, 0.5);
	// �л����������Ĳ��� false ��ʾ���ٷ��� Splash ����
	SceneManager::enter(scene, transition, false);

	// ��ӱ���
	auto background = new Sprite(GetImage("����_����"));
	background->setPos(Window::getSize() / 2);
	scene->add(background);

	// ��ӵ���
	auto ground = CreateGround();
	scene->add(ground);

	// ��ӱ���ͼƬ
	auto title = new Sprite(GetImage("�ı�_����"));
	title->setPos(Window::getWidth() / 2, 150);
	scene->add(title);

	// ���С��
	auto bird = CreateBird();
	bird->setPos(Window::getSize() / 2);
	scene->add(bird);

	// ������ʼ��ť����״̬�Ͱ���״̬ʱ��ʾ�ľ���
	auto startBtn1 = new Sprite(GetImage("��ť_��ʼ"));
	auto startBtn2 = new Sprite(GetImage("��ť_��ʼ"));
	// ��ť��ѡ��ʱ�����ƶ�һ���
	startBtn2->setPosY(5);
	// ������ʼ��ť
	auto startBtn = new Button(startBtn1, startBtn2);
	// ���¿�ʼ��ť��ִ�� ClickBtnStart ����
	startBtn->setCallback(ClickBtnStart);
	// ���ð�ťλ��
	startBtn->setPosX(Window::getWidth() / 2);
	startBtn->setPosY(Window::getHeight() - startBtn1->getHeight() - 100);
	scene->add(startBtn);

	// ��� copyright ͼƬ
	auto copyright = new Sprite(GetImage("�ı�_��Ȩ"));
	copyright->setPos(Window::getWidth() / 2, Window::getHeight() - 20);
	scene->add(copyright);
}

void EnterPlay()
{
	// ���� Play ����
	auto scene = CreatePlay();
	// �л�����
	SceneManager::enter(scene, new TransitionFade(0.3, 0.3));
}

Scene * CreatePlay()
{
	// ��������
	auto scene = new MyScene();

	// ��ӱ���
	auto background = new Sprite(GetImage("����_����"));
	background->setPos(Window::getSize() / 2);
	scene->add(background);

	// ���ˮ��
	g_Pipes = CreatePipes();
	scene->add(g_Pipes);

	// ��ӵ���
	g_Ground = CreateGround();
	scene->add(g_Ground);

	// ���С��
	g_Bird = CreateBird();
	g_Bird->setPos(60, Window::getHeight() / 2);
	scene->add(g_Bird);

	// ��ӵ÷���ʾ
	g_TextScore = new Text("0", "", 28);
	g_TextScore->setName("�÷�");
	g_TextScore->setPos(Window::getWidth() / 2, 50);
	scene->add(g_TextScore);

	// ��� ready ͼƬ
	g_TextReady = new Sprite(GetImage("�ı�_׼��"));
	g_TextReady->setPos(Window::getWidth() / 2, Window::getHeight() / 2 - 70);
	scene->add(g_TextReady);

	// ��ӽ̳�ͼƬ
	g_TextTutorial = new Sprite(GetImage("�ı�_�̳�"));
	g_TextTutorial->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 30);
	scene->add(g_TextTutorial);

	// ��Ӱ���������
	Input::add(GetInput);

	// ��ʼ����Ϸ����
	g_Started = false;
	g_Score = 0;
	g_BirdDie = false;
	g_BirdSpeed = 0;

	return scene;
}

Node * CreateGround()
{
	// �ƶ������ʵ�ַ�����
	// ��Ҫ���ŵ���ͼƬ��һ���������Ļ�ڣ���һ������ŷ��������ұߣ���Ļ�⣩
	// ����ͬʱ�����ƶ�������һ����ȫ�Ƴ���Ļʱ�������ŵ��ڶ�����ұ�
	// �ڶ�����ȫ�Ƴ���Ļʱ���ٽ����ŵ���һ���ұ�
	// �������У����濴��ȥ����һֱ���ƶ���

	// ����һ���սڵ�
	auto ground = new Node();

	// ������һ�����
	auto g1 = new Sprite(GetImage("����"));
	// ����ê�����������½�
	g1->setPivot(0, 1);
	// �����������Ļ�ײ�
	g1->setPos(0, Window::getHeight());
	// ��ӵ��սڵ���
	ground->addChild(g1);

	// �����ڶ������
	auto g2 = new Sprite(GetImage("����"));
	g2->setPivot(0, 1);
	g2->setPos(g1->getWidth(), Window::getHeight());
	ground->addChild(g2);

	// ����һ����ʱ���������ƶ�����
	auto timer = new Timer(L"�����ƶ���ʱ��");
	// ����һ���ƶ�����ĺ���
	auto func = [=]()
	{
		// �ѵ��������ƶ� 2 ����
		g1->movePos(-2, 0);
		g2->movePos(-2, 0);
		// ������ȫ�Ƴ���Ļʱ�����õ���λ��
		if (g1->getPosX() <= -g1->getWidth()) {
			g1->setPosX(g1->getWidth() - 1);
		}
		if (g2->getPosX() <= -g2->getWidth()) {
			g2->setPosX(g2->getWidth() - 1);
		}
	};
	// ���ö�ʱ��ִ�к���
	timer->setCallback(func);
	// ������ʱ��
	timer->start();

	return ground;
}

Sprite * CreateBird()
{
	auto bird = new Sprite(GetImage("С��0_0"));
	// ����С��֡����
	auto animation = CreateBirdAction();
	// ѭ������֡����
	bird->runAction(new ActionLoop(animation));
	// ����С����趯��
	auto fly = CreateBirdFly();
	// ִ�з��趯��
	bird->runAction(fly);

	// ����һ��Բ��
	auto circle = new Circle();
	// ����С����״ΪԲ��
	bird->setShape(circle);

	return bird;
}

Animation * CreateBirdAction()
{
	// ����С��֡����
	auto animation = new Animation();
	animation->setName("С��֡����");
	// ��ӹؼ�֡
	animation->addKeyframe(GetImage("С��0_0"));
	animation->addKeyframe(GetImage("С��0_1"));
	animation->addKeyframe(GetImage("С��0_2"));
	animation->addKeyframe(GetImage("С��0_1"));
	// ֡���� 0.1 ���л�һ��
	animation->setInterval(0.1);
	return animation;
}

Action * CreateBirdFly()
{
	// �������趯��������΢΢������
	auto moveBy = new ActionMoveBy(0.4, Vector(0, 8));
	auto moveTwo = new ActionTwo(moveBy, moveBy->reverse());
	auto fly = new ActionLoop(moveTwo);
	fly->setName("С����趯��");
	return fly;
}

Action * CreateBirdRotate()
{
	// ������ת������С��׹��ʱ����̧ͷ�����ͷ��
	auto rotate = new ActionSequence(
		4,								// �� 3 ���������
		new ActionRotateTo(0.2, -15),	// 0.2 ������ת�� -15 ��
		new ActionDelay(0.2),			// �ȴ� 0.2 ��
		new ActionRotateTo(0.5, 90),	// 0.5 ������ת�� 90 �ȣ�С��ͷ���£�
		new ActionDelay(3)				// �ȴ� 3 �루��ֹ���������������Զ��ͷ��ڴ棩
	);
	rotate->setName("С����ת����");
	return rotate;
}

double RandomPipeHeight()
{
	// ���ˮ�ܸ߶�
	// ��Χ������Ļ������С���벻С�� 40 ����
	// ����Ļ�ײ���С���벻С�ڵ����Ϸ� 160 ����
	double landHeight = GetImage("����")->getHeight();
	double minHeight = 40;
	double maxHeight = Window::getHeight() - landHeight - 160;
	double height = Random::range(minHeight, maxHeight);
	return height;
}

Node * CreatePipe()
{
	// �����սڵ�
	auto pipe = new Node();

	// �������ˮ�ܸ߶�
	double height = RandomPipeHeight();
	pipe->setPosY(height);

	// ������ˮ��
	auto pipe1 = new Sprite(GetImage("ˮ��_��"));
	pipe1->setPivot(1, 1);

	// ������ˮ��
	auto pipe2 = new Sprite(GetImage("ˮ��_��"));
	pipe2->setPivot(1, 0);
	// ��ˮ������ˮ����� 120 ����
	pipe2->setPosY(120);

	// ������ˮ�����Ϊ�ӳ�Ա
	pipe->addChild(pipe1);
	pipe->addChild(pipe2);
	return pipe;
}

Node * CreatePipes()
{
	// �����սڵ�
	auto pipes = new Node();
	// ��������ˮ��
	auto pipe1 = CreatePipe();
	auto pipe2 = CreatePipe();
	auto pipe3 = CreatePipe();
	// ��һ��ˮ������Ļ��130���ش�
	pipe1->setPosX(Window::getWidth() + 130);
	// ����ˮ����ǰһ��ˮ�ܺ�200���ش�
	pipe2->setPosX(pipe1->getPosX() + 200);
	pipe3->setPosX(pipe2->getPosX() + 200);
	// ��ӵ��ڵ���
	pipes->addChild(pipe1);
	pipes->addChild(pipe2);
	pipes->addChild(pipe3);

	// �����ƶ�ˮ�ܵĺ���
	auto MoveFunc = [=]()
	{
		// �ƶ�����ˮ��
		for (auto pipe : pipes->getChildren())
		{
			pipe->movePos(-2, 0);
			// �ж�ˮ���Ƿ��ƶ�����Ļ��
			if (pipe->getPosX() <= 0)
			{
				// ��ˮ������Ļ�⣬���������ƶ�600����
				pipe->movePosX(600);
				// �������ˮ�ܸ߶�
				double height = RandomPipeHeight();
				// �޸�ˮ�ܸ߶�
				pipe->setPosY(height);
			}
		}
	};
	// ������ʱ��������������
	auto timer = new Timer("ˮ���ƶ���ʱ��");
	// ���ö�ʱ����ִ�к���Ϊ MoveFunc
	timer->setCallback(MoveFunc);

	return pipes;
}

void GetInput()
{
	// �������������¿ո��
	if (Input::isMouseLButtonPress() ||
		Input::isKeyPress(KeyCode::SPACE))
	{
		if (!g_Started)
		{
			// ����Ϸ��û�п�ʼ����ʼ��Ϸ
			StartGame();
		}
		// ��С����Ծ
		BirdJump();
	}
}

void StartGame()
{
	g_Started = true;

	// ����׼���ͽ̳�ͼƬ
	g_TextReady->runAction(new ActionFadeOut(0.4));
	g_TextTutorial->runAction(new ActionFadeOut(0.4));

	// ���� PlaySceneTimer �����Ļص�����
	TimerCallback tcb = PlaySceneTimer;
	// ������ʱ�����Զ�ִ�� PlaySceneTimer ����
	auto timer = new Timer("��Ϸ������ʱ��", tcb);
	timer->start();

	// ����ˮ���ƶ���ʱ��
	TimerManager::start("ˮ���ƶ���ʱ��");

	// ֹͣС����趯��
	g_Bird->stopAction("С����趯��");
	// ��ȡС���֡����
	auto animation = (Animation*)g_Bird->getAction("С��֡����");
	// ֡����ʱ��������Ϊ 0.05 �룬����С���ȶ������ٶ�
	animation->setInterval(0.05);
	// ������ת����
	auto rotate = CreateBirdRotate();
	// ִ����ת����
	g_Bird->runAction(rotate);
}

void BirdJump()
{
	if (!g_BirdDie)
	{
		// ���С�񻹻��ţ���С��һ�����ϵ��ٶ�
		g_BirdSpeed = -7.2;
		// ��ȡС�����ת����
		auto rotate = g_Bird->getAction("С����ת����");
		// ����ִ����ת����
		rotate->reset();
		// ������Ч
		MusicManager::play("res/sound/fly.wav");
	}
}

void PlaySceneTimer()
{
	// ģ��С������
	g_Bird->movePosY(g_BirdSpeed);
	// ģ��С����������
	g_BirdSpeed += 0.4;
	// ��С��������С�� 0���������������Ϸ�
	if (g_Bird->getPosY() < 0)
	{
		g_Bird->setPosY(0);
		g_BirdSpeed = 0;
	}
	// ���С���Ƿ�͵���ˮ�ܷ�����ײ
	if (IsBirdDie())
	{
		// ������ײ��С������
		BirdDie();
	}
	
	// �ж�С���Ƿ�ɹ���ˮ��
	for (auto pipe : g_Pipes->getChildren())
	{
		// ��ˮ���������ú�С��������ͬʱ���÷�
		if (pipe->getPosX() == g_Bird->getPosX())
		{
			// �ӷ�
			g_Score++;
			// �޸ĵ÷���ʾ
			g_TextScore->setText(String::toString(g_Score));
			// ������Ч
			MusicManager::play("res/sound/point.wav");
		}
	}
	// ��С��������С�ڵ��棬��Ϸ����
	if (Window::getHeight() - g_Bird->getPosY() <= 123)
	{
		// ��С��ֹͣ
		g_Bird->setPosY(Window::getHeight() - 123);
		g_Bird->stopAllActions();
		// ��С��������
		g_Bird->setRotation(90);
		// ��Ϸ����
		GameOver();
	}
}

bool IsBirdDie()
{
	// �ж�С��͵����Ƿ���ײ
	if (g_Bird->isIntersectWith(g_Ground))
	{
		return true;
	}
	// �ж�С���ˮ���Ƿ���ײ
	if (g_Bird->isIntersectWith(g_Pipes))
	{
		return true;
	}
	return false;
}

void BirdDie()
{
	// ��С���Ѿ�������ֱ�ӷ���
	if (g_BirdDie)
		return;

	// С������
	g_BirdDie = true;
	// ������Ч
	MusicManager::play("res/sound/hit.wav");

	// ��ȡ��ǰ����
	auto scene = SceneManager::getCurrentScene();
	// ���ص÷�
	g_TextScore->runAction(new ActionFadeOut(0.5));

	// ��������
	// ����һ����ɫ��ͼƬ
	auto white = new Sprite(GetImage("��ɫ"));
	white->setPivot(0, 0);
	// ͸��������Ϊ 0
	white->setOpacity(0);
	// ����Ŵ� 16 ��
	white->setScale(16);
	// ��ִ��һ�� 0.1 ��ĵ��붯������ִ��һ�� 0.1 ��ĵ�������
	white->runAction(new ActionTwo(new ActionFadeIn(0.1), new ActionFadeOut(0.1)));
	scene->add(white);

	// ֹͣˮ���ƶ���ʱ��
	TimerManager::clear("ˮ���ƶ���ʱ��");
	// �õ���ֹͣ�ƶ�
	// ��ʱ�����ƶ���ʱ������������һ���� Start �����У�
	// ���ڶ�����Ҳ���� Play �����еģ�ֹͣ
	TimerManager::get("�����ƶ���ʱ��")[1]->stopAndClear();
}

void GameOver()
{
	// ��־��Ϸ�Ѿ�����
	g_Started = false;
	// С������
	BirdDie();
	// ֹͣ��������
	Input::clearAll();
	// ֹͣ��Ϸ������ʱ��
	TimerManager::clear("��Ϸ������ʱ��");

	// ��ȡ��ǰ����
	auto scene = SceneManager::getCurrentScene();
	// ����һ���սڵ�
	auto layer = new Node();
	// ��ӵ�������
	scene->add(layer);

	// ��ʾ GameOver ͼƬ
	auto gameover = new Sprite(GetImage("�ı�_��Ϸ����"));
	gameover->setPivot(0.5, 0);
	gameover->setPosY(120);
	layer->addChild(gameover);

	// �����÷ְ�
	auto panel = CreatePanel();
	layer->addChild(panel);

	// ��ʾ���¿�ʼ��ť
	auto restartBtn1 = new Sprite(GetImage("��ť_���¿�ʼ"));
	auto restartBtn2 = new Sprite(GetImage("��ť_���¿�ʼ"));
	restartBtn2->setPosY(5);
	auto restartBtn = new Button(restartBtn1, restartBtn2);
	// �������¿�ʼ��ť��ִ�� ClickBtnRestart ����
	restartBtn->setCallback(ClickBtnRestart);
	restartBtn->setPosY(360);
	layer->addChild(restartBtn);

	// ��ʾ�������˵���ť
	auto menuBtn1 = new Sprite(GetImage("��ť_�˵�"));
	auto menuBtn2 = new Sprite(GetImage("��ť_�˵�"));
	menuBtn2->setPosY(5);
	auto menuBtn = new Button(menuBtn1, menuBtn2);
	// ���·������˵���ť��ִ�� ClickBtnMenu ����
	menuBtn->setCallback(ClickBtnMenu);
	menuBtn->setPosY(420);
	layer->addChild(menuBtn);

	// �������
	layer->setPosX(Window::getWidth() / 2);
	// ���ڵ������Ƶ���Ļ�·�
	layer->setPosY(Window::getHeight());

	// ���������������˶����ڵĸ߶�
	auto vec = Vector(0, -Window::getHeight());
	// λ�ƶ������õ÷����ӵײ��ƶ�����
	layer->runAction(new ActionMoveBy(1, vec));
}

Node * CreatePanel()
{
	// �����÷ְ�
	auto panel = new Sprite(GetImage("�÷ְ�"));
	panel->setPosY(Window::getHeight() / 2);

	// ��ȡ��߷�
	int bestScore = Data::getInt("��߷�", 0);

	// ������߷�
	if (g_Score > bestScore)
	{
		bestScore = g_Score;
		Data::saveInt("��߷�", bestScore);
		// ��� new ͼ��
		auto newImage = new Sprite(GetImage("�³ɼ�"));
		newImage->setPos(26, 23);
		panel->addChild(newImage);
	}

	// ��ӽ���
	auto modalFrame = GetModal(g_Score);
	if (modalFrame)
	{
		auto modal = new Sprite(modalFrame);
		modal->setPos(-65, 5);
		panel->addChild(modal);
	}

	// ��ʾ�÷�
	auto scoreImage = new Text("", "", 20, Color::BLACK);
	scoreImage->setText(String::toString(g_Score));
	scoreImage->setPivot(1, 0.5);
	scoreImage->setPos(91, -20);
	panel->addChild(scoreImage);

	// ��ʾ��߷�
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
	else if (score >= 10 && score < 20) return GetImage("ͭ��");
	else if (score >= 20 && score < 30) return GetImage("����");
	else if (score >= 30 && score < 50) return GetImage("����");
	else return GetImage("������");
}

void ClickBtnStart()
{
	// ���Ű�ť��Ч
	MusicManager::play("res/sound/click.wav");
	// ִ�� EnterPlay ����
	EnterPlay();
}

void ClickBtnRestart()
{
	// ���Ű�ť��Ч
	MusicManager::play("res/sound/click.wav");
	// �����µ� Play ����
	auto scene = CreatePlay();
	// �л�����
	SceneManager::enter(scene, new TransitionFade(0.3, 0.3), false);
}

void ClickBtnMenu()
{
	// ���Ű�ť��Ч
	MusicManager::play("res/sound/click.wav");
	// ���� Start ����
	SceneManager::back(new TransitionFade(0.3, 0.3));
}