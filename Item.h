#pragma once
#include <string>
#include "Stats.h"

using namespace std;

class Item
{
private:
	string name;
	Stats* stats;
	int minLevel;

public:
	static int itemCount;

	Item(string n, Stats* stats);
	Item(string n, Stats* stats, int ml);
	~Item();

	void Print();

	string GetName();
	Stats* GetStats();
	int GetMinLevel();
};

