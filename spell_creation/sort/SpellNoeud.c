#include "header/SpellNoeud.h"
#include "header/SpellActions.h"
#include "../tools/header/ListChaine.h"
#include <stdlib.h>

NoeudInfo noeudInfos[NB_NT];

void spellNoeud_init()
{
    spellAction_init();

    noeudInfos[NT_CONST_FLOAT].nbInput = 1;
    noeudInfos[NT_CONST_FLOAT].nbOutput = 2;

    noeudInfos[NT_CONST_SAVE].nbInput = 2;
    noeudInfos[NT_CONST_SAVE].nbOutput = 2;

    noeudInfos[NT_CONST_DELAY].nbInput = 2;
    noeudInfos[NT_CONST_DELAY].nbOutput = 2;

    noeudInfos[NT_CONST_RANDOM].nbInput = 1;
    noeudInfos[NT_CONST_RANDOM].nbOutput = 2;


    noeudInfos[NT_DECLENCHEUR_ON_TICK].nbInput = 0;
    noeudInfos[NT_DECLENCHEUR_ON_TICK].nbOutput = 1;


    noeudInfos[NT_COND_EQUAL].nbInput = 3;
    noeudInfos[NT_COND_EQUAL].nbOutput = 2;

    noeudInfos[NT_COND_LITTER_THAN].nbInput = 3;
    noeudInfos[NT_COND_LITTER_THAN].nbOutput = 2;

    noeudInfos[NT_COND_GREATTER_THAN].nbInput = 3;
    noeudInfos[NT_COND_GREATTER_THAN].nbOutput = 2;

    noeudInfos[NT_COND_LITTER_OR_EQUAL_THAN].nbInput = 3;
    noeudInfos[NT_COND_LITTER_OR_EQUAL_THAN].nbOutput = 2;

    noeudInfos[NT_COND_GREATTER_OR_EQUAL_THAN].nbInput = 3;
    noeudInfos[NT_COND_GREATTER_OR_EQUAL_THAN].nbOutput = 2;

    noeudInfos[NT_COND_INVERT].nbInput = 2;
    noeudInfos[NT_COND_INVERT].nbOutput = 2;


    noeudInfos[NT_INPUT_CURRENT_POS].nbInput = 1;
    noeudInfos[NT_INPUT_CURRENT_POS].nbOutput = 3;

    noeudInfos[NT_INPUT_TARGET_POS].nbInput = 1;
    noeudInfos[NT_INPUT_TARGET_POS].nbOutput = 3;

    noeudInfos[NT_INPUT_COLOR].nbInput = 1;
    noeudInfos[NT_INPUT_COLOR].nbOutput = 4;

    noeudInfos[NT_INPUT_SPEED].nbInput = 1;
    noeudInfos[NT_INPUT_SPEED].nbOutput = 3;

    noeudInfos[NT_INPUT_FORCE].nbInput = 1;
    noeudInfos[NT_INPUT_FORCE].nbOutput = 3;

    noeudInfos[NT_INPUT_DIRECTION].nbInput = 1;
    noeudInfos[NT_INPUT_DIRECTION].nbOutput = 2;

    noeudInfos[NT_INPUT_GET_LAST_SPELL].nbInput = 1;
    noeudInfos[NT_INPUT_GET_LAST_SPELL].nbOutput = 3; // tout pour avoir un spell

    noeudInfos[NT_INPUT_GET_LAST_MOB].nbInput = 1;
    noeudInfos[NT_INPUT_GET_LAST_MOB].nbOutput = 3; // tout pour avoir un Mob

    noeudInfos[NT_INPUT_GET_NB_SPELL_LEFT].nbInput = 1;
    noeudInfos[NT_INPUT_GET_NB_SPELL_LEFT].nbOutput = 2;

    noeudInfos[NT_INPUT_GET_NB_MOB_LEFT].nbInput = 1;
    noeudInfos[NT_INPUT_GET_NB_MOB_LEFT].nbOutput = 2;

    noeudInfos[NT_INPUT_SENDER].nbInput = 1;
    noeudInfos[NT_INPUT_SENDER].nbOutput = 3; // tout pour avoir un Mob (le sender)

    noeudInfos[NT_INPUT_MANA_USE].nbInput = 1;
    noeudInfos[NT_INPUT_MANA_USE].nbOutput = 2;

    noeudInfos[NT_INPUT_MANA_STORE].nbInput = 1;
    noeudInfos[NT_INPUT_MANA_STORE].nbOutput = 2;

    noeudInfos[NT_INPUT_MAX_MANA].nbInput = 1;
    noeudInfos[NT_INPUT_MAX_MANA].nbOutput = 2;

    noeudInfos[NT_INPUT_PERTE_SECOND].nbInput = 1;
    noeudInfos[NT_INPUT_PERTE_SECOND].nbOutput = 2;

    noeudInfos[NT_INPUT_NB_NOEUD_THIS_TICK].nbInput = 1;
    noeudInfos[NT_INPUT_NB_NOEUD_THIS_TICK].nbOutput = 2;


    noeudInfos[NT_MATH_PLUS].nbInput = 3;
    noeudInfos[NT_MATH_PLUS].nbOutput = 2;

    noeudInfos[NT_MATH_MOINS].nbInput = 3;
    noeudInfos[NT_MATH_MOINS].nbOutput = 2;

    noeudInfos[NT_MATH_FOIS].nbInput = 3;
    noeudInfos[NT_MATH_FOIS].nbOutput = 2;

    noeudInfos[NT_MATH_DIVIDE].nbInput = 3;
    noeudInfos[NT_MATH_DIVIDE].nbOutput = 2;

    noeudInfos[NT_MATH_COS].nbInput = 2;
    noeudInfos[NT_MATH_COS].nbOutput = 2;

    noeudInfos[NT_MATH_SIN].nbInput = 2;
    noeudInfos[NT_MATH_SIN].nbOutput = 2;

    noeudInfos[NT_MATH_ANGLE_TO].nbInput = 3;
    noeudInfos[NT_MATH_ANGLE_TO].nbOutput = 2;


    noeudInfos[NT_EFFECT_SET_FORCE_AT].nbInput = 3;
    noeudInfos[NT_EFFECT_SET_FORCE_AT].nbOutput = 1;

    noeudInfos[NT_EFFECT_SET_COLOR].nbInput = 4;
    noeudInfos[NT_EFFECT_SET_COLOR].nbOutput = 1;


    noeudInfos[NT_DEBUG_PRINTF].nbInput = 2;
    noeudInfos[NT_DEBUG_PRINTF].nbOutput = 1;
}

