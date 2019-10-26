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

GameUnitTemp::~GameUnitTemp()
{
	;
}

void GameUnitTemp::Print() const
{
	SavageLog("\n");
	SavageLog("cold_down:%d\n", cold_down);
	SavageLog("mana_cost:%d\n", mana_cost);
	SavageLog("health:%d\n", health);
	SavageLog("attack:%d\n", attack);
	SavageLog("attack_range_near:%d\n", attack_range_near);
	SavageLog("attack_range_far:%d\n", attack_range_far);
	SavageLog("move_range:%d\n", move_range);
	SavageLog("status:%d\n", status);
	SavageLog("height:%d\n", height);
	SavageLog("\n");
	for (auto &code : trigger)
	{
		SavageLog("trigger:%s\n----------------\n%s\n----------------\n", code.first.c_str(), code.second.code);
	}
}

int LoadTemplate(const string filepath, GameUnitTemp* pTemp)
{
	if (!pTemp)
	{
		SavageLog("Error: Can't operate nullptr\n");
		return -1;
	}
	ifstream fin((filepath + "info.log").c_str());
	if (!fin)
	{
		SavageLog("Error: Can't open %s\n", (filepath + "info.log").c_str());
		return -1;
	}
	string order;
	while (fin >> order)
	{
		if (order == "cold_down")fin >> pTemp->cold_down;
		if (order == "mana_cost")fin >> pTemp->mana_cost;
		if (order == "health")fin >> pTemp->health;
		if (order == "attack")fin >> pTemp->attack;
		if (order == "attack_range_near")fin >> pTemp->attack_range_near;
		if (order == "attack_range_far")fin >> pTemp->attack_range_far;
		if (order == "move_range")fin >> pTemp->move_range;
		if (order == "summon_status")fin >> pTemp->status;
		if (order == "to_air")pTemp->status |= 32;
		if (order == "height")fin >> pTemp->height;
		if (order == "trigger")
		{
			string trigger_name, trigger_path; fin >> trigger_name;
			trigger_path = filepath + trigger_name + ".code";
			pTemp->trigger[trigger_name].LoadFromFile(trigger_path.c_str());
		}
	}
	fin.close();
	return 0;
}

int LoadTemplate(const string filepath, GameTemp* pTemp)
{
	if (!pTemp)
	{
		SavageLog("Error: Can't operate nullptr\n");
		return -1;
	}
	ifstream fin((filepath + "info.log").c_str());
	if (!fin)
	{
		SavageLog("Error: Can't open %s\n", (filepath + "info.log").c_str());
		return -1;
	}
	string order;
	while (fin >> order)
	{
		if (order == "name")fin >> pTemp->temp_name;
		if (order == "capacity")fin >> pTemp->capacity;
	}
	fin.close();
	LoadTemplate(filepath + "0/", &pTemp->unit_temp[0]);
	LoadTemplate(filepath + "1/", &pTemp->unit_temp[1]);
	LoadTemplate(filepath + "2/", &pTemp->unit_temp[2]);
	return 0;
}

void GameTemp::Print() const
{
	printf("Name:%s\n", temp_name.c_str());
	printf("Capacity:%d\n", capacity);
	for (int level = 0; level < 3; level++)
	{
		printf("-------LEVEL:%d-------\n", level);
		unit_temp[level].Print();
	}
	printf("---------------------\n");
}