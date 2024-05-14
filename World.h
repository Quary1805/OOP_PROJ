#pragma once
#include "Entity.h"
#include "EntityDef.h"
#include "Item.h"
#include <string>
#include <vector>

using namespace std;

class World
{
private:
	vector<Entity*>* entities;
	vector<EntityDef*>* species;
	vector<Item*>* items;

	Player* player;
public:
	World();
	~World();

	void NewItem(Item* i);
	void NewEntityDef(EntityDef* ed);
	Entity* CreatePlayer(string n);
	Entity* CreateEnemyFromDef(EntityDef* def, int level);
	Entity* CreateEnemyFromDef(string defname, int level);

	Enemy* GetEnemyByName(string n);
	EntityDef* GetEntityDefByName(string n);
	Item* GetItemByName(string n);
	Player* GetPlayer();
};

