#pragma once
//------------------------------------------------------------------------
// Entity.h
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "EntitySettings.h"
//------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Entity
//------------------------------------------------------------------------
// Base class for all the graphic entities that use aprites
//------------------------------------------------------------------------
class CEntity
{
public:
	// Constructor that saves the sprite creation data
	CEntity(SSpriteInfo spriteInfo);

	// Initialize the sprite with the spriteInfo data
	void InitSprite(SSpriteInfo spriteInfo);

	// Update the sprite, position, etc of the entity
	virtual void Update(float deltaTime, float currentSpeed) = 0;

	// Draw the sprites
	void Render();

	// Get for the sprite
	CSimpleSprite* GetSprite() { return m_sprite; }

protected:
	CSimpleSprite* m_sprite;
	float m_positionX = 0.0f;
	float m_positionY = 0.0f;
	float m_speed = DEFAULT_SPEED;
};


//------------------------------------------------------------------------
// CBackgroundPiece
//------------------------------------------------------------------------
// Wall or Floor Piece Entities
//------------------------------------------------------------------------
class CBackgroundPiece : public CEntity
{
public:
	CBackgroundPiece(SSpriteInfo spriteInfo);

	// Move using the player's speed
	void Update(float deltaTime, float current_speed);
};


//------------------------------------------------------------------------
// CStaticEntity
//------------------------------------------------------------------------
// Entities that do not move on the screen(buttons, score decorations, etc)
//------------------------------------------------------------------------
class CStaticEntity : public CEntity
{
public:
	CStaticEntity(SSpriteInfo spriteInfo);

	// Update the sprite each frame
	void Update(float deltaTime, float currentSpeed);
};


//------------------------------------------------------------------------
// CCollisionEntity
//------------------------------------------------------------------------
// Base class for entites that can collide with the player
//------------------------------------------------------------------------
class CCollisionEntity : public CEntity
{
public:
	CCollisionEntity(SSpriteInfo spriteInfo, SCollisionInfo collisionInfo);

	virtual void Update(float deltaTime, float currentSpeed);

	// Resolve Collision for ENEMY or COLLECTIBLE/POWERUP entities
	virtual void ResolveCollision(float& scoreAddition, float& lifeAddition) = 0;
	virtual void ResolveCollision(float& scoreAddition, unsigned int& collectibleType) = 0;

	// Return if the entity disappears during collision or not
	bool GetDisappearWhenHit() { return m_disappearWhenHit; }

	// Get the collision entity type(ENEMY, COLLECTIBLE, POWERUP)
	unsigned int GetCollisionEntityType() { return m_collisionEntityType; }
	void SetCollisionEntityType(unsigned int collisionEntityType) { m_collisionEntityType = collisionEntityType; };

protected:
	// How much flying entities can move up at min/max
	float m_minVariationY = 100.0f;
	float m_maxVariationY = 100.0f;

	// Used to change the direction up/down
	float m_direction = 1.0f;

	// How many frames will spend the entity in a new direction
	float m_upDownFrames = 0.0f;

	bool m_disappearWhenHit = false;

	// ENEMY, COLLECTIBLE, POWERUP
	unsigned int m_collisionEntityType = 0;
};

//------------------------------------------------------------------------
// CEnemyEntity
//------------------------------------------------------------------------
// Enemy entity(skul, ghost, etc)
//------------------------------------------------------------------------
class CEnemyEntity : public CCollisionEntity
{
public:
	CEnemyEntity(SSpriteInfo spriteInfo, SCollisionInfo collisionInfo);

	// Resolve type specific collision
	void ResolveCollision(float& scoreAddition, float& lifeAddition);
	void ResolveCollision(float& scoreAddition, unsigned int& collectibleType) {};

	// Get/Set for the score points given after being destroyed by the player
	float GetScorePoints() { return m_scorePoints; }
	void SetScorePoints(float scorePoints) { m_scorePoints = scorePoints; }

	// Get/Set for the damage points to the hero given after collision
	float GetHeroDamagePoints() { return m_heroDamagePoints; }
	void SetHeroDamagePoints(float heroDamagePoints) { m_heroDamagePoints = heroDamagePoints; }

private:
	float m_scorePoints = 0.0f;
	float m_heroDamagePoints = 0.0f;
};

//------------------------------------------------------------------------
// CCollectibleEntity
//------------------------------------------------------------------------
// COLLECTIBLE/POWERUP
//------------------------------------------------------------------------
class CCollectibleEntity : public CCollisionEntity
{
public:
	CCollectibleEntity(SSpriteInfo spriteInfo, SCollisionInfo collisionInfo);

	// Resolve type specific collision
	void ResolveCollision(float& scoreAddition, float& lifeAddition) {};
	void ResolveCollision(float& scoreAddition, unsigned int& collectibleType);

	// Options for a specific collectible entity(book, mask, etc for COLLECTIBLE; invincibility, super attack for POWERUP)
	void SetCollectibleType(unsigned int collectibleType) { m_collectibleType = collectibleType; }
	unsigned int GetCollectibleType() { return m_collectibleType; }

	// Get the score points given when being collected by the player
	float GetScorePoints() { return m_scorePoints; }

private:
	float m_scorePoints = COLLECTIBLE_SCORE_POINTS;
	unsigned int m_collectibleType = 0;
};