#include "header/SpellActions.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// envoie un float predefinie au noeuds connectee
float NoeudAction_Const_Float(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _noeud->save);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	return 0.1f;
}

// envoie un float random entre 0. et 1. au noeuds connectee
float NoeudAction_Const_Random(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], ((float)rand() / (float)RAND_MAX));
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	return 0.5f;
}

// envoie le dernier float qu'il as reçue au noeuds connectee
float NoeudAction_Const_Copy(Noeud* _noeud, Spell* _spell) {
	if (_noeud->modified & 0b10)
		_noeud->save = _noeud->connectedNoeudIn[1];
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _noeud->save);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	return 0.2f;
}

// envoie le dernier float qu'il as reçue au noeuds connectee ou reçois un float
float NoeudAction_Const_Delay(Noeud* _noeud, Spell* _spell) {
	if (_noeud->modified & 0b10) {
		_noeud->save = _noeud->connectedNoeudIn[1];
	} else {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _noeud->save);
	}
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);

	return 0.2f;
}


// renvoie 1. si a et b sont egau sinon renvoie rien
float NoeudAction_Cond_Equal(Noeud* _noeud, Spell* _spell) {
	if (_noeud->connectedNoeudIn[1] == _noeud->connectedNoeudIn[2]) {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], 1.f);
	}
	else {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 0.f);
	}

	return 0.4f;
}

// renvoie 1. si a < b sinon renvoie rien
float NoeudAction_Cond_SmallerThan(Noeud* _noeud, Spell* _spell) {
	if (_noeud->connectedNoeudIn[1] < _noeud->connectedNoeudIn[2]) {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], 1.f);
	}
	else {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 0.f);
	}

	return 0.4f;
}

// renvoie 1. si a > b sinon renvoie rien
float NoeudAction_Cond_BiggerThan(Noeud* _noeud, Spell* _spell) {
	if (_noeud->connectedNoeudIn[1] > _noeud->connectedNoeudIn[2]) {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], 1.f);
	}
	else {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 0.f);
	}

	return 0.4f;
}

// renvoie 1. si a <= b sinon renvoie rien
float NoeudAction_Cond_SmallerThanOrEqual(Noeud* _noeud, Spell* _spell) {
	if (_noeud->connectedNoeudIn[1] <= _noeud->connectedNoeudIn[2]) {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], 1.f);
	}
	else {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 0.f);
	}

	return 0.4f;
}

// renvoie 1. si a >= b sinon renvoie rien
float NoeudAction_Cond_BiggerThanOrEqual(Noeud* _noeud, Spell* _spell) {
	if (_noeud->connectedNoeudIn[1] >= _noeud->connectedNoeudIn[2]) {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], 1.f);
	}
	else {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 0.f);
	}

	return 0.4f;
}

// renvoie 1. si a >= b sinon renvoie rien
float NoeudAction_Cond_Invert(Noeud* _noeud, Spell* _spell) {
	if (_noeud->connectedNoeudIn[1] == 0.f) {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], 1.f);
	}
	else {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 0.f);
	}

	return 0.4f;
}

// renvoie la position du sort
float NoeudAction_Input_getPos(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->pos.x);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[2], _spell->pos.y);

	return 0.3f;
}

// renvoie la position de la target
float NoeudAction_Input_getTargetPos(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->target.x);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[2], _spell->target.y);

	return 0.3f;
}

// renvoie la coulleur
float NoeudAction_Input_getColor(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->color.r / 255.);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[2], _spell->color.b / 255.);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[3], _spell->color.b / 255.);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	return 4.f;
}

// renvoie la vitesse (x et y)
float NoeudAction_Input_getSpeed(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->speed.x);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[2], _spell->speed.y);

	return 0.3f;
}

// renvoie la force (x et y)
float NoeudAction_Input_getForce(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->force.x);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[2], _spell->force.y);

	return 0.3f;
}

// renvoie la direction
float NoeudAction_Input_getDirection(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->direction);

	return 0.3f;
}

// renvoie le premier spell de la list
float NoeudAction_Input_getLastSpell(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	if (_spell->nbSpellFind < 1) return 0.2;
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->spells[0]->pos.x);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[2], _spell->spells[0]->pos.y);
	_spell->nbSpellFind--;
	for (int i = 0; i < _spell->nbSpellFind; i++) {
		_spell->spells[i] = _spell->spells[i + 1];
	}

	return 0.5f + 0.1 * _spell->nbEntityFind;
}

// renvoie le premier mob de la list
float NoeudAction_Input_getLastMob(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	if (_spell->nbEntityFind < 1) return 0.2;
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->entitys[0]->pos.x);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[2], _spell->entitys[0]->pos.y);
	_spell->nbEntityFind--;
	for (int i = 0; i < _spell->nbEntityFind; i++) {
		_spell->entitys[i] = _spell->entitys[i + 1];
	}

	return 0.5f + 0.1 * _spell->nbEntityFind;
}

// renvoie le nombre de spell dans la list
float NoeudAction_Input_getNbSpell(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->nbSpellFind);
	return 0.2f;
}

// renvoie le nombre de mob dans la list
float NoeudAction_Input_getNbMob(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->nbEntityFind);
	return 0.2f;
}

