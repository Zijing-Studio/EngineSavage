#include "SavageCoordinate.h"

Pos::Pos()
{
	x = 0; y = 0; z = 0;
}

Pos::Pos(int _x, int _y, int _z)
{
	x = _x; y = _y; z = _z;
}

Pos Pos::EliminateX() const
{
	return Pos(0, y - x, z - x);
}

Pos Pos::EliminateY() const
{
	return Pos(x - y, 0, z - y);
}

Pos Pos::EliminateZ() const
{
	return Pos(x - z, y - z, 0);
}

Pos Pos::Balance() const
{
	int t = x + y + z - max(x, max(y, z)) - min(x, min(y, z));
	return Pos(x - t, y - t, z - t);
}

int Pos::Length() const
{
	return max(x, max(y, z)) - min(x, min(y, z));
}

Pos Pos::operator+(const Pos& p) const
{
	return Pos(x + p.x, y + p.y, z + p.z).Balance();
}

Pos Pos::operator-(const Pos& p) const
{
	return Pos(x - p.x, y - p.y, z - p.z).Balance();
}

Pos Pos::operator*(const int& d) const
{
	return Pos(x * d, y * d, z * d).Balance();
}

void Pos::Print() const
{
	SavageLog("(%d,%d,%d)", x, y, z);
}

bool Pos::operator==(const Pos& b) const
{
	Pos p0 = EliminateZ(), p1 = b.EliminateZ();
	return p0.x == p1.x && p0.y == p1.y;
}

bool Pos::iszero() const
{
	return !x && !y && !z;
}
