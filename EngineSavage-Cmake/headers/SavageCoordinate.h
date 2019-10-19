#pragma once
#include"SavageHeaders.h"
#include"SavageLog.h"

struct Pos
{
public:
	int x, y, z;
	Pos();
	Pos(int _x, int _y, int _z);
	Pos EliminateX() const;//����һ���͵�ǰ�����ʾλ����ͬ��������Xֵ������
	Pos EliminateY() const;//����һ���͵�ǰ�����ʾλ����ͬ��������Yֵ������
	Pos EliminateZ() const;//����һ���͵�ǰ�����ʾλ����ͬ��������Zֵ������
	Pos Balance() const;//����һ���м�ֵ����0�������
	int Length() const;//���ش�(0,0,0)����ǰ�������С����
	Pos operator + (const Pos& p) const;//�������������������
	Pos operator - (const Pos& p) const;//�������������������
	Pos operator * (const int& d) const;//������������������d�ĳ˻�
	void Print() const;//�����ǰ���굽SavageLog
	bool operator == (const Pos& b) const;
	bool iszero() const;
};