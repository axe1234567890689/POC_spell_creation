#include "header/Spell.h"
#include "../Player/header/Player.h"
#include "../tools/header/ListChaine.h"
#include "../tools/header/clock.h"
#include <stdlib.h>
#include <stdio.h>

Spell* firstSpell = NULL;
sfCircleShape* cercle = NULL;

void spell_init()
{
    cercle = sfCircleShape_create();
}

Spell* spell_create(Entity* _sender, float _manaMax)
{
    Spell* newSpell = calloc(1, sizeof(Spell));
	newSpell->next = NULL;

    newSpell->parametre = 0;

    newSpell->nbNoeud = 0;
    newSpell->noeuds = NULL;
    newSpell->noeudsActif = NULL;
    newSpell->sender = _sender;

    newSpell->timeBeetweenTick = 1. / 20.;
    newSpell->tickTimer = 0.f;
    newSpell->nbNoeudUse = 0;
    newSpell->nbNoeudMaxByTick = 10;

    newSpell->massVol = 1.;
    newSpell->radius = 10.;
    newSpell->perimetre = newSpell->radius * newSpell->radius * 3.14;
    newSpell->mana = _manaMax;
    newSpell->manaMax = _manaMax;

    newSpell->speedCap = 10.f;
    newSpell->force = (sfVector2f){ 0., 0. };
    newSpell->speed = (sfVector2f){ 0., 0. };
    newSpell->pos = _sender->pos;
    newSpell->target = (sfVector2f){ 0., 0. };
    newSpell->directionCible = 0.f;
    newSpell->color = sfBlue;

    newSpell->perteSecond = newSpell->perimetre * newSpell->massVol;

    newSpell->spellFindRadius = 1.f;
    newSpell->nbSpellFind = 0;
    newSpell->spells = NULL; // list des spells detecte;
    newSpell->entityFindRadius = 1.f;
    newSpell->nbEntityFind = 0;
    newSpell->entitys = NULL; // list des mobs detecte

    pushFrontValue(&firstSpell, newSpell);

    return newSpell;
}

void updateOneSpell(void* _null, Spell* _spell) {
    if (_spell->noeudDeclencheurs[0] != NULL) {
        for (int i = 0; i < ((Noeud*) _spell->noeudDeclencheurs[0])->connectedNoeudOut->nbOut; i++) {
            Noeud* lastNoeud = (Noeud*)getLast(&_spell->noeudsActif);
            if (lastNoeud != NULL)
                modif(lastNoeud, ((Noeud*)_spell->noeudDeclencheurs[0])->connectedNoeudOut->value[i].noeud, ((Noeud*)_spell->noeudDeclencheurs[0])->connectedNoeudOut->value[i].posInNoeud, 1.);
            else {
                _spell->noeudsActif = ((Noeud*)_spell->noeudDeclencheurs[0])->connectedNoeudOut->value[i].noeud;
            }
        }
    }
    _spell->mana -= (_spell->perimetre * _spell->massVol / 100.) * deltaTime;
    Noeud* current;
    if (_spell->manaMax < 0) {
        while (_spell->noeudsActif != NULL && _spell->nbNoeudUse < _spell->nbNoeudMaxByTick) {
            current = _spell->noeudsActif;
            _spell->mana -= noeud_update(current, _spell) + 0.1 * current->nbOut;
            current->modified = 0;
            _spell->noeudsActif = _spell->noeudsActif->next;
            _spell->nbNoeudUse++;
        }
        //printf("%.2f mana use this tick en utilisant %d noeud\n", -_spell->mana, _spell->nbNoeudUse);
        _spell->mana = 0.;
        _spell->nbNoeudUse = 0;
        return 0;
    }
    while (_spell->noeudsActif != NULL && _spell->nbNoeudUse < _spell->nbNoeudMaxByTick && _spell->mana > 0) {
        current = _spell->noeudsActif;
        _spell->noeudsActif = _spell->noeudsActif->next;
        _spell->mana -= noeud_update(current, _spell) + 0.1 * current->nbOut;
        _spell->nbNoeudUse++;
    }
    _spell->nbNoeudUse = 0;
    if (_spell->mana <= 0) {
        spell_destroy(_spell);
        return 1;
    }
    return 0;
}

void spell_updates()
{
    forAll(&firstSpell, updateOneSpell, NULL);
}

void drawOneSpell(sfRenderWindow* _window, Spell* _spell)
{
    sfCircleShape_setPosition(cercle, _spell->pos);
    sfCircleShape_setRadius(cercle, _spell->radius);
    sfCircleShape_setOrigin(cercle, (sfVector2f) { _spell->radius , _spell->radius });
    sfCircleShape_setFillColor(cercle, _spell->color);

    sfRenderWindow_drawCircleShape(_window, cercle, NULL);
}

void spell_draw(sfRenderWindow* _window)
{
    forAll(&firstSpell, drawOneSpell, _window);
}

void spell_destroy(Spell* _spell)
{
    printf("destruction d'un sort en x : %.3f, y : %.3f\n", _spell->pos.x, _spell->pos.y);
}

void spell_destroyAll()
{
    delAllWith(&firstSpell, spell_destroy);
}
