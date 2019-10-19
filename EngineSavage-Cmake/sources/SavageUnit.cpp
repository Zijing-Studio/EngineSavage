#include "SavageUnit.h"

GameUnitModel GameUnit::GetUnitModel() const
{
	GameUnitModel ret;
	ret.pid = pid;
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

void GameUnitModel::Print() const
{
	SavageLog("\n{\n\tpid:%d\n", pid);
	SavageLog("\tunit_type:%d\n", unit_type);
	SavageLog("\thealth:%d\n", health);
	SavageLog("\thealth_limit:%d\n", health_limit);
	SavageLog("\tattack:%d\n", attack);
	SavageLog("\tattack_range_near:%d\n", attack_range_near);
	SavageLog("\tattack_range_far:%d\n", attack_range_far);
	SavageLog("\tmove_range:%d\n", move_range);
	SavageLog("\tstatus:%d\n", status);
	SavageLog("\tpos:(%d,%d)\n", pos.x, pos.y);
	SavageLog("\theight:%d\n}\n", height);
}
