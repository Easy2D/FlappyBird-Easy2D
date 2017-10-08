#include "Pipes.h"
#include "ImageLoader.h"


Pipes::Pipes()
{
	// �������ˮ��
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
		// �ƶ�����ˮ��
		for (int i = 0; i < number; i++) {
			pipes[i][0]->move(-2, 0);
			pipes[i][1]->move(-2, 0);
		}
		if (pipes[0][0]->getX() <= -pipes[0][0]->getWidth()) {
			// ����һ��ˮ�ܳ��磬ɾ�����ˮ��
			this->delSprite(pipes[0][0]);
			this->delSprite(pipes[0][1]);
			// �ͷ�ˮ��ռ�õ���Դ
			pipes[0][0]->autoRelease();
			pipes[0][1]->autoRelease();
			// �ƶ�������ָ���λ��
			pipes[0][0] = pipes[1][0]; pipes[0][1] = pipes[1][1];
			pipes[1][0] = pipes[2][0]; pipes[1][1] = pipes[2][1];
			// ˮ��������һ
			number--;
			// ���һ����ˮ��
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
	// ˮ���������Ϊ 3
	if (this->number == 3) return;
	// ���ˮ��λ��
	int pipeY = random(112, (App::getHeight() - 112) / 2 + 90);
	// ������ˮ��
	auto pipe1 = new Sprite(ImageLoader::getImage(_T("pipe_above")));
	pipe1->setY(pipeY - 60 - pipe1->getHeight());
	this->addSprite(pipe1);
	// ������ˮ��
	auto pipe2 = new Sprite(ImageLoader::getImage(_T("pipe_below")));
	pipe2->setY(pipeY + 60);
	this->addSprite(pipe2);
	// ����ˮ�ܺ�����
	if (number == 0) {
		// ��һ��ˮ������Ļ��130���ش�
		pipe1->setX(App::getWidth() + 130);
		pipe2->setX(App::getWidth() + 130);
	}
	else {
		// ����ˮ����ǰһ��ˮ�ܺ�200���ش�
		pipe1->setX(pipes[number - 1][0]->getX() + 200);
		pipe2->setX(pipes[number - 1][1]->getX() + 200);
	}
	// ���浽����
	pipes[number][0] = pipe1;
	pipes[number][1] = pipe2;
	// ˮ��������һ
	number++;
}
