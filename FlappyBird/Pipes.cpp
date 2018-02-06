#include "Pipes.h"
#include "ResLoader.h"


Pipes::Pipes()
{
	number = 0;
	// �������ˮ��
	addPipe();
	addPipe();
	addPipe();
	// �ر� onUpdate ����
	this->setAutoUpdate(false);
}


Pipes::~Pipes()
{
}

void Pipes::onUpdate()
{
	// �ƶ�����ˮ��
	for (int i = 0; i < number; i++) 
	{
		pipes[i]->movePos(-2, 0);
	}
	// �ж���ǰ���ˮ���Ƿ��ƶ�����Ļ��
	if (pipes[0]->getPosX() <= 0) 
	{
		// ����һ��ˮ������Ļ�⣬ɾ�����ˮ��
		this->removeChild(pipes[0]);
		// ��ԭ���±�Ϊ 1��2 ��ˮ��λ����ǰ
		pipes[0] = pipes[1];
		pipes[1] = pipes[2];
		// ˮ��������һ
		number--;
		// ���һ����ˮ��
		addPipe();
	}
}

void Pipes::addPipe()
{
	// ˮ���������Ϊ 3
	if (number >= 3) 
		return;
	
	// ����ˮ��
	auto pipe = new Pipe();
	// ����ˮ�ܺ�����
	if (number == 0) {
		// ��һ��ˮ������Ļ��130���ش�
		pipe->setPosX(EWindow::getWidth() + 130);
	}
	else {
		// ����ˮ����ǰһ��ˮ�ܺ�200���ش�
		pipe->setPosX(pipes[number - 1]->getPosX() + 200);
	}
	// ���� pipe ��ָ��
	pipes[number] = pipe;
	// ˮ��������һ
	number++;

	this->addChild(pipe);
}

void Pipes::start()
{
	// �� onUpdate ����
	this->setAutoUpdate(true);
}

void Pipes::stop()
{
	// �ر� onUpdate ����
	this->setAutoUpdate(false);
}
