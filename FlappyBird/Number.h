#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "common.h"


// ������
// ��ʾ�÷�ʱ�����ڽ� int ������ת��ΪͼƬ����
class Number :
	public Node
{
public:
	Number();

	int getNumber();					// ��ȡ�����������
	void setNumber(int number);			// �� int ת��ΪͼƬ����
	void setLittleNumber(int number);	// �� int ת��ΪͼƬ��С��

protected:
	int number;
};
