#pragma once
#include <string>
#include "Stats.h"

using namespace std;

class Move
{
private:
	string name;
	int power;
	bool isMagic;
	float accuracy;

public:

	Move(string n, int pow, bool mag);
	Move(string n, int pow, bool mag, float acc);

	string GetName();
	int GetPower();
	bool GetIsMagic();
	bool Success();
};