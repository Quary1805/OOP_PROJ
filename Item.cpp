#include <iostream>
#include "Item.h"

using namespace std;

int Item::itemCount = 0;

Item::Item(string n, Stats* stats, int ml)
{
	this->name = n;
	this->stats = stats;
	this->minLevel = ml;

	this->itemCount++;
}

Item::Item(string n, Stats* stats) : Item::Item(n, stats, 1) {}

void Item::Print()
{
	cout << this->name << endl;
	cout << "Level " << this->minLevel << endl;
	cout << "---------------------------------" << endl;
	this->stats->Print();
}

string Item::GetName()
{
	return this->name;
}

Stats* Item::GetStats()
{
	return this->stats;
}

int Item::GetMinLevel()
{
	return this->minLevel;
}

Item::~Item() {
	this->itemCount--;
	delete stats;
}