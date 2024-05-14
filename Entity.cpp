#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "Entity.h"

using namespace std;

int Entity::entityCount = 0;

void Player::LevelUp()
{
	this->level++;
	this->RecalculateStats();
}

void Player::LevelUp(int levels)
{
	this->level += levels;
	this->RecalculateStats();
}

bool Player::TryEquip(Item* i, int slot)
{
	if (slot < 0 || slot > 2)
		return false;

	this->equipment->at(slot) = i;
	this->RecalculateStats();
	return true;
}

float Player::Attack(Move* mov, Entity* who)
{
	bool canUse = false;
	for (int i = 0; i < this->species->GetMoves()->size(); i++)
	{
		if (mov == this->species->GetMoves()->at(i))
			canUse = true;
	}

	if (!mov->Success() || !canUse)
		return 0.0f;

	srand(time(0));
	float critMult = (((float)(rand() % 10000) / 10000) <= this->stats->criticalChance) ? this->stats->criticalDamage : 1;
	float dmg = mov->GetPower() * critMult * (mov->GetIsMagic() ? (this->stats->magicDamage / who->GetStats()->magicArmor) : (this->stats->physicalDamage / who->GetStats()->physicalArmor));

	who->LoseHealth(dmg);
	return dmg;
}

float Player::Attack(Entity* who)
{
	srand(time(0));
	return this->Attack(this->species->GetMoves()->at(rand() % this->species->GetMoves()->size()), who);
}

void Player::Print()
{
	cout << "=================================" << endl;
	if (this->currentHealth <= 0)
		cout << "           - D E A D -           " << endl;
	cout << "               YOU               " << endl;
	cout << this->name << endl;
	cout << "Level " << this->level << endl;
	cout << "Health " << this->currentHealth << " / " << this->stats->health << endl;
	cout << "=================================" << endl;
	cout << "            EQUIPMENT            " << endl;

	int equipmentCount = 0;

	for (int i = 0; i < 3; i++)
	{
		if (this->equipment->at(i) != nullptr)
		{
			cout << "---------------------------------" << endl;
			this->equipment->at(i)->Print();
		}
	}

	if (equipmentCount == 0) {
		cout << "---------------------------------" << endl;
		cout << "No equipment equiped." << endl;
	}

	cout << "=================================" << endl;
	cout << "              STATS              " << endl;
	this->stats->Print();
	cout << "=================================" << endl;
}

void Player::RecalculateStats()
{
	float missingHealth = this->stats->health - this->currentHealth;

	this->stats->health = this->species->GetStats()->health * ((20 + this->level) / 20);
	this->stats->physicalDamage = this->species->GetStats()->physicalDamage * ((50 + this->level) / 50);
	this->stats->physicalArmor = this->species->GetStats()->physicalArmor * ((50 + this->level) / 50);
	this->stats->magicDamage = this->species->GetStats()->magicDamage * ((50 + this->level) / 50);
	this->stats->magicArmor = this->species->GetStats()->magicArmor * ((50 + this->level) / 50);
	this->stats->criticalChance = this->species->GetStats()->criticalChance;
	this->stats->criticalDamage = this->species->GetStats()->criticalDamage;

	for (int i = 0; i < this->equipment->size(); i++)
	{
		if (this->equipment->at(i) != nullptr) {
			this->stats->health += this->equipment->at(i)->GetStats()->health;
			this->stats->physicalDamage += this->equipment->at(i)->GetStats()->physicalDamage;
			this->stats->physicalArmor += this->equipment->at(i)->GetStats()->physicalArmor;
			this->stats->magicDamage += this->equipment->at(i)->GetStats()->magicDamage;
			this->stats->magicArmor += this->equipment->at(i)->GetStats()->magicArmor;
			this->stats->criticalChance += this->equipment->at(i)->GetStats()->criticalChance;
			this->stats->criticalDamage += this->equipment->at(i)->GetStats()->criticalDamage;
		}
	}

	this->currentHealth = this->stats->health - missingHealth;
}

string Player::GetName()
{
	return this->name;
}

bool Player::LoseHealth(float damage)
{
	this->currentHealth -= damage;
	if (this->currentHealth <= 0) {
		cout << endl << "=================================" << endl;
		cout << "         Y O U   D I E D         " << endl;
		cout << "=================================" << endl;
		this->currentHealth = 0;
		return false;
	}
	return true;
}

vector<Item*>* Player::GetEquipment()
{
	return this->equipment;
}

Player::Player(string n, EntityDef* species)
{
	this->name = n;
	this->species = species;
	this->currentHealth = species->GetStats()->health;
	this->level = 1;
	this->stats = species->GetStats();
	this->equipment = new vector<Item*>(3);

	this->entityCount++;
}

float Enemy::Attack(Entity* who)
{
	srand(0);
	Move* mov = this->species->GetMoves()->at(rand() % this->species->GetMoves()->size());
	if (!mov->Success())
		return 0.0f;

	srand(time(0));
	float critMult = (((float)(rand() % 10000) / 10000) <= this->stats->criticalChance) ? this->stats->criticalDamage : 1;
	float dmg = mov->GetPower() * critMult * (mov->GetIsMagic() ? (this->stats->magicDamage / who->GetStats()->magicArmor) : (this->stats->physicalDamage / who->GetStats()->physicalArmor));

	who->LoseHealth(dmg);
	return dmg;
}

void Enemy::Print()
{
	cout << "=================================" << endl;
	if (this->currentHealth <= 0)
		cout << "           - D E A D -           " << endl;
	cout << "              ENEMY              " << endl;
	cout << this->name << endl;
	cout << "Level " << this->level << endl;
	cout << "Health " << this->currentHealth << " / " << this->stats->health << endl;
	cout << "=================================" << endl;
	cout << "              STATS              " << endl;
	this->stats->Print();
	cout << "=================================" << endl;
}

void Enemy::RecalculateStats()
{
	this->stats->health = this->species->GetStats()->health * ((20 + this->level) / 20);
	this->stats->physicalDamage = this->species->GetStats()->physicalDamage * ((50 + this->level) / 50);
	this->stats->physicalArmor = this->species->GetStats()->physicalArmor * ((50 + this->level) / 50);
	this->stats->magicDamage = this->species->GetStats()->magicDamage * ((50 + this->level) / 50);
	this->stats->magicArmor = this->species->GetStats()->magicArmor * ((50 + this->level) / 50);
	this->stats->criticalChance = this->species->GetStats()->criticalChance;
	this->stats->criticalDamage = this->species->GetStats()->criticalDamage;

	this->currentHealth = this->stats->health;
}

string Enemy::GetName()
{
	return "Lv." + to_string(this->level) + " " + this->name;
}

bool Enemy::LoseHealth(float damage)
{
	this->currentHealth -= damage;
	if (this->currentHealth <= 0) {
		this->currentHealth = 0;
		return false;
	}
	return true;
}

Enemy::Enemy(string n, int level, EntityDef* species)
{
	this->name = n;
	this->species = species;
	this->stats = this->species->GetStats();
	this->level = level;
	this->currentHealth = stats->health;

	this->entityCount++;

	this->RecalculateStats();
}

int Entity::GetLevel()
{
	return this->level;
}

Stats* Entity::GetStats()
{
	return this->stats;
}

bool Entity::IsAlive()
{
	return this->currentHealth > 0;
}

float Entity::GetHealth()
{
	return this->currentHealth;
}

Entity::~Entity()
{
	this->entityCount--;
	delete stats;
}

Player::~Player() {
	if (equipment != nullptr) {
		delete equipment;
	}
}

Enemy::~Enemy() {
	// Nic navíc, dìdí
}