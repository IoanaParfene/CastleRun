#pragma once
//------------------------------------------------------------------------
// EntityVectors.h
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <vector>
#include <chrono>
//------------------------------------------------------------------------
#include "Entity.h"
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// CGraphicsEntityVector
//------------------------------------------------------------------------
// Base class for all entity vector management objects
//------------------------------------------------------------------------
template<class T>
class CGraphicsEntityVector
{
public:
	// Constructor 
	CGraphicsEntityVector(SSpriteInfo spriteInfo);

	// Randomize or get a specific spriteInfo struct
	virtual void CreateSpriteInfo(SSpriteInfo* spriteInfo);

	// Check if new entity addition is possible
	virtual bool CheckAddCondition();

	// Manipulate entity vector
	virtual void AddEntity(SSpriteInfo spriteInfo) = 0;
	void DeleteEntity();
	// Get the position of the las entity
	void GetLastEntityData(SSpriteInfo* spriteInfo);
	
	// Update sprites, speed of entities
	virtual void UpdateEntities(float deltaTime, float currentSpeed);

	// Draw entity sprites
	void RenderEntities();

	// Get and Set the entity vector
	std::vector<T> GetEntityVector() { return m_entityVector; };
	void SetEntityVector(std::vector<T> entityVector) { m_entityVector = entityVector; };

protected:

	std::vector<T> m_entityVector;
	std::vector<SSpriteInfo> m_entitySpriteInfoVector;

	// The sprite info struct used to model new entities
	SSpriteInfo m_spriteInfoModel;

	// Add more entities if below 
	int m_minEntityVectorSize = MIN_ENTITY_VECTOR_SIZE;

	// X Position at at which the entities shoul be deletes(otside of screen)
	float m_minEntityX = MIN_ENTITY_X;

};


//------------------------------------------------------------------------
// CStaticEntityVector
//------------------------------------------------------------------------
// Used for static entities(instructions, buttons, score panels)
//------------------------------------------------------------------------
template<class T>
class CStaticEntityVector : public CGraphicsEntityVector<T>
{
public:
	// Constructor 
	CStaticEntityVector(SSpriteInfo spriteInfo);

	void AddEntity(SSpriteInfo spriteInfo);
	// Replace entity data outside of spritesheet, used for existing/missing collectibles
	void ReplaceEntity(int vectorPosition, SSpriteInfo spriteInfo);
};


//------------------------------------------------------------------------
// CBackgroundVector
//------------------------------------------------------------------------
// Used for wall and floor tiles
//------------------------------------------------------------------------
template<class T>
class CBackgroundVector : public CGraphicsEntityVector<T>
{
public:
	// Constructors for wall and floor tiles
	CBackgroundVector(std::vector<SSpriteInfo> spriteInfoVector, SSpriteInfo spriteInfo1, SSpriteInfo spriteInfo2);
	CBackgroundVector(std::vector<SSpriteInfo> spriteInfoVector, SSpriteInfo spriteInfo);

	virtual void AddEntity(SSpriteInfo spriteInfo);
	// Randomize type of background tiles
	void RandomizeSpriteInfo(SSpriteInfo* spriteInfo);
	void CreateSpriteInfo(SSpriteInfo* spriteInfo);

};

//------------------------------------------------------------------------
// CCollisionVector
//------------------------------------------------------------------------
// Used as a base for entities that collide with the player
//------------------------------------------------------------------------
template<class T>
class CCollisionVector : public CGraphicsEntityVector<T>
{
public:
	CCollisionVector(SSpriteInfo spriteInfo, SCollisionInfo collisionInfoModel, SCollisionEntityVectorData collisionVectorInfo, unsigned int collisionEntityType);
	virtual void AddEntity(SSpriteInfo spriteInfo);
	bool CheckAddCondition();
	void UpdateEntities(float deltaTime, float currentSpeed);

	unsigned int GetCollisionEntityType() { return m_collisionEntityType; }
	void SetCollisionEntityType(unsigned int collisionEntityType) { m_collisionEntityType = collisionEntityType; };


private:
	// Used to speed up the min/max time between entity creation, as the game naturally speeds up as time passes
	float m_entitySpawnTimeReduction = 0.0f;

	// Collision entity type(ENEMY, COLLECTIBLE, POWERUP)
	unsigned int m_collisionEntityType = 0;

	// Collision specific data used by the vector class to randomize new entities
	SCollisionInfo m_collisionInfoModel;

	// The collision defaut model used to create new entities
	SCollisionEntityVectorData m_collisionVectorInfo;

	std::chrono::time_point<std::chrono::system_clock> m_lastEntityCreationTime = std::chrono::system_clock::now();
	std::chrono::duration<double> m_secondsUntilNextEntity = std::chrono::duration<double>(0.0f);
};


//------------------------------------------------------------------------
// CEnemyVector
//------------------------------------------------------------------------
// Used as for skulls, ghosts, etc
//------------------------------------------------------------------------
template<class T>
class CEnemyVector : public CCollisionVector<T>
{
public:
	CEnemyVector(SSpriteInfo spriteInfo, SCollisionInfo collisionInfoModel, SCollisionEntityVectorData collisionVectorInfo, unsigned int collisionEntityType, float scorePoints, float heroDamagePoints);
	void AddEntity(SSpriteInfo spriteInfo);

private:
	// The things that will change upon collision
	float m_scorePoints = 0.0f;
	float m_heroDamagePoints = 0.0f;
};

//------------------------------------------------------------------------
// CCollectibleVector
//------------------------------------------------------------------------
// Used as for simple COLLECTIBLES and for POWERUPS
//------------------------------------------------------------------------
template<class T>
class CCollectibleVector: public CCollisionVector<T>
{
public:
	CCollectibleVector(SSpriteInfo spriteInfo, SCollisionInfo collisionInfoModel, SCollisionEntityVectorData collisionVectorInfo, unsigned int collisionEntityType, unsigned int collectibleType, std::vector<SCollectibleData> collectibleOptions);
	
	void AddEntity(SSpriteInfo spriteInfo);

	void SetCollectibleType(unsigned int collectibleType) { m_collectibleType = collectibleType; }
	unsigned int GetCollectibleType() { return m_collectibleType; }

private:
	// Options for a specific collectible entity(book, mask, etc for COLLECTIBLE; invincibility, super attack for POWERUP)
	unsigned int m_collectibleType = 0;
	// The option vector for that specific collectible
	std::vector<SCollectibleData> m_collectibleOptions;
};
