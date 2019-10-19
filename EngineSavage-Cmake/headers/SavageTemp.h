#pragma once
#include"Loong.h"

#define GAME_TEMP_TYPE_ARTIFACT 1
#define GAME_TEMP_TYPE_CHARACTER 2
#define GAME_TEMP_TYPE_BUILDING 3

void LoadCode(const char* filepath, LoongCode** ppCode);

class GameUnitTemp
{
public:
	int temp_type = 0;
	int health = 0;
	int attack = 0;
	int attack_range_near = 0;
	int attack_range_far = 0;
	int move_range = 0;
	int status = 0;
	int height = 0;
	LoongCode* trigger_gamestart = NULL;		//Activate when game starts.
	LoongCode* trigger_roundstart = NULL;		//Activate when a round starts.
	LoongCode* trigger_roundend = NULL;		//Activate when a round ends.
	LoongCode* trigger_cast = NULL;			//Activate when using a card.
	LoongCode* trigger_summon = NULL;			//Activate when summoning something.
	LoongCode* trigger_attack = NULL;			//Activate when an attack event happens.
	LoongCode* trigger_move = NULL;			//Activate when a move event happens.
	LoongCode* trigger_heal = NULL;			//Activate when a healing event happens.
	LoongCode* trigger_damage = NULL;			//Activate when a damage event happens.
	LoongCode* trigger_death = NULL;			//Activate when a unit is dying.
	LoongCode* trigger_halo = NULL;			//Affact summary calculation.
	GameUnitTemp();
	GameUnitTemp(const GameUnitTemp& temp);
	~GameUnitTemp();
	void LoadFromFile(const char* filepath);
	void Print() const;
};