#include "SavageWorld.h"

GameWorld* g_pWorld;

GameWorld::GameWorld()
{
	funcspace["pos"] = ::MakePos;
	funcspace["print"] = ::Print;
	funcspace["max"] = ::Max;
	funcspace["min"] = ::Min;
	funcspace["Summon"] = ::Summon;
	funcspace["Move"] = ::Move;
	funcspace["Attack"] = ::Attack;
	funcspace["Damage"] = ::Damage;
	funcspace["Bless"] = ::Bless;
	funcspace["Kill"] = ::Kill;
	funcspace["Unit"] = ::QueryUnit;
	funcspace["UnitCount"] = ::UnitCount;
	memset(units, 0, sizeof units);
	unit_cnt = 1;
}

void GameWorld::LoadTemp(const char* filepath)
{
	temps.push_back(GameUnitTemp());
	temps[temps.size() - 1].LoadFromFile(filepath);
}

GameUnit GameWorld::CreateUnitFromTemp(int tempid) const
{
	GameUnit unit;
	unit.pid = 0;
	unit.unit_type = tempid;
	unit.health = temps[tempid].health;
	unit.health_limit = temps[tempid].health;
	unit.health_buff = 0;
	unit.attack = temps[tempid].attack;
	unit.attack_buff = 0;
	unit.attack_range_near = temps[tempid].attack_range_near;
	unit.attack_range_near_buff = 0;
	unit.attack_range_far = temps[tempid].attack_range_far;
	unit.attack_range_far_buff = 0;
	unit.move_range = temps[tempid].move_range;
	unit.move_range_buff = 0;
	unit.status = temps[tempid].status | UNIT_STATUS_SLEEP;
	unit.pos = Pos();
	unit.height = temps[tempid].height;
	return unit;
}

void GameWorld::Summon(GameUnit unit, int from_id)
{
	units[unit_cnt++] = unit;
	for (int i = 1; i < unit_cnt; i++)
	{
		if (!(units[i].status & UNIT_STATUS_DEAD) && temps[units[i].unit_type].trigger_summon)
		{
			map<string, IContent> contentspace;
			contentspace["fromid"].assign(from_id);
			contentspace["id"].assign(i);
			contentspace["uid"].assign(unit_cnt - 1);
			IContent res;
			res = LoongExecuter(*temps[units[i].unit_type].trigger_summon, funcspace, contentspace);
		}
	}
}

IContent Summon(IContent var)
{
	IContent unit_var;
	unit_var.assign(var[0]);
	GameUnit unit;
	unit.pid = unit_var["pid"].to_int();
	unit.unit_type = unit_var["unittype"].to_int();
	unit.health = unit_var["health"].to_int();
	unit.health_limit = unit_var["healthlimit"].to_int();
	unit.health_buff = 0;
	unit.attack = unit_var["attack"].to_int();
	unit.attack_buff = 0;
	unit.attack_range_near = unit_var["attackrangenear"].to_int();
	unit.attack_range_near_buff = 0;
	unit.attack_range_far = unit_var["attackrangefar"].to_int();
	unit.attack_range_far_buff = 0;
	unit.move_range = unit_var["moverange"].to_int();
	unit.move_range_buff = 0;
	unit.status = unit_var["status"].to_int();
	unit.pos = unit_var["pos"].to_pos();
	unit.height = unit_var["height"].to_int();
	g_pWorld->Summon(unit, var[1].to_int());
	return IContent();
}

IContent Move(IContent var)
{
	g_pWorld->Move(var[0].to_int(), var[1].to_pos());
	return IContent();
}

IContent Attack(IContent var)
{
	g_pWorld->Attack(var[0].to_int(), var[1].to_int());
	return IContent();
}

IContent Damage(IContent var)
{
	g_pWorld->Damage(var[0].to_int(), var[1].to_int(), var[2].to_int(), var[3].to_int());
	return IContent();
}

