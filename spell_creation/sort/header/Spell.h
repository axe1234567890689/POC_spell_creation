#pragma once

#include "SFML/Graphics.h"
#include "../../Player/header/Player.h"
#include "SpellNoeud.h"

typedef struct Spell Spell;
typedef struct Player Player;

enum SpellParametre {
	SPELL_HAVE_TARGET = 1 << 0,
};

typedef struct MSG MSG;
struct MSG {
	MSG* next;
	unsigned int id;
	float message;
};

struct Spell {
	Spell* next;

	int parametre;
	// 0b0000_0000_0000_0000_0000_0000_0000_0001 target?

	int nbNoeud;
	Noeud* noeuds; // une list
	Noeud** noeudDeclencheurs[NB_DECLENCHEUR]; // une liste de liste de pointeur de declencheur
	Noeud* noeudsActif; // une list chaine
	Entity* sender;

	float timeBeetweenTick;
	float tickTimer;
	int nbNoeudUse;
	int nbNoeudMaxByTick;

	float massVol;
	float radius;
	float perimetre;
	float mana;
	float manaMax;

	float speedCap;
	sfVector2f force;
	sfVector2f speed;
	sfVector2f pos;
	float direction;
	sfVector2f target;
	float directionCible;
	sfColor color;

	float perteSecond;

	float spellFindRadius;
	int nbSpellFind;
	Spell** spells; // list des spells detecte;
	float entityFindRadius;
	int nbEntityFind;
	Entity** entitys; // list des mobs detecte
};

void spell_init();

Spell* spell_create(Entity* _sender, float _manaMax);

void spell_updates();

void drawOneSpell(sfRenderWindow* _window, Spell* _spell);
void spell_draw(sfRenderWindow* _window);

void spell_destroy(Spell* _spell);
void spell_destroyAll();
