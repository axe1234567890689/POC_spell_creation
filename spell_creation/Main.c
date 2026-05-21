#include <SFML/Graphics.h>
#include "tools/header/clock.h"
#include "sort/header/Spell.h"
#include "Player/header/Player.h"
#include <stdlib.h>

int main(int argc, char** argv) {
	clock_create();

	entity_init();
	spell_init();
	spellNoeud_init();


	sfRenderWindow* window = sfRenderWindow_create((sfVideoMode) { 1920., 1080., 32 }, "test magique", sfDefaultStyle, NULL);
	srand(window);

	sfEvent event;

	Entity* testPlayer = entity_create((sfVector2f) { 960., 540. });

	Spell* sort = spell_create(testPlayer, -1);
	sort->nbNoeud = 3;
	sort->noeuds = calloc(sort->nbNoeud, sizeof(Noeud));
	noeud_create(&sort->noeuds[0], NT_DECLENCHEUR_ON_TICK);
	noeud_create(&sort->noeuds[1], NT_CONST_RANDOM);
	noeud_create(&sort->noeuds[2], NT_EFFECT_SET_COLOR);

	sort->noeudDeclencheurs[0] = &sort->noeuds[0];

	sort->noeuds[0].connectedNoeudOut[0].nbOut = 1;
	sort->noeuds[0].connectedNoeudOut[0].value = calloc(sort->noeuds[0].connectedNoeudOut[0].nbOut, sizeof(Out));
	sort->noeuds[0].connectedNoeudOut[0].value[0].noeud = &sort->noeuds[1];
	sort->noeuds[0].connectedNoeudOut[0].value[0].posInNoeud = 0;

	sort->noeuds[1].connectedNoeudOut[1].nbOut = 3;
	sort->noeuds[1].connectedNoeudOut[1].value = calloc(sort->noeuds[1].connectedNoeudOut[1].nbOut, sizeof(Out));
	sort->noeuds[1].connectedNoeudOut[1].value[0].noeud = &sort->noeuds[2];
	sort->noeuds[1].connectedNoeudOut[1].value[0].posInNoeud = 1;
	sort->noeuds[1].connectedNoeudOut[1].value[1].noeud = &sort->noeuds[2];
	sort->noeuds[1].connectedNoeudOut[1].value[1].posInNoeud = 2;
	sort->noeuds[1].connectedNoeudOut[1].value[2].noeud = &sort->noeuds[2];
	sort->noeuds[1].connectedNoeudOut[1].value[2].posInNoeud = 3;
	sort->noeuds[1].save = 39.f;

	sort->nbNoeudMaxByTick = 1;

	while (sfRenderWindow_isOpen(window)) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			switch (event.type) {
			case sfEvtClosed:
				sfRenderWindow_close(window);
				break;
			case sfEvtKeyPressed:
				switch (event.key.scancode) {
				case sfScanEscape:
					sfRenderWindow_close(window);
					break;
				}
				break;
			}
		}

		clock_update();

		spell_updates();
		entity_updates();


		sfRenderWindow_clear(window, sfBlack);

		entity_draw(window);
		spell_draw(window);

		sfRenderWindow_display(window);

	}
	spell_destroyAll();
	entity_destroyAll();
	sfRenderWindow_destroy(window);
}
