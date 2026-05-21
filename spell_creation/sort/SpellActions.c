#include "header/SpellActions.h"
#include <stdlib.h>
#include <stdio.h>

float NoeudAction_Const_Float(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _noeud->save);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.);
	return 0.1f;
}

float NoeudAction_Const_Random(Noeud* _noeud, Spell* _spell) {
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], ((float)rand() / (float)RAND_MAX));
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.);
	return 0.5f;
}

float NoeudAction_Const_Copy(Noeud* _noeud, Spell* _spell) {
	if (_noeud->modified & 0b10)
		_noeud->save = _noeud->connectedNoeudIn[1];
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _noeud->save);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.);
	return 0.2f;
}

float NoeudAction_Const_Delay(Noeud* _noeud, Spell* _spell) {
	if (_noeud->modified & 0b10) {
		_noeud->save = _noeud->connectedNoeudIn[1];
	} else {
		modifAllLinked(_noeud, &_noeud->connectedNoeudOut[1], _noeud->save);
	}
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.);

	return 0.2f;
}

float NoeudAction_Effect_Color(Noeud* _noeud, Spell* _spell) {
	_spell->color.r = _noeud->connectedNoeudIn[1] * 255.;
	_spell->color.g = _noeud->connectedNoeudIn[2] * 255.;
	_spell->color.b = _noeud->connectedNoeudIn[3] * 255.;
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.);
	return 4.;
}

float NoeudAction_Debug_Printf(Noeud* _noeud, Spell* _spell) {
	printf("[DEBUG] Noeud: ce noeud a ressue une valeur des %.3f\n", _noeud->connectedNoeudIn[1]);
	modifAllLinked(_noeud, &_noeud->connectedNoeudOut[0], 1.);
	return 0.f;
}

void spellAction_init()
{
	spellNoeud_addOneAction(NT_CONST_FLOAT, NoeudAction_Const_Float);
	spellNoeud_addOneAction(NT_CONST_SAVE, NoeudAction_Const_Copy);
	spellNoeud_addOneAction(NT_CONST_DELAY, NoeudAction_Const_Delay);
	spellNoeud_addOneAction(NT_CONST_RANDOM, NoeudAction_Const_Random); 

	spellNoeud_addOneAction(NT_EFFECT_SET_COLOR, NoeudAction_Effect_Color);

	spellNoeud_addOneAction(NT_DEBUG_PRINTF, NoeudAction_Debug_Printf);
}
