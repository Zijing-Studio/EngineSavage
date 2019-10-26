#include "SavageWorld.h"

const int player_cnt = 2;
const int troop_cnt = 4;

IContent MakePos(IContent var)
{
	return IContent(Pos(var[0].to_int(), var[1].to_int(), var[2].to_int()));
}
IContent Print(IContent var)
{
	var.Print();
	return IContent();
}
IContent Max(IContent var)
{
	return IContent(max(var[0].to_int(), var[1].to_int()));
}
IContent Min(IContent var)
{
	return IContent(min(var[0].to_int(), var[1].to_int()));
}

map<string, ILoongFunction> g_world_funcspace;
vector<GameTemp> game_temp;
GameMap game_map;
vector<GameUnit> game_unit;

int troop[player_cnt][troop_cnt], reserve[player_cnt][troop_cnt];
int mana[player_cnt], mana_limit[player_cnt];

struct GameStation
{
public:
	int x, y, pid;
};
vector<GameStation> game_station;

void SetMana(int pid, int m)
{
	mana_limit[pid] = mana[pid] = m;
}

void StartRound(int pid)
{
	mana_limit[pid]++;
	mana_limit[pid] = min(mana_limit[pid], 12);
	mana[pid] = mana_limit[pid];
	LoongContentSpace contentspace;
	for (int i = 0; i < game_station.size(); i++)
	{
		bool on[player_cnt] = {};
		Pos pos = Pos(game_station[i].x, game_station[i].y, 0);
		for (int j = 0; j < game_unit.size(); j++)
		{
			if (game_unit[j].status & UNIT_STATUS_DEAD)continue;
			if (pos == game_unit[j].pos)
			{
				on[game_unit[j].pid] = 1;
			}
		}
		if (on[0] ^ on[1])
		{
			if (on[0])game_station[i].pid = 0;
			else game_station[i].pid = 1;
		}
	}
	contentspace["pid"].assign(pid);
	Trigger("startround", contentspace);
}

void EndRound(int pid)
{
	for (int i = 2; i < game_unit.size(); i++)
	{
		GameUnit& unit = game_unit[i];
		if (unit.status & UNIT_STATUS_DEAD)continue;
		unit.status &= ~UNIT_STATUS_SLEEP;
	}
	LoongContentSpace contentspace;
	contentspace["pid"].assign(pid);
	Trigger("endround", contentspace);
}

void CalcHalo()
{
	for (int uid = 2; uid < game_unit.size(); uid++)
	{
		if (game_unit[uid].status & UNIT_STATUS_DEAD)continue;
		LoongContentSpace contentspace;
		contentspace["uid"].assign(uid);
		contentspace["attack"].assign(0);
		contentspace["health"].assign(0);
		contentspace["attack_range_near"].assign(0);
		contentspace["attack_range_far"].assign(0);
		contentspace["move_range"].assign(0);
		Trigger("halo", contentspace);
		game_unit[uid].attack_buff = contentspace["attack"].to_int();
		int hlb = game_unit[uid].health_limit + game_unit[uid].health_buff, hla;
		game_unit[uid].health_buff = contentspace["health"].to_int();
		hla = game_unit[uid].health_limit + game_unit[uid].health_buff;
		game_unit[uid].health = game_unit[uid].health * hla / hlb;
		game_unit[uid].attack_range_far_buff = contentspace["attack_range_far"].to_int();
		game_unit[uid].attack_range_near_buff = contentspace["attack_range_near"].to_int();
		game_unit[uid].move_range_buff = contentspace["move_range"].to_int();
	}
}


void AddStation(int x, int y)
{
	GameStation gs;
	gs.x = x;
	gs.y = y;
	gs.pid = -1;
	game_station.push_back(gs);
}

int ChooseTroop(int pid, int* t)
{
	bool illegal = 0;
	for (int i = 0; i < troop_cnt; i++)
	{
		if (t[i] >= game_temp.size() || t[i] < 0)
			illegal = 1;
		for (int j = 0; j < i; j++)
		{
			if (t[i] == t[j])illegal = 1;
		}
		if (illegal)break;
		troop[pid][i] = t[i];
		reserve[pid][i] = game_temp[t[i]].capacity;

		if (reserve[pid][i] == -1)
		{
			illegal = 1;
			break;
		}
	}
	if (illegal)
	{
		SavageLog("Error: Illegal troop chose by player %d.\n", pid);
		return -1;
	}
	return 0;
}