void spellNoeud_addOneAction(NT _noeudType, activeNoeud _fonctionAction)
{
    noeudInfos[_noeudType].noeudActions = _fonctionAction;
}

void noeud_create(Noeud* _noeud, NT _type)
{
    _noeud->modified = 0;
    _noeud->next = NULL;
    _noeud->type = _type;
    _noeud->nbIn = noeudInfos[_type].nbInput;
    _noeud->connectedNoeudIn = calloc(_noeud->nbIn, sizeof(float));
    _noeud->nbOut = noeudInfos[_type].nbOutput;
    _noeud->connectedNoeudOut = calloc(_noeud->nbOut, sizeof(Out));
}

float noeud_update(Noeud* _noeud, Spell* _spell)
{
    if (_noeud->type == NT_NONE || noeudInfos[_noeud->type].noeudActions == NULL) return;
    return noeudInfos[_noeud->type].noeudActions(_noeud, _spell);
}

void modifAllLinked(Noeud* _lastNoeud, Outs* _outputs, float _value)
{
    for (int i = 0; i < _outputs->nbOut; i++) {
        modif(_lastNoeud, _outputs->value[i].noeud, _outputs->value[i].posInNoeud, _value);
    }
}

void modif(Noeud* _lastNoeud, Noeud* _targetNoeud, unsigned char _target, float _value)
{
    _targetNoeud->connectedNoeudIn[_target] = _value;
    if ((_targetNoeud->modified & (1 << _target)) && 
        ((_targetNoeud->modified & 0b1) == 1 || 
         (_targetNoeud->modified == ((1 << _targetNoeud->nbIn) - 2) && _targetNoeud->nbIn != 1))) return;
    _targetNoeud->modified |= 1 << _target;
    if (_target == 0 || _targetNoeud->modified == ((1 << (_targetNoeud->nbIn)) - 2)) {
        pushBackValue(&_lastNoeud, _targetNoeud);
        _targetNoeud->next = NULL;
    }
}
