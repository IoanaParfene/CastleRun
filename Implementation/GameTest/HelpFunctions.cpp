#pragma once
//------------------------------------------------------------------------
// HelperFunctions.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <iostream>
//------------------------------------------------------------------------
#include "HelpFunctions.h"
//------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------

float HelpFunctions::randomizeFloatInterval(float start, float end)
{
	// Randomize a float between start and end
	return start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (end - start)));
}

bool HelpFunctions::checkCollision(collisionData collision_parameters)
{
	// Square collision implementation
	if (collision_parameters.hero_x < collision_parameters.entity_x + collision_parameters.entity_width &&
		collision_parameters.hero_x + collision_parameters.hero_weapon_x + collision_parameters.hero_width > collision_parameters.entity_x &&
		collision_parameters.hero_y < collision_parameters.entity_y + collision_parameters.entity_height &&
		collision_parameters.hero_y + collision_parameters.hero_height > collision_parameters.entity_y)
	{
		return true;
	}
	return false;
}