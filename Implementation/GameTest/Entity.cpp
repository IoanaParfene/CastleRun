#pragma once
//------------------------------------------------------------------------
// Entity.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "Entity.h"
#include "HelpFunctions.h"
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// CEntity Methods
//------------------------------------------------------------------------
CEntity::CEntity(SSpriteInfo spriteInfo)
{
	// Set the entity position and create the sprite
	m_positionX = spriteInfo.x;
	m_positionY = spriteInfo.y;
	InitSprite(spriteInfo);
}

void CEntity::InitSprite(SSpriteInfo spriteInfo)
{
	// Initialize the Sprite
	m_sprite = App::CreateSprite(spriteInfo.fileName, spriteInfo.nColumns, spriteInfo.nRows);
	m_sprite->SetPosition(spriteInfo.x, spriteInfo.y);
	m_sprite->SetScale(spriteInfo.scale);
	// Add Animations
	for (auto i = 0; i != spriteInfo.animations.size(); i++)
	{
		m_sprite->CreateAnimation(spriteInfo.animations[i].id, spriteInfo.animations[i].animationSpeed, spriteInfo.animations[i].frames);
		m_sprite->SetAnimation(0);
	}
}

void CEntity::Render()
{
	m_sprite->Draw();
}


//------------------------------------------------------------------------
// CBackgroundPiece Methods
//------------------------------------------------------------------------
CBackgroundPiece::CBackgroundPiece(SSpriteInfo spriteInfo) : CEntity(spriteInfo)
{
}

void CBackgroundPiece::Update(float deltaTime, float currentSpeed)
{
	m_sprite->Update(deltaTime);

	float x, y;
	m_sprite->GetPosition(x, y);

	// Move based on the player's speed
	x -= m_speed * currentSpeed;
	m_sprite->SetPosition(x, y);
}


//------------------------------------------------------------------------
// CStaticEntity Methods
//------------------------------------------------------------------------
CStaticEntity::CStaticEntity(SSpriteInfo spriteInfo) : CEntity(spriteInfo)
{
}

void CStaticEntity::Update(float deltaTime, float current_speed)
{
	m_sprite->Update(deltaTime);
}

CCollisionEntity::CCollisionEntity(SSpriteInfo spriteInfo, SCollisionInfo collisionInfo) : CEntity(spriteInfo)
{
	// Store the collision data
	m_minVariationY = collisionInfo.minVariationY;
	m_maxVariationY = collisionInfo.maxVariationY;
	m_disappearWhenHit = collisionInfo.disappearWhenHit;
	m_speed = collisionInfo.speed;
}

void CCollisionEntity::Update(float deltaTime, float current_speed)
{
	m_sprite->Update(deltaTime);

	float x, y;
	m_sprite->GetPosition(x, y);

	// If there are frames left towards a direction
	float y_change;
	if (m_upDownFrames > 0)
	{
		// Change y to move in that direction
		y_change = m_direction * ENTITY_Y_SPEED;
		m_upDownFrames -= 1;

		// If the screen limits were passed change direction anyway
		if ((y + y_change) < MIN_ENTITY_Y || (y + y_change) > MAX_ENTITY_Y)
		{
			y_change = 0;
			m_upDownFrames = int(HelpFunctions::randomizeFloatInterval(m_minVariationY, m_maxVariationY));
			m_direction *= -1;
		}
	}
	else // Change direction and recalculate frames spent there 
	{
		y_change = 0;
		m_upDownFrames = int(HelpFunctions::randomizeFloatInterval(m_minVariationY, m_maxVariationY));
		m_direction *= -1;
	}
	// Update a frame of movement if the player is a flying type
	m_upDownFrames--;
	x -= m_speed * current_speed;
	y += y_change;
	m_sprite->SetPosition(x, y);

}
//------------------------------------------------------------------------
// CEnemyEntity Methods
//------------------------------------------------------------------------
CEnemyEntity::CEnemyEntity(SSpriteInfo spriteInfo, SCollisionInfo collisionInfo) : CCollisionEntity(spriteInfo, collisionInfo)
{
}

void CEnemyEntity::ResolveCollision(float &scoreAddition, float& lifeAddition)
{
	// Give the game_state the collision parameters to resolve collision
	scoreAddition = m_scorePoints;
	lifeAddition = m_heroDamagePoints;
}


//------------------------------------------------------------------------
// CCollectibleEntity Methods
//------------------------------------------------------------------------
CCollectibleEntity::CCollectibleEntity(SSpriteInfo spriteInfo, SCollisionInfo collisionInfo) : CCollisionEntity(spriteInfo, collisionInfo)
{
}

void CCollectibleEntity::ResolveCollision(float& scoreAddition, unsigned int& collectibleType)
{
	// Give the game_state the collision parameters to resolve collision
	scoreAddition = m_scorePoints;
	collectibleType = m_collectibleType;
}