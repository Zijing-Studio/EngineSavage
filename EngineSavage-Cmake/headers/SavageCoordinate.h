#pragma once
#include"SavageHeaders.h"
#include"SavageLog.h"

struct Pos
{
public:
	int x, y, z;
	Pos();
	Pos(int _x, int _y, int _z);
	Pos EliminateX() const;//返回一个和当前坐标表示位置相同，消除了X值的坐标
	Pos EliminateY() const;//返回一个和当前坐标表示位置相同，消除了Y值的坐标
	Pos EliminateZ() const;//返回一个和当前坐标表示位置相同，消除了Z值的坐标
	Pos Balance() const;//返回一个中间值被置0后的坐标
	int Length() const;//返回从(0,0,0)到当前坐标的最小步数
	Pos operator + (const Pos& p) const;//返回两个坐标的向量和
	Pos operator - (const Pos& p) const;//返回两个坐标的向量差
	Pos operator * (const int& d) const;//返回坐标向量和整数d的乘积
	void Print() const;//输出当前坐标到SavageLog
	bool operator == (const Pos& b) const;
	bool iszero() const;
};