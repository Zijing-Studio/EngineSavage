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
IContent GetUnit(IContent var);


void Initialize();

void LoadTemps(const string dirpath);

void LoadMap(const string filepath);

void AddStation(int x,int y);

void SetMana(int pid, int m);

void StartRound(int pid);

void EndRound(int pid);

void CalcHalo();


void Trigger(string eventname, LoongContentSpace& contentspace);

void TriggerEvent(string eventname, int targuid, int fromuid, int value, Pos pos);

void PrintWorldStatus();


int summon(GameUnit unit);

void changehealth(int uid, int health);

void kill(int uid);

void move(int uid, Pos pos);

void Summon(GameUnit unit);

void Kill(int targuid, int fromuid);

void Move(int uid, Pos pos);

void ChangeHealth(int targuid, int fromuid, int value);

int ChooseTroop(int pid, int* t);

int Summon(int pid, int tid, int level, Pos pos);

int Move(int pid, int uid, Pos pos);

int Attack(int pid, int fromuid, int targuid);
