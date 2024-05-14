#include <iostream>
#include "World.h"

using namespace std;

int main() {
	World* world = new World();

	// Vytváøení druhù

	world->NewEntityDef(new EntityDef("Player", new Stats(100, 50, 50, 50, 50, 0.2, 2)));

	world->NewEntityDef(new EntityDef("Dragon", new Stats(1000, 200, 100, 100, 30, 0.1, 4)));

	// Vytváøení "chmatù"

	Move* sek = new Move("Sek", 30, false);

	Move* chrl = new Move("Chrlení plamene", 50, true);

	Move* kop = new Move("Kopnutí", 10, false);

	Move* kous = new Move("Kousnutí", 40, false);

	// Pøiøadíme druhùm

	world->GetEntityDefByName("Player")->AddMove(sek);

	world->GetEntityDefByName("Player")->AddMove(kop);

	world->GetEntityDefByName("Dragon")->AddMove(chrl);

	world->GetEntityDefByName("Dragon")->AddMove(kous);

	// Nový item

	world->NewItem(new Item("Iron Sword", new Stats(0, 30, 0, 0, 0, 0.05, 0.5)));

	Item* mec = world->GetItemByName("Iron Sword");

	// Vytvoøíme Igora a dáme mu meè

	world->CreatePlayer("Igor");

	world->GetPlayer()->TryEquip(mec, 1);

	// Vytvoøíme Level 40 Draka

	world->CreateEnemyFromDef("Dragon", 40);

	// Pøipravíme si je na fight

	Enemy* drak = world->GetEnemyByName("Lv.40 Dragon");

	Player* igor = world->GetPlayer();

	// Dáme Igorovi 48 level upù (1 -> 49);

	igor->LevelUp(48);

	// A pak ještì dogrindil poslední (49 -> 50)

	igor->LevelUp();

	// Vypíšeme si je

	igor->Print();

	drak->Print();

	// Do boje!

	while (igor->IsAlive() && drak->IsAlive()) {
		// Hráè si útok smí vybrat, sek je prostì lepší
		igor->Attack(drak);

		// Drak používá náhodný tah
		drak->Attack(igor);
	}

	// Z mrtvého udìláme abstraktního ducha (lepší to být nemùže :D)

	AbstractEntity* duch;
	if (igor->IsAlive())
		duch = drak;
	else
		duch = igor;

	// A kdo nám umøel?

	duch->Print();

	delete world;
}