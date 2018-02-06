#include "Pipe.h"
#include "ResLoader.h"


Pipe::Pipe()
{
	scored = false;

	// ���ˮ�ܸ߶�
	// ��Χ������Ļ������С���벻С�� 100 ����
	// ����Ļ�ײ���С���벻С�ڵ����Ϸ� 100 ����
	float landHeight = ResLoader::getImage(L"land")->getHeight();
	float height = ERandom::range(100, EWindow::getHeight() - landHeight - 100);
	
	// ������ˮ��
	auto pipe1 = new ESprite(ResLoader::getImage(L"pipe_above"));
	pipe1->setPivot(1, 1);
	pipe1->setPosY(height - 60);

	// ����ˮ����״
	// ����������ײ���������ԭ��ο� Bird.cpp
	auto rt1 = new ERectangle(pipe1);
	rt1->setCategoryBitmask(PIPE_BITMASK);
	rt1->setCollisionBitmask(BIRD_BITMASK);
	pipe1->setShape(rt1);

	// ������ˮ��
	auto pipe2 = new ESprite(ResLoader::getImage(L"pipe_below"));
	pipe2->setPivot(1, 0);
	pipe2->setPosY(height + 60);

	// ����ˮ����״
	auto rt2 = new ERectangle(pipe2);
	rt2->setCategoryBitmask(PIPE_BITMASK);
	rt2->setCollisionBitmask(BIRD_BITMASK);
	pipe2->setShape(rt2);

	// ������ˮ�����Ϊ�ӳ�Ա
	this->addChild(pipe1);
	this->addChild(pipe2);
}


Pipe::~Pipe()
{
}
