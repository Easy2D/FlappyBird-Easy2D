#include "GameOverLayer.h"
#include "GameScene.h"
#include "ImageLoader.h"


GameOverLayer::GameOverLayer(int score)
{
	// ��ʾ GameOver ͼƬ
	auto gameover = ImageLoader::getImage(_T("text_game_over"));
	gameover->setWindowCenterX();
	gameover->setY(120);
	// ��ʾ�÷ְ�
	auto panel = ImageLoader::getImage(_T("score_panel"));
	panel->setWindowCenter();
	// ��ʾ���¿�ʼ��ť
	auto restart = new ImageButton(ImageLoader::getImage(_T("button_restart")));
	restart->setWindowCenterX();
	restart->setY(330);
	restart->setClickedCallback([] {
		// �������¿�ʼ������һ���µ� GameScene
		App::enterScene(new GameScene(), false);
	});
	// ��ť����ʱ�������ƶ�5����
	restart->setSelectCallback([=] {
		restart->move(0, 5);
	});
	restart->setUnselectCallback([=] {
		restart->move(0, -5);
	});
	// ��ʾ�������˵���ť
	auto menu = new ImageButton(ImageLoader::getImage(_T("button_menu")));
	menu->setWindowCenterX();
	menu->setY(400);
	menu->setClickedCallback([] {
		// ���·������˵���������һ������
		App::backScene();
	});
	// ��ť����ʱ�������ƶ�5����
	menu->setSelectCallback([=] {
		menu->move(0, 5);
	});
	menu->setUnselectCallback([=] {
		menu->move(0, -5);
	});
	// ��ʾ���Ӱ�ť
	auto share = new ImageButton(ImageLoader::getImage(_T("button_share")));
	share->setWindowCenterX();
	share->setY(435);
	share->setClickedCallback([] {
		//MusicUtils::playMusic(_T("res/sound/MenuClick.mp3"));
		ShellExecute(NULL, _T("open"), _T("https://gitee.com/werelone/FlappyBird"), NULL, NULL, SW_SHOWNORMAL);
	});
	// ��ť����ʱ�������ƶ�5����
	share->setSelectCallback([=] {
		share->move(0, 5);
	});
	share->setUnselectCallback([=] {
		share->move(0, -5);
	});
	// �ϲ�Ϊһ���ڵ�
	auto all = new BatchNode();
	all->add(gameover);
	all->add(panel);
	all->add(restart);
	all->add(menu);
	all->add(share);
	this->add(all);
	// ���ڵ������Ƶ���Ļ�·�
	all->setY(App::getHeight());
	// ��Timerʵ�ּ򵥵��ƶ�����
	Timer::addTimer(_T("game_over"), [=] {
		if (all->getY() > 0) {
			all->move(0, -8);
		}
		else {
			// ������������ʾ�÷�
			showScore();
			Timer::stopTimer(_T("game_over"));
		}
	});
	
	// ��ȡ�÷ֺ���߷�
	this->score = score;
	this->bestScore = FileUtils::getInt(_T("best_score"), 0);
	// ������߷�
	if (score >= bestScore) {
		FileUtils::saveInt(_T("best_score"), score);
		bestScore = score;
		// ��� new ͼ��
		auto newImage = ImageLoader::getImage(_T("new"));
		newImage->setPos(155, 269);
		all->add(newImage);
	}
	// ��ӽ���
	auto modal = getModal();
	if (modal) {
		modal->setPos(57, 237);
		all->add(modal);
		// �������
		auto blink = new Sprite(ImageLoader::getImage(_T("blink_00")));
		// ����֡����
		auto frames = new ActionFrames(130);
		frames->addFrame(ImageLoader::getImage(_T("blink_00")));
		frames->addFrame(ImageLoader::getImage(_T("blink_01")));
		frames->addFrame(ImageLoader::getImage(_T("blink_02")));
		frames->addFrame(ImageLoader::getImage(_T("blink_01")));
		frames->addFrame(ImageLoader::getImage(_T("blink_00")));
		// ִ��֡����ǰ����������λ��
		auto action = new ActionTwo(new ActionCallback([=] {
			int x = random(modal->getX(), modal->getX() + modal->getWidth());
			int y = random(modal->getY(), modal->getY() + modal->getHeight());
			blink->setPos(x, y);
		}), frames);
		// ִ��ѭ������
		blink->runAction(new ActionNeverStop(action));
		all->add(blink);
	}
	// ��ʾ�÷�
	scoreImage = new Number();
	scoreImage->setDisplay(false);
	scoreImage->setPos(235, 228);
	scoreImage->setLittleNumber(0);
	this->add(scoreImage);
	// ��ʾ��߷�
	bestScoreImage = new Number();
	bestScoreImage->setDisplay(false);
	bestScoreImage->setPos(235, 269);
	bestScoreImage->setLittleNumber(bestScore);
	this->add(bestScoreImage);
	// ������Ч
	//MusicUtils::playMusic(_T("res/sound/swoosh.mp3"));
}


GameOverLayer::~GameOverLayer()
{
}

void GameOverLayer::showScore()
{
	// ��ʾ�÷֡���߷ֺͽ���
	scoreImage->setDisplay(true);
	bestScoreImage->setDisplay(true);
	// �����л����ֵ�ʱ�������1200������ʾ�궯��
	UINT delay = (score > 12) ? UINT(1200.0f / score) : 100;
	// �÷ֶ���
	Timer::addTimer(_T("show_score"), delay, [=] {
		if (scoreImage->getNumber() < score) {
			// �л�һ������
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
		return ImageLoader::getImage(_T("medals_0"));	// ͭ��
	}
	else if (score >= 20 && score < 30) {
		return ImageLoader::getImage(_T("medals_1"));	// ����
	}
	else if (score >= 30 && score < 50) {
		return ImageLoader::getImage(_T("medals_2"));	// ����
	}
	else {
		return ImageLoader::getImage(_T("medals_3"));	// ��ʯ����
	}
}
