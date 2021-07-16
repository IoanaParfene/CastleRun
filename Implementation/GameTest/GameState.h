#pragma once
//------------------------------------------------------------------------
// GameState.h
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "Hero.h"
#include "EntityVectro.h"
#include "EntityVectro.cpp"
//------------------------------------------------------------------------


// GameState 
class GameState
{

public:
	// Constructor
	GameState();

	// Data Initialization for each New Game/Replay
	void InitializeNewGameData();


	// Detect the collision between the hero and a collision entity, return if the hero and entity were hit
	void DetectCollision(collisionData collisionParameters, bool &entityHit, bool &heroHit);
	
	// Resolve Collisions for a specific Entity class Vector
	template<class T>
	void ResolveCollisions(std::vector<T> &entityVector);

	// Resolve Collisions for a specific Entity Class Vector Manager
	template<class U>
	void ResolveVectorCollisions(U manager);

	// Resolve Collisions for all the Entity Class Vector Managers
	void ResolveVectorsCollisions();


	// Game Over Condition
	bool GameIsOver();

	// Initialize display GraphicEntities
	void InitializeDisplayCollectibles();
	void InitializeDisplayPowerups();

	// Gets for the various attributes of the Character class
	Hero* GetHero() { return m_hero; }
	bool GetGameOver() { return m_gameOver; }
	int GetCurrentScreen() { return m_currentScreen; }
	bool GetGameOverScreenOn() { return m_gameOverScreenOn; }


	// Update Methods for each Screens
	void UpdateGameScreen(float deltaTime);
	void UpdateGameOverScreen(float deltaTime);
	void UpdateMainMenuScreen(float deltaTime);
	void UpdatePauseScreen();

	void UpdatePowerups();

	// Render Methods for each Screens
	void RenderGameScreen();
	void RenderPauseScreen();
	void RenderGameOverScreen();
	void RenderMainMenuScreen();

	void DrawLifeBar();
	void DrawInstructions();


private:

	// Sprite Containing Game Entity Vector Managers
	Hero* m_hero;
	CEnemyVector<CEnemyEntity>* m_skullVectorManager;
	CEnemyVector<CEnemyEntity>* m_ghoulVectorManager;
	CEnemyVector<CEnemyEntity>* m_ghostVectorManager;
	CEnemyVector<CEnemyEntity>* m_ghostHorseVectorManager;
	CBackgroundVector<CBackgroundPiece>* m_backgrounWallpaperVectorManager;
	CBackgroundVector<CBackgroundPiece>* m_backgroundFloorVectorManager;
	CCollectibleVector<CCollectibleEntity>* m_collectibleVectorManager;
	CCollectibleVector<CCollectibleEntity>* m_powerupVectorManager;
	// Screen display foun/not found collectibles and powerups
	CStaticEntityVector<CStaticEntity>* m_displayCollectiblesManager;
	CStaticEntityVector<CStaticEntity>* m_displayPowerupsManager;
	
	// Power up management vectors, positions based on 'Setting.h' enum
	// True if the powerup at that position is active at the moment
	std::vector<bool> m_activePowerups;
	// Time a powerup of type found at vector location was created
	std::vector<std::chrono::time_point<std::chrono::system_clock>> m_lastPowerupCreationTimes;

	// Screen Changing Data
	bool m_gameOver = GAME_OVER;
	bool m_gameOverScreenOn = GAME_OVER_SCREEN;
	int m_currentScreen = MENU;
	float m_score = 0.0f;

	// Used for leaderboard
	std::vector<int> m_bestScores{ 0,0,0 };
	
	// Used to track gameplay time between screens
	std::chrono::duration<double> gameTime;
	std::chrono::time_point<std::chrono::system_clock> startGameTime;

	// Static UI entities 
	CSimpleSprite* m_healthBar;
	CSimpleSprite* m_scoreBackground;
	CSimpleSprite* m_background;
	CSimpleSprite* m_instructionIcon;
	CSimpleSprite* m_instructions;
};