IContent Kill(IContent var)
{
	g_pWorld->Kill(var.to_int());
	return IContent();
}

IContent Bless(IContent var)
{
	g_pWorld->Bless(var[0].to_int(), var[1].to_int(), var[2].to_int());
	return IContent();
}

IContent QueryUnit(IContent var)
{
	GameUnitModel unit = g_pWorld->units[var.to_int()].GetUnitModel();
	IContent res;
	res["pid"].assign(unit.pid);
	res["unittype"].assign(unit.unit_type);
	res["health"].assign(unit.health);
	res["healthlimit"].assign(unit.health_limit);
	res["attack"].assign(unit.attack);
	res["attackrangenear"].assign(unit.attack_range_near);
	res["attackrangefar"].assign(unit.attack_range_far);
	res["moverange"].assign(unit.move_range);
	res["status"].assign(unit.status);
	res["pos"].assign(unit.pos);
	res["height"].assign(unit.height);
	return res;
}

IContent UnitCount(IContent var)
{
	return g_pWorld->unit_cnt - 1;
}

void GameWorld::Move(int uid, Pos targ)
{
	GameUnit &unit = units[uid];
	map<pair<int, int>, bool> vis;
	struct State
	{
		int x, y, d;
		State(int _x = 0, int _y = 0, int _d = 0) { x = _x; y = _y; d = _d; }
	};
	queue<State> Q;
	bool reached = 0;
	if (0 < unit.move_range + unit.move_range_buff)
	{
		Pos start = unit.pos.EliminateZ();
		State nst;
		nst = State(start.x, start.y, 1);
		nst.x++;
		Q.push(nst);
		nst = State(start.x, start.y, 1);
		nst.x--;
		Q.push(nst);
		nst = State(start.x, start.y, 1);
		nst.y++;
		Q.push(nst);
		nst = State(start.x, start.y, 1);
		nst.y--;
		Q.push(nst);
		nst = State(start.x, start.y, 1);
		nst.x++; nst.y++;
		Q.push(nst);
		nst = State(start.x, start.y, 1);
		nst.x--; nst.y--;
		Q.push(nst);
	}
	while (!Q.empty())
	{
		State st = Q.front(); Q.pop();
		if (vis[make_pair(st.x, st.y)])continue;
		vis[make_pair(st.x, st.y)] = 1;
		//printf("(%d,%d),%d\n", st.x, st.y, st.d);
		Pos pos = Pos(st.x, st.y, 0);
		//printf("(%d,%d),%d (%d,%d,%d) (%d,%d,%d)\n", st.x, st.y, st.d, pos.x, pos.y, pos.z, targ.x, targ.y, targ.z);
		bool blocked = 0, unreachable = 0;
		int blockstate = gamemap.BlockType(pos);
		if (blockstate == 0)unreachable = 1;
		else if (blockstate == 2)
		{
			if (unit.height == 0)unreachable = 1;
		}
		for (int i = 1; i < unit_cnt; i++)
		{
			if (units[i].status & UNIT_STATUS_DEAD)continue;
			if (temps[units[i].unit_type].temp_type == GAME_TEMP_TYPE_ARTIFACT)continue;
			Pos diff = units[i].pos - pos;
			if (temps[units[i].unit_type].temp_type == GAME_TEMP_TYPE_BUILDING)
			{
				if (unit.height == 0 && diff.iszero())unreachable = 1;
			}
			else
			{
				if (diff.Length() <= 1)
				{
					if (units[i].pid != unit.pid)blocked = 1;
					if (diff.iszero())
					{
						if (unit.height == units[i].height)unreachable = 1;
					}
				}
			}
		}
		if (unreachable)continue;
		if (pos == targ)
		{
			reached = 1;
			break;
		}
		if (!blocked&&st.d<unit.move_range+unit.move_range_buff)
		{
			State nst;
			nst = st; nst.d++;
			nst.x++;
			Q.push(nst);
			nst = st; nst.d++;
			nst.x--;
			Q.push(nst);
			nst = st; nst.d++;
			nst.y++;
			Q.push(nst);
			nst = st; nst.d++;
			nst.y--;
			Q.push(nst);
			nst = st; nst.d++;
			nst.x++; nst.y++;
			Q.push(nst);
			nst = st; nst.d++;
			nst.x--; nst.y--;
			Q.push(nst);
		}
	}
	if (reached)
	{
		Pos from = unit.pos;
		unit.pos = targ;
		for (int i = 1; i < unit_cnt; i++)
		{
			if (units[i].status & UNIT_STATUS_DEAD)continue;
			if(temps[units[i].unit_type].trigger_move)
			{
				map<string, IContent> contentspace;
				contentspace["id"].assign(i);
				contentspace["uid"].assign(uid);
				contentspace["from"].assign(from);
				contentspace["targ"].assign(targ);
				IContent res;
				res = LoongExecuter(*temps[units[i].unit_type].trigger_move, funcspace, contentspace);
			}
		}
	}
	else SavageLog("Movement Failed.\n");
}

