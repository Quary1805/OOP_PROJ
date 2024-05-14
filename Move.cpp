#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Move.h"

using namespace std;

Move::Move(string n, int pow, bool mag, float acc)
{
	this->name = n;
	this->power = pow;
	this->isMagic = mag;
	this->accuracy = acc;
}

string Move::GetName()
{
	return this->name;
}

int Move::GetPower()
{
	return this->power;
}

bool Move::GetIsMagic()
{
	return this->isMagic;
}

Move::Move(string n, int pow, bool mag) : Move::Move(n, pow, mag, 0.9) {};

bool Move::Success()
{
	srand(time(0));
	return ((float)(rand() % 1001) / 1000) <= this->accuracy; // 0 - 1000 -> 0.000 - 1.000
}
