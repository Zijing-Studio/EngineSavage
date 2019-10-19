#include "SavageTemp.h"

void LoadCode(const char* filepath, LoongCode** ppCode)
{
	FILE* file;
#ifdef _MSC_VER
	fopen_s(&file, filepath, "r");
#else
	file = fopen(filepath, "r");
#endif
	if (file)
	{
		fclose(file);
		if (!(*ppCode))*ppCode = new LoongCode;
		(*ppCode)->LoadFromFile(filepath);
	}
}

GameUnitTemp::GameUnitTemp()
{
}

GameUnitTemp::GameUnitTemp(const GameUnitTemp& temp)
{
	temp_type = temp.temp_type;
	health = temp.health;
	attack = temp.attack;
	attack_range_near = temp.attack_range_near;
	attack_range_far = temp.attack_range_far;
	move_range = temp.move_range;
	if (temp.trigger_gamestart)
	{
		trigger_gamestart = new LoongCode;
		*trigger_gamestart = *temp.trigger_gamestart;
	}
	else trigger_gamestart = NULL;
	if (temp.trigger_roundstart)
	{
		trigger_roundstart = new LoongCode;
		*trigger_roundstart = *temp.trigger_roundstart;
	}
	else trigger_roundstart = NULL;
	if (temp.trigger_roundend)
	{
		trigger_roundend = new LoongCode;
		*trigger_roundend = *temp.trigger_roundend;
	}
	else trigger_roundend = NULL;
	if (temp.trigger_cast)
	{
		trigger_cast = new LoongCode;
		*trigger_cast = *temp.trigger_cast;
	}
	else trigger_cast = NULL;
	if (temp.trigger_summon)
	{
		trigger_summon = new LoongCode;
		*trigger_summon = *temp.trigger_summon;
	}
	else trigger_summon = NULL;
	if (temp.trigger_attack)
	{
		trigger_attack = new LoongCode;
		*trigger_attack = *temp.trigger_attack;
	}
	else trigger_attack = NULL;
	if (temp.trigger_move)
	{
		trigger_move = new LoongCode;
		*trigger_move = *temp.trigger_move;
	}
	else trigger_move = NULL;
	if (temp.trigger_heal)
	{
		trigger_heal = new LoongCode;
		*trigger_heal = *temp.trigger_heal;
	}
	else trigger_heal = NULL;
	if (temp.trigger_damage)
	{
		trigger_damage = new LoongCode;
		*trigger_damage = *temp.trigger_damage;
	}
	else trigger_damage = NULL;
	if (temp.trigger_death)
	{
		trigger_death = new LoongCode;
		*trigger_death = *temp.trigger_death;
	}
	else trigger_death = NULL;
	if (temp.trigger_halo)
	{
		trigger_halo = new LoongCode;
		*trigger_halo = *temp.trigger_halo;
	}
	else trigger_halo = NULL;
}

GameUnitTemp::~GameUnitTemp()
{
	if (trigger_gamestart)delete trigger_gamestart;
	if (trigger_roundstart)delete trigger_roundstart;
	if (trigger_cast)delete trigger_cast;
	if (trigger_summon)delete trigger_summon;
	if (trigger_attack)delete trigger_attack;
	if (trigger_move)delete trigger_move;
	if (trigger_heal)delete trigger_heal;
	if (trigger_damage)delete trigger_damage;
	if (trigger_death)delete trigger_death;
	if (trigger_halo)delete trigger_halo;
}

void GameUnitTemp::LoadFromFile(const char* filepath)
{
	char path[1024];
	sprintf(path, "%s\\info.log", filepath);
	FILE* file;
#ifdef _MSC_VER
	fopen_s(&file, path, "r");
#else
	file = fopen(path, "r");
#endif // _MSC_VER
	if (!file)return;
	bool res = 1;
	res = res && fscanf(file, "%d%d%d%d%d%d%d%d", 
		&temp_type,
		&health,
		&attack,
		&attack_range_near,
		&attack_range_far,
		&move_range,
		&status,
		&height);
	if (!res)return;
	sprintf(path, "%s\\gamestart.code", filepath);
	LoadCode(path, &trigger_gamestart);
	sprintf(path, "%s\\roundstart.code", filepath);
	LoadCode(path, &trigger_roundstart);
	sprintf(path, "%s\\roundend.code", filepath);
	LoadCode(path, &trigger_roundend);
	sprintf(path, "%s\\cast.code", filepath);
	LoadCode(path, &trigger_cast);
	sprintf(path, "%s\\summon.code", filepath);
	LoadCode(path, &trigger_summon);
	sprintf(path, "%s\\attack.code", filepath);
	LoadCode(path, &trigger_attack);
	sprintf(path, "%s\\move.code", filepath);
	LoadCode(path, &trigger_move);
	sprintf(path, "%s\\heal.code", filepath);
	LoadCode(path, &trigger_heal);
	sprintf(path, "%s\\damage.code", filepath);
	LoadCode(path, &trigger_damage);
	sprintf(path, "%s\\death.code", filepath);
	LoadCode(path, &trigger_death);
	sprintf(path, "%s\\halo.code", filepath);
	LoadCode(path, &trigger_halo);
}

void GameUnitTemp::Print() const
{
	SavageLog("\n");
	SavageLog("type:%d\n", temp_type);
	SavageLog("health:%d\n", health);
	SavageLog("attack:%d\n", attack);
	SavageLog("attack_range_near:%d\n", attack_range_near);
	SavageLog("attack_range_far:%d\n", attack_range_far);
	SavageLog("move_range:%d\n", move_range);
	SavageLog("status:%d\n", status);
	SavageLog("height:%d\n", height);
	SavageLog("\n");
	if (trigger_gamestart)SavageLog("\ntrigger_gamestart:\n%s\n", trigger_gamestart->code);
	if (trigger_roundstart)SavageLog("\ntrigger_roundstart:\n%s\n", trigger_roundstart->code);
	if (trigger_roundend)SavageLog("\ntrigger_roundend:\n%s\n", trigger_roundend->code);
	if (trigger_cast)SavageLog("\ntrigger_cast:\n%s\n", trigger_cast->code);
	if (trigger_summon)SavageLog("\ntrigger_summon:\n%s\n", trigger_summon->code);
	if (trigger_attack)SavageLog("\ntrigger_attack:\n%s\n", trigger_attack->code);
	if (trigger_move)SavageLog("\ntrigger_move:\n%s\n", trigger_move->code);
	if (trigger_heal)SavageLog("\ntrigger_heal:\n%s\n", trigger_heal->code);
	if (trigger_damage)SavageLog("\ntrigger_damage:\n%s\n", trigger_damage->code);
	if (trigger_death)SavageLog("\ntrigger_death:\n%s\n", trigger_death->code);
	if (trigger_halo)SavageLog("\ntrigger_halo:\n%s\n", trigger_halo->code);
}
