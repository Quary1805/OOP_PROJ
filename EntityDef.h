#pragma once

#include "Stats.h"
#include "Move.h"
#include <string>
#include <vector>

class Entity;

class EntityDef
{
private:
	string name;
	Stats* stats;
	vector<Move*>* moves;

public:
	static int entityDefCount;

	EntityDef(string n, Stats* stats);
	~EntityDef();

	void AddMove(Move* move);
	string GetName();
	Stats* GetStats();
	vector<Move*>* GetMoves();
	Entity* CreateEnemy(int level);
	Entity* CreatePlayer(string n);
};