void GameWorld::Attack(int targid, int fromid)
{
	if (units[targid].status & UNIT_STATUS_DEAD)
	{
		SavageLog("Attack Failed: Target is dead.\n");
		return;
	}
	if (units[fromid].status & UNIT_STATUS_DEAD)
	{
		SavageLog("Attack Failed: Attacker is dead.\n");
		return;
	}
	Pos diff = units[targid].pos - units[fromid].pos;
	if (diff.Length() <= units[fromid].attack_range_far + units[fromid].attack_range_far_buff &&
		diff.Length() >= units[fromid].attack_range_near + units[fromid].attack_range_near_buff)
	{
		int damage = units[fromid].attack + units[fromid].attack_buff;
		for (int i = 1; i < unit_cnt; i++)
		{
			if (units[i].status & UNIT_STATUS_DEAD)continue;
			if (temps[units[i].unit_type].trigger_attack)
			{
				map<string, IContent> contentspace;
				contentspace["id"].assign(i);
				contentspace["targid"].assign(targid);
				contentspace["fromid"].assign(fromid);
				contentspace["damage"].assign(damage);
				IContent res;
				res = LoongExecuter(*temps[units[i].unit_type].trigger_attack, funcspace, contentspace);
				damage = contentspace["damage"].to_int();
			}
		}
		if (units[targid].health > 0)
			Damage(targid, fromid, damage, DAMAGE_TYPE_ATTACK);
	}
	else SavageLog("Attack Failed: Out of range.\n");
}

void GameWorld::Damage(int targid, int fromid, int damage, int type)
{
	if (units[targid].status & UNIT_STATUS_DEAD)
	{
		SavageLog("Attack Failed: Target is dead.\n");
		return;
	}
	if (units[fromid].status & UNIT_STATUS_DEAD)
	{
		SavageLog("Attack Failed: Attacker is dead.\n");
		return;
	}
	for (int i = 1; i < unit_cnt; i++)
	{
		if (units[i].status & UNIT_STATUS_DEAD)continue;
		if (temps[units[i].unit_type].trigger_damage)
		{
			map<string, IContent> contentspace;
			contentspace["id"].assign(i);
			contentspace["targid"].assign(targid);
			contentspace["fromid"].assign(fromid);
			contentspace["damage"].assign(damage);
			contentspace["type"].assign(type);
			IContent res;
			res = LoongExecuter(*temps[units[i].unit_type].trigger_damage, funcspace, contentspace);
			damage = contentspace["damage"].to_int();
		}
	}
	units[targid].health -= damage;
}