float NoeudAction_Input_getSender(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->sender->pos.x);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[2], _spell->sender->pos.y);

	return 0.2f;
}

float NoeudAction_Input_getDirectionTo(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	sfVector2f dir = { _noeud->connectedNoeudIn[1] - _spell->pos.x, _noeud->connectedNoeudIn[2] - _spell->pos.y };
	float angle = atan2f(dir.y, dir.x);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], angle);

	return 0.2f;
}

float NoeudAction_Input_getManaUse(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->manaMax - _spell->mana);

	return 0.3f;
}

float NoeudAction_Input_getManaLeft(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->mana);

	return 0.2f;
}

float NoeudAction_Input_getMaxMana(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->manaMax);

	return 0.2f;
}

float NoeudAction_Input_getPerte(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _spell->perimetre * _spell->massVol / 100.);

	return 0.5f;
}

float NoeudAction_Input_getNBNoeudUse(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], (float) _spell->nbNoeudUse);

	return 0.2f;
}


float NoeudAction_Effect_Color(Noeud* _noeud, Spell* _spell) {
	_spell->color.r = _noeud->connectedNoeudIn[1] * 255.f;
	_spell->color.g = _noeud->connectedNoeudIn[2] * 255.f;
	_spell->color.b = _noeud->connectedNoeudIn[3] * 255.f;
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.f);

	return 4.f;
}

float NoeudAction_Debug_Printf(Noeud* _noeud, Spell* _spell) {
	printf("[DEBUG] Noeud: ce noeud a ressue une valeur des %f\n", _noeud->connectedNoeudIn[1]);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.);
	return 0.f;
}

void spellAction_init()
{
	spellNoeud_addOneAction(NT_CONST_FLOAT, NoeudAction_Const_Float);
	spellNoeud_addOneAction(NT_CONST_SAVE, NoeudAction_Const_Copy);
	spellNoeud_addOneAction(NT_CONST_DELAY, NoeudAction_Const_Delay);
	spellNoeud_addOneAction(NT_CONST_RANDOM, NoeudAction_Const_Random);

	spellNoeud_addOneAction(NT_COND_EQUAL, NoeudAction_Cond_Equal);
	spellNoeud_addOneAction(NT_COND_LITTER_THAN, NoeudAction_Cond_SmallerThan);
	spellNoeud_addOneAction(NT_COND_GREATTER_THAN, NoeudAction_Cond_BiggerThan);
	spellNoeud_addOneAction(NT_COND_LITTER_OR_EQUAL_THAN, NoeudAction_Cond_SmallerThanOrEqual);
	spellNoeud_addOneAction(NT_COND_GREATTER_OR_EQUAL_THAN, NoeudAction_Cond_BiggerThanOrEqual);
	spellNoeud_addOneAction(NT_COND_INVERT, NoeudAction_Cond_Invert);

	spellNoeud_addOneAction(NT_INPUT_CURRENT_POS, NoeudAction_Input_getPos);
	spellNoeud_addOneAction(NT_INPUT_TARGET_POS, NoeudAction_Input_getTargetPos);
	spellNoeud_addOneAction(NT_INPUT_COLOR, NoeudAction_Input_getColor);
	spellNoeud_addOneAction(NT_INPUT_SPEED, NoeudAction_Input_getSpeed);
	spellNoeud_addOneAction(NT_INPUT_FORCE, NoeudAction_Input_getForce);
	spellNoeud_addOneAction(NT_INPUT_DIRECTION, NoeudAction_Input_getDirection);
	spellNoeud_addOneAction(NT_INPUT_GET_LAST_SPELL, NoeudAction_Input_getLastSpell);
	spellNoeud_addOneAction(NT_INPUT_GET_LAST_MOB, NoeudAction_Input_getLastMob);
	spellNoeud_addOneAction(NT_INPUT_GET_NB_SPELL_LEFT, NoeudAction_Input_getNbSpell);
	spellNoeud_addOneAction(NT_INPUT_GET_NB_MOB_LEFT, NoeudAction_Input_getNbMob); 
	spellNoeud_addOneAction(NT_INPUT_SENDER, NoeudAction_Input_getSender);
	spellNoeud_addOneAction(NT_INPUT_DIRECTION_TO, NoeudAction_Input_getDirectionTo);
	spellNoeud_addOneAction(NT_INPUT_MANA_USE, NoeudAction_Input_getManaUse);
	spellNoeud_addOneAction(NT_INPUT_MANA_STORE, NoeudAction_Input_getManaLeft);
	spellNoeud_addOneAction(NT_INPUT_MAX_MANA, NoeudAction_Input_getMaxMana);
	spellNoeud_addOneAction(NT_INPUT_PERTE_SECOND, NoeudAction_Input_getPerte);
	spellNoeud_addOneAction(NT_INPUT_NB_NOEUD_THIS_TICK, NoeudAction_Input_getNBNoeudUse);

	spellNoeud_addOneAction(NT_EFFECT_SET_COLOR, NoeudAction_Effect_Color);

	spellNoeud_addOneAction(NT_DEBUG_PRINTF, NoeudAction_Debug_Printf);
}