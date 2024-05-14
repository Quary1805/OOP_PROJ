#include <iostream>
#include "World.h"

World::World()
{
	this->player = nullptr;
	this->entities = new vector<Entity*>;
	this->species = new vector<EntityDef*>;
	this->items = new vector<Item*>;
}

void World::NewItem(Item* i)
{
	this->items->push_back(i);
}

void World::NewEntityDef(EntityDef* ed)
{
	this->species->push_back(ed);
}

Entity* World::CreatePlayer(string n)
{
	Entity* player = this->GetEntityDefByName("Player")->CreatePlayer(n);
	this->entities->push_back(player);
	this->player = (Player*)player;
	return player;
}

Entity* World::CreateEnemyFromDef(EntityDef* def, int level)
{
	Entity* enemy = def->CreateEnemy(level);
	this->entities->push_back(enemy);
	return enemy;
}

Entity* World::CreateEnemyFromDef(string defname, int level)
{
	return CreateEnemyFromDef(this->GetEntityDefByName(defname), level);
}

Enemy* World::GetEnemyByName(string n)
{
	for (int i = 0; i < this->entities->size(); i++)
	{
		Entity* current = this->entities->at(i);
		if (current->GetName() == n && current != this->player)
			return dynamic_cast<Enemy*>(current);

	}
	return nullptr;
}

EntityDef* World::GetEntityDefByName(string n)
{
	for (int i = 0; i < this->species->size(); i++)
	{
		EntityDef* current = this->species->at(i);
		if (current->GetName() == n)
			return current;
	}
	return nullptr;
}

Item* World::GetItemByName(string n)
{
	for (int i = 0; i < this->items->size(); i++)
	{
		Item* current = this->items->at(i);
		if (current->GetName() == n)
			return current;
	}
	return nullptr;
}

Player* World::GetPlayer()
{
	return this->player;
}

World::~World() {
	if (entities != nullptr) {
		for (Entity* entity : *entities) {
			delete entity;
		}
		delete entities;
	}

	if (species != nullptr) {
		for (EntityDef* spec : *species) {
			delete spec;
		}
		delete species;
	}

	if (items != nullptr) {
		for (Item* item : *items) {
			delete item;
		}
		delete items;
	}
}