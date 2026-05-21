#pragma once

float deltaTime;
float trueDeltaTime;

void clock_create();
void clock_update();
void clock_setTicksSecond(float _newTickSecond);
void clock_setTimeSpeed(float _newTimeSpeed);
void clock_destroy();
