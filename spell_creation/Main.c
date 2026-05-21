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
	sort->nbNoeud = 5;
	sort->noeuds = calloc(sort->nbNoeud, sizeof(Noeud));
	noeud_create(&sort->noeuds[0], NT_CONST_FLOAT);
	noeud_create(&sort->noeuds[1], NT_CONST_FLOAT);
	noeud_create(&sort->noeuds[2], NT_COND_LITTER_THAN);
	noeud_create(&sort->noeuds[3], NT_DEBUG_PRINTF);
	noeud_create(&sort->noeuds[4], NT_DEBUG_PRINTF);

	sort->nbNoeudMaxByTick = 20;

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
