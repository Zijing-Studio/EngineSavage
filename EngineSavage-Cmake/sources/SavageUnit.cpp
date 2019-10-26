#include "SavageUnit.h"

GameUnitModel GameUnit::GetUnitModel() const
{
	GameUnitModel ret;
	ret.pid = pid;
	ret.level = level;
	ret.unit_type = unit_type;
	ret.health = health;
	ret.health_limit = health_limit + health_buff;
	ret.attack = attack + attack_buff;
	ret.attack_range_far = attack_range_far + attack_range_far_buff;
	ret.attack_range_near = attack_range_near + attack_range_near_buff;
	ret.move_range = move_range + move_range_buff;
	ret.status = status;
	ret.pos = pos.EliminateZ();
	ret.height = height;
	return ret;
}
