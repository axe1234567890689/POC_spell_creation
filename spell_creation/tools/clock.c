#include <SFML/Graphics.h>
#include "header/clock.h"

sfClock* clock = NULL;
float ticksSecond = 60.;
float timeSpeed = 1.;

void clock_create()
{
	clock = sfClock_create();
	trueDeltaTime = 1. / ticksSecond;
	deltaTime = trueDeltaTime * timeSpeed;
}

void clock_update()
{
	if (!clock) return;
	trueDeltaTime = sfTime_asSeconds(sfClock_restart(clock));
	deltaTime = trueDeltaTime * timeSpeed;
}

void clock_setTicksSecond(float _newTickSecond)
{
	if (!clock) return;
	ticksSecond = _newTickSecond;
}

void clock_setTimeSpeed(float _newTimeSpeed)
{
	if (!clock) return;
	timeSpeed = _newTimeSpeed;
}

void clock_destroy()
{
	if (!clock) return;
	sfClock_destroy(clock);
}
