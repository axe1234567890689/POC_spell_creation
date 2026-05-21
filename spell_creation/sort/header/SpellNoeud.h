#pragma once

typedef char NT;
typedef float* In;
typedef struct Noeud Noeud;
typedef struct Spell Spell;
typedef float (*activeNoeud)(Noeud* noeud, Spell* _spell);

enum NT {
	NT_NONE,

	NT_CONST_FLOAT,
	NT_CONST_SAVE,
	NT_CONST_DELAY,
	NT_CONST_RANDOM,

	NT_DECLENCHEUR_ON_TICK,
	NT_DECLENCHEUR_TOUCH_PLAYER,
	NT_DECLENCHEUR_TOUCH_SOMETHING,
	NT_DECLENCHEUR_IS_ARRIVED_TO,
	NT_DECLENCHEUR_RANGE_WITH_SENDER,
	NT_DECLENCHEUR_MANA_USE,
	NT_DECLENCHEUR_MANA_LEFT,
	NT_DECLENCHEUR_COLOR_HAS_CHANGED,
	NT_DECLENCHEUR_RECEIVED_MESSAGE,
#define NB_DECLENCHEUR 9

	NT_COND_EQUAL,
	NT_COND_LITTER_THAN,
	NT_COND_GREATTER_THAN,
	NT_COND_LITTER_OR_EQUAL_THAN,
	NT_COND_GREATTER_OR_EQUAL_THAN,
	NT_COND_INVERT,

	NT_INPUT_CURRENT_POS,
	NT_INPUT_TARGET_POS,
	NT_INPUT_COLOR,
	NT_INPUT_SPEED,
	NT_INPUT_FORCE,
	NT_INPUT_DIRECTION,
	NT_INPUT_GET_LAST_SPELL,
	NT_INPUT_GET_LAST_MOB,
	NT_INPUT_GET_NB_SPELL_LEFT,
	NT_INPUT_GET_NB_MOB_LEFT,
	NT_INPUT_SENDER,
	NT_INPUT_DIRECTION_TO,
	NT_INPUT_MANA_USE,
	NT_INPUT_MANA_STORE,
	NT_INPUT_MAX_MANA,
	NT_INPUT_PERTE_SECOND,
	NT_INPUT_NB_NOEUD_THIS_TICK,

	NT_EFFECT_GO_TO,
	NT_EFFECT_SET_SPEED_AT,
	NT_EFFECT_NEW_TARGET,
	NT_EFFECT_MOB_DETECTION_RADIUS,
	NT_EFFECT_SPELL_DETECTION_RADIUS,
	NT_EFFECT_MOB_DETECTION,
	NT_EFFECT_SPELL_DETECTION,
	NT_EFFECT_SET_DIRECTION,
	NT_EFFECT_SET_COLOR,
	NT_EFFECT_RADIUS_OF_SPELL, // radius = sqrt(POID DU MANA / (LA MASSE VOLUMIQUE * 3.14))
	NT_EFFECT_VOLUMIQUE_MASS,  // LA MASSE VOLUMIQUE = POID DU MANA / SURFACE
	NT_EFFECT_SET_TICK_PER_SECOND,
	NT_EFFECT_SET_MAX_NOEUD_BY_TICK,

	NT_DEBUG_PRINTF,

	NB_NT,
};

typedef struct NoeudInfo {
	unsigned char nbInput;
	unsigned char nbOutput;
	activeNoeud noeudActions;
} NoeudInfo;

typedef struct Out {
	Noeud* noeud;
	unsigned char posInNoeud;
} Out;

typedef struct Outs {
	unsigned int nbOut;
	Out* value;
} Outs;

struct Noeud {
	Noeud* next;
	NT type;
	int modified;
	int nbIn;
	In connectedNoeudIn;
	int nbOut;
	Outs* connectedNoeudOut;
	float save;
};

void spellNoeud_init();
void spellNoeud_addOneAction(NT _noeudType, activeNoeud _fonctionAction);

void noeud_create(Noeud* _noeud, NT _type);

float noeud_update(Noeud* _noeud, Spell* _spell);
void modifAllLinked(Noeud* _lastNoeud, Outs* _outputs, float _value);
void modif(Noeud* _lastNoeud, Noeud* _targetNoeud, unsigned char _target, float _value);
