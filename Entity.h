#pragma once
#include "Move.h"
#include "Stats.h"
#include "EntityDef.h"
#include "Item.h"
#include <string>
#include <vector>

class AbstractEntity {
public:
	virtual float Attack(Entity* who) = 0;
	virtual void Print() = 0;
	virtual void RecalculateStats() = 0;
	virtual string GetName() = 0;
	virtual bool LoseHealth(float damage) = 0;
};

class Entity : public AbstractEntity
{
protected:
	EntityDef* species;
	float currentHealth;
	string name;
	int level;
	Stats* stats;

public:
	static int entityCount;

	~Entity();

	int GetLevel();
	Stats* GetStats();
	bool IsAlive();
	float GetHealth();
};

class Player : public Entity {
private:
	vector<Item*>* equipment;

public:
	void LevelUp();
	void LevelUp(int levels);
	bool TryEquip(Item* i, int slot);
	float Attack(Move* mov, Entity* who);
	virtual float Attack(Entity* who) override;
	virtual void Print() override;
	virtual void RecalculateStats() override;
	virtual string GetName() override;
	virtual bool LoseHealth(float damage) override;

	vector<Item*>* GetEquipment();

	Player(string n, EntityDef* species);
	~Player();
};

class Enemy : public Entity {
public:
	virtual float Attack(Entity* who) override;
	virtual void Print() override;
	virtual void RecalculateStats() override;
	virtual string GetName() override;
	virtual bool LoseHealth(float damage) override;

	Enemy(string n, int level, EntityDef* species);
	~Enemy();
};