int summon(GameUnit unit)
{
	game_unit.push_back(unit);
	return game_unit.size() - 1;
}

void changehealth(int uid, int health)
{
	game_unit[uid].health += health;
	game_unit[uid].health = max(0, min(game_unit[uid].health, game_unit[uid].health_limit + game_unit[uid].health_buff));
}

void kill(int uid)
{
	game_unit[uid].status |= UNIT_STATUS_DEAD;
}

void move(int uid, Pos pos)
{
	game_unit[uid].pos = pos;
}

void Summon(GameUnit unit)
{
	int uid = summon(unit);
	TriggerEvent("summon", uid, 0, 0, Pos());
}

void Kill(int targuid, int fromuid)
{
	kill(targuid);
	TriggerEvent("kill", targuid, fromuid, 0, Pos());
}

void Move(int uid, Pos pos)
{
	LoongContentSpace contentspace;
	contentspace["uid"].assign(uid);
	contentspace["pos"].assign(pos);
	contentspace["cancle"].assign(0);
	Trigger("move", contentspace);
	if (contentspace["cancle"].to_int())return;
	if (game_unit[uid].status & UNIT_STATUS_DEAD)return;
	Pos frompos = game_unit[uid].pos;
	move(uid, pos);
	contentspace["uid"].assign(uid);
	contentspace["frompos"].assign(frompos);
	Trigger("moveafter", contentspace);
}

void ChangeHealth(int targuid, int fromuid, int value)
{
	LoongContentSpace contentspace;
	contentspace["targuid"].assign(targuid);
	contentspace["fromuid"].assign(fromuid);
	contentspace["value"].assign(value);
	Trigger("changehealth", contentspace);
	targuid = contentspace["targuid"].to_int();
	fromuid = contentspace["fromuid"].to_int();
	value = contentspace["value"].to_int();
	if (value)
	{
		changehealth(targuid, value);
		Trigger("changehealthafter", contentspace);
		if (game_unit[targuid].health <= 0 && !(game_unit[targuid].status & UNIT_STATUS_DEAD))
			Kill(targuid, fromuid);
	}
}

void Trigger(string eventname, LoongContentSpace& contentspace)
{
	for (int i = 2; i < game_unit.size(); i++)
	{
		if (game_unit[i].status & UNIT_STATUS_DEAD)continue;
		if (game_temp[game_unit[i].unit_type].unit_temp[game_unit[i].level].trigger.count(eventname))
		{
			contentspace["id"].assign(i);
			IContent content = LoongExecuter(game_temp[game_unit[i].unit_type].unit_temp[game_unit[i].level].trigger[eventname], g_world_funcspace, contentspace);
		}
	}
}


void TriggerEvent(string eventname, int targuid, int fromuid, int value, Pos pos)
{
	LoongContentSpace contentspace;
	contentspace["targuid"].assign(targuid);
	contentspace["fromuid"].assign(fromuid);
	contentspace["value"].assign(value);
	contentspace["pos"].assign(pos);
	Trigger(eventname, contentspace);
}

IContent GetUnitCnt(IContent var)
{
	return IContent((int)game_unit.size());
}

IContent GetUnit(IContent var)
{
	IContent res;
	int id = var.to_int();
	if (id < 0 || id >= game_unit.size())return IContent();
	GameUnitModel unit = game_unit[id].GetUnitModel();
	res["attack"].assign(unit.attack);
	res["health"].assign(unit.health);
	res["pos"].assign(unit.pos);
	res["attackrangenear"].assign(unit.attack_range_near);
	res["attackrangefar"].assign(unit.attack_range_far);
	res["healthlimit"].assign(unit.health_limit);
	res["height"].assign(unit.height);
	res["level"].assign(unit.level);
	res["moverange"].assign(unit.move_range);
	res["pid"].assign(unit.pid);
	res["status"].assign(unit.status);
	res["unittype"].assign(unit.unit_type);
	return res;
}

