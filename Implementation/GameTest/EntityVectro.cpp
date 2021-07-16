#pragma once
//------------------------------------------------------------------------
// EntityVectors.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "EntityVectro.h"
#include "HelpFunctions.h"
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// CGraphicsEntityVector Methods
//------------------------------------------------------------------------
template<class T>
CGraphicsEntityVector<T>::CGraphicsEntityVector(SSpriteInfo spriteInfo)
{
	// Store the default spriteInfo 
	m_spriteInfoModel = spriteInfo;
}

template<class T>
void CGraphicsEntityVector<T>::CreateSpriteInfo(SSpriteInfo* spriteInfo)
{
	// Use the cosntructor parameter spriteInfo instead of randomizing a new one
	*spriteInfo = m_spriteInfoModel;
}

template<class T>
void CGraphicsEntityVector<T>::GetLastEntityData(SSpriteInfo* spriteInfo)
{
	// Get the position of the last entity and update the spriteInfoModel for the new one

	float lastPieceX, lastPieceY, lastPieceWidth, lastPieceHeight;

	T lastPiece = m_entityVector[m_entityVector.size() - 1];
	lastPiece.GetSprite()->GetPosition(lastPieceX, lastPieceY);
	lastPieceWidth = lastPiece.GetSprite()->GetWidth();
	lastPieceHeight = lastPiece.GetSprite()->GetHeight();

	spriteInfo->x += lastPieceX + lastPieceWidth;
}

template<class T>
void CGraphicsEntityVector<T>::DeleteEntity()
{
	// The position of the deleted entity
	int erasePosition = -1;
	float x, y;

	for (int i = 0; i < m_entityVector.size(); ++i)
	{
		m_entityVector[i].GetSprite()->GetPosition(x, y);

		// If the entity is outside the screen, delete it
		if (x < m_minEntityX)
		{
			erasePosition = i;
		}
		if (erasePosition > -1)
		{
			m_entityVector.erase(m_entityVector.begin() + erasePosition);
			break;
		}
	}
}

template<class T>
bool CGraphicsEntityVector<T>::CheckAddCondition()
{
	// Chech if there are less entities in the vector than the threshold
	if (m_entityVector.size() < m_minEntityVectorSize)
	{
		return true;
	}
	return false;
}

template<class T>
void CGraphicsEntityVector<T>::UpdateEntities(float deltaTime, float current_speed)
{
	// If addinf a new entity is possible
	if (CheckAddCondition()==true)
	{
		SSpriteInfo newSpriteInfo;
		CreateSpriteInfo(&newSpriteInfo);
		AddEntity(newSpriteInfo);
	}
	// Update entity position
	for (auto i = 0; i != m_entityVector.size(); i++)
	{
		m_entityVector[i].Update(deltaTime, current_speed);
	}
	// Delete the first entity outside the screen that passes the minimum postion
	DeleteEntity();
}

template<class T>
void CGraphicsEntityVector<T>::RenderEntities()
{
	for (auto i = 0; i != m_entityVector.size(); i++)
	{
		m_entityVector[i].Render();
	}
}


//------------------------------------------------------------------------
// CStaticEntityVector Methods
//------------------------------------------------------------------------
template<class T>
CStaticEntityVector<T>::CStaticEntityVector(SSpriteInfo spriteInfo) : CGraphicsEntityVector(spriteInfo)
{
	// Create a new entity and add it to the vector
	AddEntity(spriteInfo);
}

template<class T>
void CStaticEntityVector<T>::AddEntity(SSpriteInfo spriteInfo)
{
	T* newPiece = new T(spriteInfo);
	m_entityVector.push_back(*newPiece);
}

template<class T>
void CStaticEntityVector<T>::ReplaceEntity(int position, SSpriteInfo spriteInfo)
{
	// Replace the entity at a specifici vector position
	T* newPiece = new T(spriteInfo);
	m_entityVector[position] = *newPiece;
}


//------------------------------------------------------------------------
// CBackgroundVector Methods
//------------------------------------------------------------------------
template<class T>
CBackgroundVector<T>::CBackgroundVector(std::vector<SSpriteInfo> spriteInfoVector, SSpriteInfo spriteInfo) : CGraphicsEntityVector(spriteInfo)
{
	// Add the first element in the vector
	T* newPiece = new T(spriteInfo);
	m_entityVector.push_back(*newPiece);

	// Add the entity sprite options for the background
	m_entitySpriteInfoVector = spriteInfoVector;
}

template<class T>
CBackgroundVector<T>::CBackgroundVector(std::vector<SSpriteInfo> spriteInfoVector, SSpriteInfo spriteInfo1, SSpriteInfo spriteInfo2) : CGraphicsEntityVector(spriteInfo1)
{
	// Add the first 2 elements in the vector
	T* newPiece1 = new T(spriteInfo1);
	T* newPiece2 = new T(spriteInfo2);
	m_entityVector.push_back(*newPiece1);
	m_entityVector.push_back(*newPiece2);

	// Add the entity sprite options for the background
	m_entitySpriteInfoVector = spriteInfoVector;
}

template<class T>
void CBackgroundVector<T>::RandomizeSpriteInfo(SSpriteInfo* spriteInfo)
{
	// Randomize a new sprite from the vector
	int code = int(HelpFunctions::randomizeFloatInterval(0, m_entitySpriteInfoVector.size()));
	*spriteInfo = m_entitySpriteInfoVector[code];
}

