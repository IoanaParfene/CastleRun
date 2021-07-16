#pragma once
//------------------------------------------------------------------------
// HelperFunctions.h
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <cstdlib>
#include <stdbool.h>
//------------------------------------------------------------------------
#include "Settings.h"
//------------------------------------------------------------------------

namespace HelpFunctions
{
	float randomizeFloatInterval(float start, float end);

	bool checkCollision(collisionData collision_parameters);
}
