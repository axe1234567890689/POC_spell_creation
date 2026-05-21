#include "header/Entity.h"
#include "../tools/header/ListChaine.h"
#include <stdlib.h>
#include <stdio.h>

Entity* firstEntity = NULL;
sfRectangleShape* rectangle = NULL;

void entity_init()
{
    rectangle = sfRectangleShape_create();
    sfRectangleShape_setSize(rectangle, (sfVector2f) { 25., 25. });
    sfRectangleShape_setFillColor(rectangle, sfGreen);
}

Entity* entity_create(sfVector2f _pos)
{
    Entity* newEntity = malloc(sizeof(Entity));
    newEntity->ID = 0;
    newEntity->next = NULL;
    newEntity->pos = _pos;
    newEntity->exPos = _pos;
    newEntity->entityTypeInfo = NULL;
    pushFrontValue(&firstEntity, newEntity);
    return newEntity;
}

void entity_updates()
{
}

void drawOneEntity(sfRenderWindow* _window, Entity* _entity) 
{
    sfRectangleShape_setPosition(rectangle, _entity->pos);

    sfRenderWindow_drawRectangleShape(_window, rectangle, NULL);
}

void entity_draw(sfRenderWindow* _window)
{
    forAll(&firstEntity, drawOneEntity, _window);
}

void entity_destroy(Entity* _entityToDestroy)
{
    printf("destruction de l'entity %d en x : %.3f, y : %.3f\n", _entityToDestroy->ID, _entityToDestroy->pos.x, _entityToDestroy->pos.y);
}

void entity_destroyAll()
{
    delAllWith(&firstEntity, entity_destroy);
}
