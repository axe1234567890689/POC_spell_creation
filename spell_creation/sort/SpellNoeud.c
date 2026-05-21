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

    noeudInfos[NT_EFFECT_SET_COLOR].nbInput = 4;
    noeudInfos[NT_EFFECT_SET_COLOR].nbOutput = 1;

    noeudInfos[NT_DEBUG_PRINTF].nbInput = 1;
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
