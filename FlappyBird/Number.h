#pragma once
#include <easy2d.h>


// ������
// ��ʾ�÷�ʱ�����ڽ� int ������ת��ΪͼƬ����
class Number :
	public ENode
{
public:
	Number();

	int getNumber();					// ��ȡ�����������
	void setNumber(int number);			// �� int ת��ΪͼƬ����
	void setLittleNumber(int number);	// �� int ת��ΪͼƬ��С��

protected:
	int number;
};

