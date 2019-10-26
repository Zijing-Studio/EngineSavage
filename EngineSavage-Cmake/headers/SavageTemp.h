#pragma once
#include"Loong.h"

#include<fstream>

#define GAME_TEMP_TYPE_ARTIFACT 1
#define GAME_TEMP_TYPE_CHARACTER 2
#define GAME_TEMP_TYPE_BUILDING 3
using namespace std;

void LoadCode(const char* filepath, LoongCode** ppCode);

class GameUnitTemp
{
public:
	int cold_down = 0;
	int mana_cost = 0;
	int health = 0;
	int attack = 0;
	int attack_range_near = 0;
	int attack_range_far = 0;
	int move_range = 0;
	int status = 0;
	int height = 0;
	map<string, LoongCode> trigger;
	GameUnitTemp();
	~GameUnitTemp();
	void Print() const;
};

class GameTemp
{
public:
	string temp_name="";
	int capacity = 0;
	GameUnitTemp unit_temp[3];
	void Print() const;
};

int LoadTemplate(const string filepath, GameUnitTemp* pTemp);

int LoadTemplate(const string filepath, GameTemp* pTemp);