IContent IKill(IContent var)
{
	int targid = var[0].to_int(), fromid = var[1].to_int();
	Kill(targid, fromid);
	return IContent();
}

IContent IChangeHealth(IContent var)
{
	ChangeHealth(var[0].to_int(), var[1].to_int(), var[2].to_int());
	return IContent();
}

void Initialize()
{
	g_world_funcspace["Pos"] = MakePos;
	g_world_funcspace["print"] = Print;
	g_world_funcspace["max"] = Max;
	g_world_funcspace["min"] = Min;
	g_world_funcspace["GetUnitCnt"] = GetUnitCnt;
	g_world_funcspace["GetUnit"] = GetUnit;
	g_world_funcspace["Kill"] = IKill;
	g_world_funcspace["ChangeHealth"] = IChangeHealth;
}

void LoadTemps(const string dirpath)
{
	int index = 0;
	char* temppath = new char[1024];
	GameTemp* temp = new GameTemp;
	while (true)
	{
		sprintf(temppath, "%s%d/", dirpath.c_str(), index);
		int res = LoadTemplate(temppath, temp);
		if (res)break;
		game_temp.push_back(*temp);
		index++;
	}
	delete temp;
	delete[] temppath;
}

void LoadMap(const string filepath)
{
	game_map.Init(filepath);
}

