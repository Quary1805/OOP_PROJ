#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Stats.h"

using namespace std;

Stats::Stats(float h, float pd, float pa, float md, float ma, float cc, float cd)
{
    this->health = h;
    this->physicalDamage = pd;
    this->physicalArmor = pa;
    this->magicDamage = md;
    this->magicArmor = ma;
    this->criticalChance = cc;
    this->criticalDamage = cd;
}

Stats::Stats(float h, float pd, float pa, float md, float ma) : Stats::Stats(h, pd, pa, md, ma, 0, 0) {};

void Stats::Print()
{
    cout << "Max Health: " << (this->health > 0 ? "+" : "") << this->health << endl;
    cout << "Physical Damage: " << (this->physicalDamage > 0 ? "+" : "") << this->physicalDamage << endl;
    cout << "Physical Armor: " << (this->physicalArmor > 0 ? " + " : "") << this->physicalArmor << endl;
    cout << "Magic Damage: " << (this->magicDamage > 0 ? "+" : "") << this->magicDamage << endl;
    cout << "Magic Armor: " << (this->magicArmor > 0 ? "+" : "") << this->magicArmor << endl;
    cout << "Critical Chance: " << (this->criticalChance > 0 ? "+" : "") << this->criticalChance*100 << "%" << endl;
    cout << "Critical Damage Multiplier: " << (this->criticalDamage > 0 ? "+" : "") << this->criticalDamage*100 << "%" << endl;
}