template<class T>
void CBackgroundVector<T>::AddEntity(SSpriteInfo spriteInfo)
{
	// Add one entity at the end of the last backgorund piece
	GetLastEntityData(&spriteInfo);
	T* newPiece = new T(spriteInfo);
	m_entityVector.push_back(*newPiece);
}

template<class T>
void CBackgroundVector<T>::CreateSpriteInfo(SSpriteInfo* spriteInfo)
{
	// Change the default sprite model
	RandomizeSpriteInfo(spriteInfo);
}


//------------------------------------------------------------------------
// CCollisionVector Methods
//------------------------------------------------------------------------
template<class T>
CCollisionVector<T>::CCollisionVector(SSpriteInfo spriteInfo, SCollisionInfo collisionInfo, SCollisionEntityVectorData collisionVectorInfo, unsigned int collisionEntityType) : CGraphicsEntityVector(spriteInfo)
{
	// Initialize the collision entity parameters
	m_collisionInfoModel = collisionInfo;
	m_collisionVectorInfo = collisionVectorInfo;
	m_secondsUntilNextEntity = std::chrono::duration<double>(m_collisionVectorInfo.secondsUntilFirstEntity);
	m_collisionEntityType = collisionEntityType;
}


template<class T>
void CCollisionVector<T>::AddEntity(SSpriteInfo spriteInfo) 
{
	// Get the position of the last entity if it exists
	if (m_entityVector.size() > 0)
	{
		GetLastEntityData(&spriteInfo);
	}
	// Randomize The speed
	m_collisionInfoModel.speed = HelpFunctions::randomizeFloatInterval(m_collisionVectorInfo.minSpeed, m_collisionVectorInfo.maxSpeed);

	// Create the new Entity
	T* newPiece = new T(spriteInfo, m_collisionInfoModel);
	// Add the collision information
	newPiece->SetCollisionEntityType(m_collisionEntityType);
	m_entityVector.push_back(*newPiece);

	// Recalculate the time until the next entity
	m_lastEntityCreationTime = std::chrono::system_clock::now();
	m_secondsUntilNextEntity = std::chrono::duration<double>(HelpFunctions::randomizeFloatInterval(m_collisionVectorInfo.minSecondsUntilNextEntity * m_entitySpawnTimeReduction, m_collisionVectorInfo.maxSecondsUntilNextEntity* m_entitySpawnTimeReduction));

}

template<class T>
bool CCollisionVector<T>::CheckAddCondition()
{
	// If the second until a new entity have passed, create a new one
	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - m_lastEntityCreationTime;
	if (m_secondsUntilNextEntity < elapsed_seconds)
	{
		return true;
	}
	return false;
}

template<class T>
void CCollisionVector<T>::UpdateEntities(float deltaTime, float currentSpeed)
{
	CGraphicsEntityVector<T>::UpdateEntities(deltaTime, currentSpeed);

	// Speed up the min/max time between entity creation, as the game naturally speeds up as time passes
	m_entitySpawnTimeReduction = 1.0f / currentSpeed;
}



//------------------------------------------------------------------------
// CEnemyVector Methods
//------------------------------------------------------------------------
template<class T>
CEnemyVector<T>::CEnemyVector(SSpriteInfo spriteInfo, SCollisionInfo collisionInfoModel, SCollisionEntityVectorData collisionVectorInfo, unsigned int collisionEntityType, float scorePoints, float heroDamagePoints) : CCollisionVector(spriteInfo, collisionInfoModel, collisionVectorInfo, collisionEntityType)
{
	// Add the score and damage model points for enemy creation
	m_scorePoints = scorePoints;
	m_heroDamagePoints = heroDamagePoints;
}

template<class T>
void CEnemyVector<T>::AddEntity(SSpriteInfo spriteInfo)
{
	CCollisionVector<T>::AddEntity(spriteInfo);
	// Set the score and damage points received in the constructor
	m_entityVector[m_entityVector.size() - 1].SetScorePoints(m_scorePoints);
	m_entityVector[m_entityVector.size() - 1].SetHeroDamagePoints(m_heroDamagePoints);
}


//------------------------------------------------------------------------
// CollectibleVector Methods
//------------------------------------------------------------------------
template<class T>
CCollectibleVector<T>::CCollectibleVector(SSpriteInfo spriteInfo, SCollisionInfo collisionInfoModel, SCollisionEntityVectorData collisionVectorInfo, unsigned int collisionEntityType, unsigned int collectibleType, std::vector<SCollectibleData> collectibleOptions) : CCollisionVector(spriteInfo, collisionInfoModel, collisionVectorInfo, collisionEntityType)
{
	// Set the collectible type and its parameters
	m_collectibleOptions = collectibleOptions;
	m_collectibleType = collectibleType;
}

template<class T>
void CCollectibleVector<T>::AddEntity(SSpriteInfo spriteInfo)
{
	SSpriteInfo* collectibleSpriteInfo;
	unsigned int collectibleType;

	// Randomize new entity collision and sprite data from the vector
	int code = int(HelpFunctions::randomizeFloatInterval(0, m_collectibleOptions.size()));
	m_spriteInfoModel = m_collectibleOptions[code].collectibleSprite;
	m_collectibleType = m_collectibleOptions[code].collectibleType;
	
	CCollisionVector<T>::AddEntity(m_spriteInfoModel);
	m_entityVector[m_entityVector.size()-1].SetCollectibleType(m_collectibleType);

}