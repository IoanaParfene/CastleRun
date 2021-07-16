#pragma once
#include "stdafx.h"
#include "Settings.h"
#ifndef HERO_H
#define HERO_H
#include "Hero.h"
#include <chrono>
class Hero;


class KeyboardInputComponent
{
public:
	void Update(Hero& hero);
};

class PhysicsComponent
{
public:
	void Update(Hero& hero);
};

class GraphicsComponent
{
public:
	void Update(Hero& hero);
};

#endif