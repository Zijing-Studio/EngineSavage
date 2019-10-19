#pragma once
#include"SavageCoordinate.h"
#include"Loong.h"

#define UNIT_STATUS_SLEEP 1
#define UNIT_STATUS_DEAD 2
#define UNIT_STATUS_MOVED 4
#define UNIT_STATUS_STEALTH 8
#define UNIT_STATUS_FROZEN 16

class GameUnitModel
{
public:
	int pid;
	int unit_type;
	int health;
	int health_limit;
	int attack;
	int attack_range_near;
	int attack_range_far;
	int move_range;
	int status;
	Pos pos;
	int height;
	void Print() const;
};

class GameUnit
{
public:
	int pid;
	int unit_type;
	int health;
	int health_limit;
	int health_buff;
	int attack;
	int attack_buff;
	int attack_range_near;
	int attack_range_near_buff;
	int attack_range_far;
	int attack_range_far_buff;
	int move_range;
	int move_range_buff;
	int status;
	Pos pos;
	int height;
	GameUnitModel GetUnitModel() const;
};