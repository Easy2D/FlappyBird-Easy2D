#include "Pipes.h"
#include "ImageLoader.h"


Pipes::Pipes()
{
	// 添加三根水管
	addPipe();
	addPipe();
	addPipe();
}


Pipes::~Pipes()
{
}

void Pipes::start()
{
	Timer::addTimer(_T("pipes_move"), [=] {
		// 移动所有水管
		for (int i = 0; i < number; i++) {
			pipes[i][0]->move(-2, 0);
			pipes[i][1]->move(-2, 0);
		}
		if (pipes[0][0]->getX() <= -pipes[0][0]->getWidth()) {
			// 若第一个水管出界，删除这个水管
			this->delSprite(pipes[0][0]);
			this->delSprite(pipes[0][1]);
			// 释放水管占用的资源
			pipes[0][0]->autoRelease();
			pipes[0][1]->autoRelease();
			// 移动数组中指针的位置
			pipes[0][0] = pipes[1][0]; pipes[0][1] = pipes[1][1];
			pipes[1][0] = pipes[2][0]; pipes[1][1] = pipes[2][1];
			// 水管数量减一
			number--;
			// 添加一个新水管
			addPipe();
		}
	});
}

void Pipes::stop()
{
	Timer::stopTimer(_T("pipes_move"));
}

void Pipes::addPipe()
{
	// 水管最大数量为 3
	if (this->number == 3) return;
	// 随机水管位置
	int pipeY = random(112, (App::getHeight() - 112) / 2 + 90);
	// 创建上水管
	auto pipe1 = new Sprite(ImageLoader::getImage(_T("pipe_above")));
	pipe1->setY(pipeY - 60 - pipe1->getHeight());
	this->addSprite(pipe1);
	// 创建下水管
	auto pipe2 = new Sprite(ImageLoader::getImage(_T("pipe_below")));
	pipe2->setY(pipeY + 60);
	this->addSprite(pipe2);
	// 设置水管横坐标
	if (number == 0) {
		// 第一个水管在屏幕外130像素处
		pipe1->setX(App::getWidth() + 130);
		pipe2->setX(App::getWidth() + 130);
	}
	else {
		// 其他水管在前一个水管后方200像素处
		pipe1->setX(pipes[number - 1][0]->getX() + 200);
		pipe2->setX(pipes[number - 1][1]->getX() + 200);
	}
	// 保存到数组
	pipes[number][0] = pipe1;
	pipes[number][1] = pipe2;
	// 水管数量加一
	number++;
}