void GameWorld::Kill(int uid)
{
	if (units[uid].status & UNIT_STATUS_DEAD)
	{
		SavageLog("Kill Failed: Already Dead.\n");
		return;
	}
	for (int i = 1; i < unit_cnt; i++)
	{
		if (units[i].status & UNIT_STATUS_DEAD)continue;
		if (temps[units[i].unit_type].trigger_death)
		{
			map<string, IContent> contentspace;
			contentspace["id"].assign(i);
			contentspace["uid"].assign(uid);
			IContent res;
			res = LoongExecuter(*temps[units[i].unit_type].trigger_death, funcspace, contentspace);
		}
	}
	units[uid].status |= UNIT_STATUS_DEAD;
}

void GameWorld::Bless(int uid, int health, int attack)
{
	units[uid].health += health;
	units[uid].health_limit += health;
	units[uid].attack += attack;
}

void GameWorld::Print() const
{
	SavageLog("\n");
	SavageLog("\nMap:\n");
	gamemap.Print();
	SavageLog("\nTemplates:\n");
	for (int i=0;i<temps.size();i++)
	{

		const GameUnitTemp* temp = &temps[i];
		SavageLog("Template %d:\n------------------\n", i);
		temp->Print();
		SavageLog("------------------\n");
	}
	SavageLog("\nUnits:\n");
	for (int i = 1; i < unit_cnt; i++)
	{
		if (units[i].status & UNIT_STATUS_DEAD)continue;
		SavageLog("uid[%d] ", i); units[i].GetUnitModel().Print();
	}
}

void GameWorld::Refresh()
{
	for (int i = 1; i < unit_cnt; i++)
		if (units[i].health <= 0)Kill(i);
	for (int uid = 1; uid < unit_cnt; uid++)
	{
		if (units[uid].status & UNIT_STATUS_DEAD)continue;
		int health_buff = 0;
		int attack_buff = 0;
		int attack_range_near_buff = 0;
		int attack_range_far_buff = 0;
		int move_range_buff = 0;
		for (int id = 1; id < unit_cnt; id++)
		{
			if (units[id].status & UNIT_STATUS_DEAD)continue;
			if (temps[units[id].unit_type].trigger_halo)
			{
				map<string, IContent> contentspace;
				contentspace["id"].assign(id);
				contentspace["uid"].assign(uid);
				contentspace["health_buff"].assign(health_buff);
				contentspace["attack_buff"].assign(attack_buff);
				contentspace["attack_range_near_buff"].assign(attack_range_near_buff);
				contentspace["attack_range_far_buff"].assign(attack_range_far_buff);
				contentspace["move_range_buff"].assign(move_range_buff);
				IContent res;
				res = LoongExecuter(*temps[units[id].unit_type].trigger_halo, funcspace, contentspace);
				health_buff = contentspace["health_buff"].to_int();
				attack_buff = contentspace["attack_buff"].to_int();
				attack_range_near_buff = contentspace["attack_range_near_buff"].to_int();
				attack_range_far_buff = contentspace["attack_range_far_buff"].to_int();
				move_range_buff = contentspace["move_range_buff"].to_int();
			}
		}
		if (health_buff > units[uid].health_buff)
		{
			units[uid].health += health_buff - units[uid].health_buff;
		}
		units[uid].health_buff = health_buff;
		units[uid].health = min(units[uid].health, units[uid].health_limit + units[uid].health_buff);
		units[uid].attack_buff = attack_buff;
		units[uid].attack_range_near_buff = attack_range_near_buff;
		units[uid].attack_range_far_buff = attack_range_far_buff;
		units[uid].move_range_buff = move_range_buff;
	}
}

IContent MakePos(IContent var)
{
	return Pos(var[0].to_int(), var[1].to_int(), var[2].to_int());
}

IContent Print(IContent content)
{
	cout << content.str().c_str() << endl;
	return IContent();
}

IContent Max(IContent var)
{
	return IContent(max(var[0].to_int(),var[1].to_int()));
}

IContent Min(IContent var)
{
	return IContent(min(var[0].to_int(), var[1].to_int()));
}

void ActivateWorld(GameWorld* pWorld)
{
	g_pWorld = pWorld;
}
