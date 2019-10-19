#pragma once
#include"SavageUnit.h"
#include"SavageMap.h"
#include"SavageTemp.h"
#include"Loong.h"

#define MAX_UNIT (1024*1024)

#define DAMAGE_TYPE_ATTACK 1
#define DAMAGE_TYPE_NORMAL 2

IContent MakePos(IContent var);
IContent Print(IContent var);
IContent Max(IContent var);
IContent Min(IContent var);

class GameWorld
{
public:
	GameMap gamemap;
	map<string, ILoongFunction> funcspace;
	vector<GameUnitTemp> temps;
	GameUnit units[MAX_UNIT]; int unit_cnt;
	
	GameWorld();
	void LoadTemp(const char* filepath);

	GameUnit CreateUnitFromTemp(int tempid) const;
	void Summon(GameUnit unit, int from_id);
	
	void Move(int uid, Pos targ);
	void Attack(int targid, int fromid);
	void Damage(int targid, int fromid, int damage, int type);
	void Kill(int uid);
	void Bless(int uid, int health, int attack);
	void Print() const;

	void Refresh();
};

IContent Summon(IContent var);
IContent Move(IContent var);
IContent Attack(IContent var);
IContent Damage(IContent var);
IContent Kill(IContent var);
IContent Bless(IContent var);
IContent QueryUnit(IContent var);
IContent UnitCount(IContent var);

void ActivateWorld(GameWorld* pWorld);