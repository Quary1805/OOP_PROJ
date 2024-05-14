#pragma once
class Stats
{
public:
	float health;
	float physicalArmor;
	float magicArmor;
	float criticalChance;
	float criticalDamage;
	float physicalDamage;
	float magicDamage;

	Stats(float h, float pd, float pa, float md, float ma);
	Stats(float h, float pd, float pa, float md, float ma, float cc, float cd);

	void Print();
};

