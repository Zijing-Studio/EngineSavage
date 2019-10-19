#pragma once
#include"SavageCoordinate.h"

class GameMap
{
	int width, height, originx, originy;
	int* map_info;
public:
	GameMap();
	~GameMap();
	void Init(string strMapFilePath = "");
	int BlockType(Pos position) const;
	void Print() const;
};