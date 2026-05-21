#pragma once

#include "SFML/Graphics.h"

typedef struct Entity Entity;
struct Entity {
	Entity* next;
	unsigned int ID;
	sfVector2f pos;
	sfVector2f exPos;
	void* entityTypeInfo;
};

void entity_init();

Entity* entity_create(sfVector2f _pos);

void entity_updates();

void drawOneEntity(sfRenderWindow* _window, Entity* _entity);
void entity_draw(sfRenderWindow* _window);

void entity_destroy(Entity* _entityToDestroy);
void entity_destroyAll();
