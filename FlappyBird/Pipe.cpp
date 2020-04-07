#include "Pipe.h"
#include "ResLoader.h"


Pipe::Pipe()
{
	scored = false;

	// ���ˮ�ܸ߶�
	// ��Χ������Ļ������С���벻С�� 100 ����
	// ����Ļ�ײ���С���벻С�ڵ����Ϸ� 100 ����
	float landHeight = ResLoader::getImage(L"land")->getHeight();
	float height = Random::range(100, Window::getHeight() - landHeight - 100);

	// ������ˮ��
	auto pipe1 = gcnew Sprite(ResLoader::getImage(L"pipe_above"));
	pipe1->setAnchor(1, 1);
	pipe1->setPosY(height - 60);

	// ������ˮ��
	auto pipe2 = gcnew Sprite(ResLoader::getImage(L"pipe_below"));
	pipe2->setAnchor(1, 0);
	pipe2->setPosY(height + 60);

	// ������ˮ�����Ϊ�ӳ�Ա
	this->addChild(pipe1);
	this->addChild(pipe2);
}


Pipe::~Pipe()
{
}
