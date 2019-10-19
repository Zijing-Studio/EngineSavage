#include "SavageMap.h"

GameMap::GameMap()
{
	width = height = originx = originy = 0;
	map_info = NULL;
}

GameMap::~GameMap()
{
	if (map_info)delete[]map_info;
}

void GameMap::Init(string strMapFilePath)
{
	FILE* mapfile;
#ifdef _MSC_VER
	fopen_s(&mapfile, strMapFilePath.c_str(), "r");
#else
	mapfile = fopen(strMapFilePath.c_str(), "r");
#endif // _MSC_VER
	if (!mapfile)return;
	bool res = 1;
	res = res && fscanf(mapfile, "%d%d%d%d", &width, &height, &originx, &originy);
	if (res)
	{
		if (map_info)delete[]map_info;
		map_info = new int[1ll * width * height];
		char* line = new char[1ll + width];
		for (int i = 0; i < height; i++)
		{
			res = res && fscanf(mapfile, "%s", line);
			for (int j = 0; j < width; j++)
			{
				map_info[1ll * i * width + j] = line[j] - '0';
			}
		}
		delete[]line;
	}
	fclose(mapfile);
}

int GameMap::BlockType(Pos position) const
{
	int x = position.EliminateZ().x, y = position.EliminateZ().y;
	x += originx;
	y += originy;
	if (x < 0 || x >= width)return 0;
	if (y < 0 || y >= height)return 0;
	return map_info[y * width + x];
}

void GameMap::Print() const
{
	SavageLog("Printing Map.\nwidth:%d height:%d originx:%d originy:%d\n", width, height, originx, originy);
	for (int x = 0; x < width; x++)SavageLog("-"); SavageLog("\n");
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			SavageLog("%d", map_info[x + y * width]);
		}
		SavageLog("\n");
	}
	for (int x = 0; x < width; x++)SavageLog("-"); SavageLog("\n");
}
