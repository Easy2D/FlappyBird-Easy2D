#include "Pipes.h"
#include "ResLoader.h"


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
	auto timer = new ETimer([=](int) {
		// �ƶ�����ˮ��
		for (int i = 0; i < number; i++) {
			pipes[i][0]->movePos(-2, 0);
			pipes[i][1]->movePos(-2, 0);
		}
		if (pipes[0][0]->getPosX() <= -pipes[0][0]->getWidth()) {
			// ����һ��ˮ�ܳ��磬ɾ�����ˮ��
			this->removeChild(pipes[0][0]);
			this->removeChild(pipes[0][1]);
			// �ͷ�ˮ��ռ�õ���Դ
			pipes[0][0]->removeFromParent();
			pipes[0][1]->removeFromParent();
			// �ƶ�������ָ���λ��
			pipes[0][0] = pipes[1][0]; pipes[0][1] = pipes[1][1];
			pipes[1][0] = pipes[2][0]; pipes[1][1] = pipes[2][1];
			// ˮ��������һ
			number--;
			// ���һ����ˮ��
			addPipe();
		}
	});
	timer->bindWith(this);
}

void Pipes::stop()
{
	ETimerManager::stopAllTimersBindedWith(this);
}

void Pipes::addPipe()
{
	// ˮ���������Ϊ 3
	if (this->number == 3) return;
	// ���ˮ��λ��
	float pipeY = ERandom::between(100, EApp::getHeight() - ResLoader::getImage(L"land")->getHeight() - 100);
	// ������ˮ��
	auto pipe1 = new ESprite(ResLoader::getImage(L"pipe_above"));
	pipe1->setPivot(0.5f, 1);
	pipe1->setPosY(pipeY - 60);
	this->addChild(pipe1);
	// Ϊ��ˮ������������
	auto rt1 = new ERectangle(pipe1);
	rt1->setCategoryBitmask(0x0100);
	rt1->setCollisionBitmask(0x0001);
	pipe1->setGeometry(rt1);
	// ������ˮ��
	auto pipe2 = new ESprite(ResLoader::getImage(L"pipe_below"));
	pipe2->setPivot(0.5f, 0);
	pipe2->setPosY(pipeY + 60);
	this->addChild(pipe2);
	// Ϊ��ˮ������������
	auto rt2 = new ERectangle(pipe2);
	rt2->setCategoryBitmask(0x0100);
	rt2->setCollisionBitmask(0x0001);
	pipe2->setGeometry(rt2);
	// ����ˮ�ܺ�����
	if (number == 0) {
		// ��һ��ˮ������Ļ��130���ش�
		pipe1->setPosX(EApp::getWidth() + 130);
		pipe2->setPosX(EApp::getWidth() + 130);
	}
	else {
		// ����ˮ����ǰһ��ˮ�ܺ�200���ش�
		pipe1->setPosX(pipes[number - 1][0]->getPosX() + 200);
		pipe2->setPosX(pipes[number - 1][1]->getPosX() + 200);
	}
	// ���浽����
	pipes[number][0] = pipe1;
	pipes[number][1] = pipe2;
	// ˮ��������һ
	number++;
}
