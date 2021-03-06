﻿#include"Savage.h"
#include"Loong.h"


int main()
{
	Initialize();
	LoadTemps("Character/");
	LoadMap("Map/test.map");
	int troop[] = { 0,1,2,3 };
	ChooseTroop(0, troop);
	ChooseTroop(1, troop);
	AddStation(7, 7);
	AddStation(-7, -7);
	AddStation(0, 5);
	AddStation(0, -5);
	AddStation(6, -6);
	AddStation(-6, 6);
	
	GameUnit base;
	int baseid[2];
	base.attack = 0;
	base.attack_buff = 0;
	base.attack_range_far = 0;
	base.attack_range_far_buff = 0;
	base.attack_range_near = 0;
	base.attack_range_near_buff = 0;
	base.health = 30;
	base.health_limit = 30;
	base.health_buff = 0;
	base.height = 0;
	base.move_range = 0;
	base.move_range_buff = 0;
	base.pos = Pos(7, 7, 0);
	base.status = 0;
	base.unit_type = -1;
	base.level = 0;
	base.pid = 0;
	baseid[0] = summon(base);
	base.pos = Pos(-7, -7, 0);
	base.pid = 1;
	baseid[1] = summon(base);
	//return 0;
	SetMana(0, 1);
	SetMana(1, 2);
	int round = 0, state = 0;
	while (true)
	{
		PrintWorldStatus();
		printf("Round:%d Player:%d\n", round, round & 1);
		if (!state)
		{
			StartRound(round & 1);
			state = 1;
		}
		else
		{
			cout << ">";
			string order;
			cin >> order;
			if(order=="end")
			{
				EndRound(round & 1);
				round++;
				state = 0;
			}
			else if (order=="summon")
			{
				int type,level,x,y;
				cin >> type >> level >> x >> y;
				Summon(round & 1, type, level, Pos(x, y, 0));
			}
			else if (order == "move")
			{
				int uid, x, y;
				cin >> uid >> x >> y;
				Move(round & 1, uid, Pos(x, y, 0));
			}
			else if (order == "attack")
			{
				int uid, targuid;
				cin >> uid >> targuid;
				Attack(round & 1, uid, targuid);
			}
		}
		CalcHalo();
	}

}
/*
summon 3 0 6 6
end
summon 2 0 -6 -6
end
summon 3 1 6 7
move 2 7 6
end
move 3 -1 -1
end
end
move 3 4 4
end
end
move 3 6 6
*/