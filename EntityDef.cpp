#include "EntityDef.h"
#include "Stats.h"
#include "Move.h"
#include "Entity.h"
#include <string>
#include <iostream>

using namespace std;

int EntityDef::entityDefCount = 0;

EntityDef::EntityDef(string n, Stats* stats)
{
	this->name = n;
	this->stats = stats;
	this->moves = new vector<Move*>;

	this->entityDefCount++;
}

EntityDef::~EntityDef() {
	this->entityDefCount--;
	if (moves != nullptr) {
		for (Move* move : *moves) {
			delete move;
		}
		delete moves;
	}
}

void EntityDef::AddMove(Move* move)
{
	this->moves->push_back(move);
}

string EntityDef::GetName()
{
	return this->name;
}

Stats* EntityDef::GetStats()
{
	return this->stats;
}

vector<Move*>* EntityDef::GetMoves()
{
	return this->moves;
}

Entity* EntityDef::CreateEnemy(int level)
{
	if (this->name == "Player")
		return nullptr;
	return new Enemy(this->name, level, this);
}

Entity* EntityDef::CreatePlayer(string n)
{
	if (this->name != "Player")
		return nullptr;
	return new Player(this->name, this);
}
