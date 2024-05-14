#include <iostream>
#include "World.h"

using namespace std;

int main() {
	World* world = new World();

	// Vytv��en� druh�

	world->NewEntityDef(new EntityDef("Player", new Stats(100, 50, 50, 50, 50, 0.2, 2)));

	world->NewEntityDef(new EntityDef("Dragon", new Stats(1000, 200, 100, 100, 30, 0.1, 4)));

	// Vytv��en� "chmat�"

	Move* sek = new Move("Sek", 30, false);

	Move* chrl = new Move("Chrlen� plamene", 50, true);

	Move* kop = new Move("Kopnut�", 10, false);

	Move* kous = new Move("Kousnut�", 40, false);

	// P�i�ad�me druh�m

	world->GetEntityDefByName("Player")->AddMove(sek);

	world->GetEntityDefByName("Player")->AddMove(kop);

	world->GetEntityDefByName("Dragon")->AddMove(chrl);

	world->GetEntityDefByName("Dragon")->AddMove(kous);

	// Nov� item

	world->NewItem(new Item("Iron Sword", new Stats(0, 30, 0, 0, 0, 0.05, 0.5)));

	Item* mec = world->GetItemByName("Iron Sword");

	// Vytvo��me Igora a d�me mu me�

	world->CreatePlayer("Igor");

	world->GetPlayer()->TryEquip(mec, 1);

	// Vytvo��me Level 40 Draka

	world->CreateEnemyFromDef("Dragon", 40);

	// P�iprav�me si je na fight

	Enemy* drak = world->GetEnemyByName("Lv.40 Dragon");

	Player* igor = world->GetPlayer();

	// D�me Igorovi 48 level up� (1 -> 49);

	igor->LevelUp(48);

	// A pak je�t� dogrindil posledn� (49 -> 50)

	igor->LevelUp();

	// Vyp�eme si je

	igor->Print();

	drak->Print();

	// Do boje!

	while (igor->IsAlive() && drak->IsAlive()) {
		// Hr�� si �tok sm� vybrat, sek je prost� lep��
		igor->Attack(drak);

		// Drak pou��v� n�hodn� tah
		drak->Attack(igor);
	}

	// Z mrtv�ho ud�l�me abstraktn�ho ducha (lep�� to b�t nem��e :D)

	AbstractEntity* duch;
	if (igor->IsAlive())
		duch = drak;
	else
		duch = igor;

	// A kdo n�m um�el?

	duch->Print();

	delete world;
}