void PrintWorldStatus()
{
	printf("\nGameMap:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	game_map.Print();
	printf("\n");
	for (int i = 0; i < game_temp.size(); i++)
	{
		printf("\nTemplate #%d\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", i);
		game_temp[i].Print();
	}

	printf("Base Health:[%d,%d]\n", game_unit[0].health, game_unit[1].health);

	for (int i = 2; i < game_unit.size(); i++)
	{
		GameUnitModel unit_model = game_unit[i].GetUnitModel();
		if (unit_model.status & UNIT_STATUS_DEAD)continue;
		printf("Unit #%d\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", i);
		printf("playerid:%d\n", unit_model.pid);
		printf("type:%d,%s\n", unit_model.unit_type, game_temp[unit_model.unit_type].temp_name.c_str());
		printf("level:%d\n", unit_model.level);
		printf("health:%d\\%d\n", unit_model.health, unit_model.health_limit);
		printf("attack:%d\n", unit_model.attack);
		printf("attack_range:%d\\%d\n", unit_model.attack_range_near, unit_model.attack_range_far);
		printf("move_range:%d\n", unit_model.move_range);
		printf("pos:(%d,%d) height:%d\n", unit_model.pos.EliminateZ().x, unit_model.pos.EliminateZ().y, unit_model.height);
		printf("status:%d\n", unit_model.status);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	}

	for (int i = 0; i < player_cnt; i++)
	{
		printf("player #%d", i);
		for (int j = 0; j < troop_cnt; j++)
		{
			printf(" %s:%d\\%d", game_temp[troop[i][j]].temp_name.c_str(), reserve[i][j], game_temp[troop[i][j]].capacity);
		}
		printf("\n");
	}

	printf("Mana:[%d\\%d,%d\\%d]\n", mana[0], mana_limit[0], mana[1], mana_limit[1]);

	printf("Stations:\n");
	for (int i = 0; i < game_station.size(); i++)
	{
		GameStation st = game_station[i];
		printf("(%d,%d):%d ", st.x, st.y, st.pid);
	}
	puts("");
	puts("");
}

bool IsEmpty(Pos p, int height)
{
	bool ret = true;
	for (auto unit : game_unit)
	{
		if (unit.status & UNIT_STATUS_DEAD)continue;
		if (unit.pos == p && unit.height == height)ret = false;
		if (!ret)break;
	}
	return ret;
}

int Summon(int pid, int tid, int level, Pos pos)
{
	bool illegal = 0;
	if (pid < 0 || pid >= player_cnt)illegal = 1;
	else if (tid < 0 || tid >= troop_cnt)illegal = 1;
	else if (!reserve[pid][tid])illegal = 1;
	else if (game_temp[troop[pid][tid]].unit_temp[level].mana_cost > mana[pid])illegal = 1;
	if (illegal)
	{
		SavageLog("Error: Player#%d Summon denied.", pid);
		return -1;
	}
	pos = pos.EliminateZ();
	if (game_map.BlockType(pos) != 1)illegal = 1;
	else if (!IsEmpty(pos, game_temp[troop[pid][tid]].unit_temp[level].height))illegal = 1;
	if (illegal)
	{
		SavageLog("Error: Player#%d Summon denied.", pid);
		return -1;
	}
	bool pass = 0;
	for (auto sta : game_station)
	{
		if(sta.pid==pid)
			if ((Pos(sta.x, sta.y, 0) - pos).Length() <= 1)
			{
				pass = 1;
			}
		if (pass)break;
	}
	if (!pass)
	{
		SavageLog("Error: Player#%d Summon denied.", pid);
		return -1;
	}
	mana[pid] -= game_temp[troop[pid][tid]].unit_temp[level].mana_cost;
	reserve[pid][tid]--;
	GameUnit base;
	GameUnitTemp& temp = game_temp[troop[pid][tid]].unit_temp[level];
	base.attack = temp.attack;
	base.attack_buff = 0;
	base.attack_range_far = temp.attack_range_far;
	base.attack_range_far_buff = 0;
	base.attack_range_near = temp.attack_range_near;
	base.attack_range_near_buff = 0;
	base.health = temp.health;
	base.health_limit = temp.health;
	base.health_buff = 0;
	base.height = temp.height;
	base.move_range = temp.move_range;
	base.move_range_buff = 0;
	base.pos = pos;
	base.status = temp.status;
	base.unit_type = troop[pid][tid];
	base.level = level;
	base.pid = pid;
	Summon(base);
	return 0;
}

int Move(int pid, int uid, Pos pos)
{
	bool illegal = 0;
	if (uid < 2 || uid >= game_unit.size())illegal = 1;
	if (illegal)
	{
		SavageLog("Error: Player#%d Move Unit:%d denied.\n", pid, uid);
		return -1;
	}
	const GameUnit& unit = game_unit[uid];
	if (unit.pid != pid)illegal = 1;
	else if ((unit.pos - pos).Length() > unit.move_range)illegal = 1;
	else if (unit.status & UNIT_STATUS_SLEEP)illegal = 1;
	else if (!(unit.move_range + unit.move_range_buff))illegal = 1;
	else if (!IsEmpty(pos, unit.height))illegal = 1;
	if (illegal)
	{
		SavageLog("Error: Player#%d Move Unit:%d denied. At Two\n", pid, uid);
		return -1;
	}
	bool pass = 0;
	struct BFSState
	{
	public:
		int x, y, d;
	};
	queue<BFSState> Q;
	map<pair<int, int>, bool> vis;
	Pos startp = unit.pos.EliminateZ();
	BFSState put;
	put.d = 1;

	put.x = startp.x+1;
	put.y = startp.y;
	Q.push(put);
	put.x = startp.x-1;
	put.y = startp.y;
	Q.push(put);
	put.x = startp.x;
	put.y = startp.y+1;
	Q.push(put);
	put.x = startp.x;
	put.y = startp.y-1;
	Q.push(put);
	put.x = startp.x+1;
	put.y = startp.y+1;
	Q.push(put);
	put.x = startp.x-1;
	put.y = startp.y-1;
	Q.push(put);
	while (!Q.empty())
	{
		BFSState st = Q.front(); Q.pop();
		if (vis[make_pair(st.x, st.y)])continue;
		vis[make_pair(st.x, st.y)] = 1;
		Pos p = Pos(st.x, st.y, 0);
		bool unreachable = 0, blocked = 0;
		if (game_map.BlockType(Pos(st.x, st.y, 0)) != 1)
		{
			if (!(unit.height && game_map.BlockType(Pos(st.x, st.y, 0)) == 2))unreachable = 1;
		}
		for (const auto& punit : game_unit)
		{
			if (punit.status & UNIT_STATUS_DEAD)continue;
			if (punit.pos == p && punit.height == unit.height)unreachable = 1;
			if (unreachable)break;
			if ((punit.pos - p).Length() == 1 && punit.pid != unit.pid)blocked = 1;
		}
		if (unreachable)continue;
		if (p == pos)
		{
			pass = 1;
			break;
		}
		if (!blocked && st.d < unit.move_range + unit.move_range_buff)
		{
			startp = p;
			BFSState put;
			put.d = st.d + 1;

			put.x = startp.x + 1;
			put.y = startp.y;
			Q.push(put);
			put.x = startp.x - 1;
			put.y = startp.y;
			Q.push(put);
			put.x = startp.x;
			put.y = startp.y + 1;
			Q.push(put);
			put.x = startp.x;
			put.y = startp.y - 1;
			Q.push(put);
			put.x = startp.x + 1;
			put.y = startp.y + 1;
			Q.push(put);
			put.x = startp.x - 1;
			put.y = startp.y - 1;
			Q.push(put);
		}
	}
	if (!pass)
	{
		SavageLog("Error: Player#%d Move Unit:%d denied.", pid, uid);
		return -1;
	}
	Move(uid, pos);
	game_unit[uid].status |= UNIT_STATUS_SLEEP;
	return 0;
}

int Attack(int pid, int fromuid, int targuid)
{
	bool illegal = 0;
	if (fromuid < 2 || fromuid >= game_unit.size())illegal = 1;
	else if (targuid < 0 || targuid >= game_unit.size())illegal = 1;
	if (illegal)
	{
		SavageLog("Error: Player#%d Attack denied.", pid);
		return -1;
	}
	GameUnit& unit = game_unit[fromuid], & eunit = game_unit[targuid];
	int dist = (unit.pos - eunit.pos).Length();
	if (unit.status & UNIT_STATUS_DEAD)illegal = 1;
	else if (eunit.status & UNIT_STATUS_DEAD)illegal = 1;
	else if (unit.attack_range_near == -1)illegal = 1;
	else if (unit.status & UNIT_STATUS_SLEEP)illegal = 1;
	else if (unit.attack_range_near + unit.attack_range_near_buff > dist || unit.attack_range_far + unit.attack_range_far_buff < dist)illegal = 1;
	else if (!(unit.status & UNIT_STATUS_TOAIR) && !unit.height && eunit.height)illegal = 1;
	if (illegal)
	{
		SavageLog("Error: Player#%d Attack denied.", pid);
		return -1;
	}
	int fromdamage = 0, targdamage = unit.attack + unit.attack_buff;
	illegal = 0;
	if (eunit.attack_range_near == -1)illegal = 1;
	else if (eunit.attack_range_near + eunit.attack_range_near_buff > dist || eunit.attack_range_far + eunit.attack_range_far_buff < dist)illegal = 1;
	else if (!(eunit.status & UNIT_STATUS_TOAIR) && !eunit.height && unit.height)illegal = 1;
	if (!illegal)fromdamage = eunit.attack + eunit.attack_buff;
	LoongContentSpace contentspace;
	contentspace["fromuid"].assign(fromuid);
	contentspace["targuid"].assign(targuid);
	contentspace["fromdamage"].assign(fromdamage);
	contentspace["targdamage"].assign(targdamage);
	Trigger("attack", contentspace);
	fromdamage = contentspace["fromdamage"].to_int();
	targdamage = contentspace["targdamage"].to_int();
	if (!(game_unit[fromuid].status & UNIT_STATUS_DEAD) && !(game_unit[targuid].status & UNIT_STATUS_DEAD))
	{
		if(targdamage)ChangeHealth(targuid, fromuid, -targdamage);
		if(fromdamage)ChangeHealth(fromuid, targuid, -fromdamage);
		contentspace["fromuid"].assign(fromuid);
		contentspace["targuid"].assign(targuid);
		contentspace["fromdamage"].assign(fromdamage);
		contentspace["targdamage"].assign(targdamage);
		Trigger("attackafter", contentspace);
		game_unit[fromuid].status |= UNIT_STATUS_SLEEP;
	}
	return 0;
}