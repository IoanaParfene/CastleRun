#pragma once
//------------------------------------------------------------------------
// GameState.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <algorithm>
//------------------------------------------------------------------------
#include "GameState.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------
GameState::GameState()
{
	// Initialize data for a New Game/Replay
	InitializeNewGameData();

	// Application Starting Screen
	m_currentScreen = MENU;

	// Initialize the static Sprite Entities at fixed Positions
	m_background = App::CreateSprite(".\\TestData\\background_menu.bmp", 1, 1);
	m_background->SetPosition(650.0f, 340.0f);
	m_background->SetScale(1.8f);

	m_healthBar = App::CreateSprite(".\\TestData\\health_bar.bmp", 1, 1);
	m_healthBar->SetPosition(230.0f, 630.0f);
	m_healthBar->SetScale(1.0f);

	m_scoreBackground = App::CreateSprite(".\\TestData\\score_background.bmp", 1, 1);
	m_scoreBackground->SetPosition(1230.0f, 630.0f);
	m_scoreBackground->SetScale(1.0f);

	m_instructionIcon = App::CreateSprite(".\\TestData\\info.bmp", 1, 1);
	m_instructionIcon->SetPosition(1230.0f, 40.0f);
	m_instructionIcon->SetScale(0.2f);

	m_instructions = App::CreateSprite(".\\TestData\\instructions.bmp", 1, 1);
	m_instructions->SetPosition(640.0f, 360.0f);
	m_instructions->SetScale(2.0f);

	CSimpleSprite* m_instructions;
}

//------------------------------------------------------------------------
// // Initialize data for a New Game/Replay
//------------------------------------------------------------------------
void GameState::InitializeNewGameData()
{
	startGameTime = std::chrono::system_clock::now();

	// Sprite Containing Entities
	m_hero = new Hero();
	m_score = 0.0f;

	m_backgrounWallpaperVectorManager = new CBackgroundVector<CBackgroundPiece>(WALLPAPER_VECTOR, ENTRANCE_SPRITE, FIRST_ANGEL_SPRITE);
	m_backgroundFloorVectorManager = new CBackgroundVector<CBackgroundPiece>(FLOOR_VECTOR, FIRST_TILE_SPRITE);

	m_ghostHorseVectorManager = new CEnemyVector<CEnemyEntity>(GHOST_HORSE_SPRITE, GHOST_HORSE_COLLISION, GHOST_HORSE_VECTOR, ENEMY, GHOST_HORSE_HIT_SCORE, GHOST_HORSE_HERO_DAMAGE);
	m_ghoulVectorManager = new CEnemyVector<CEnemyEntity>(GHOST_SPRITE, GHOST_COLLISION, GHOST_VECTOR, ENEMY, GHOST_HIT_SCORE, GHOST_HERO_DAMAGE);
	m_ghostVectorManager = new CEnemyVector<CEnemyEntity>(GHOUL_SPRITE, GHOUL_COLLISION, GHOUL_VECTOR, ENEMY, GHOUL_HIT_SCORE, GHOUL_HERO_DAMAGE);
	m_skullVectorManager = new CEnemyVector<CEnemyEntity>(SKULL_SPRITE, SKULL_COLLISION, SKULL_VECTOR, ENEMY, SKULL_HIT_SCORE, SKULL_HERO_DAMAGE);

	m_collectibleVectorManager = new CCollectibleVector<CCollectibleEntity>(BOOK_SPRITE, COLLECTIBLE_COLLISION, COLLECTIBLE_VECTOR, COLLECTIBLE, BOOK, COLLECTIBLES);
	m_powerupVectorManager = new CCollectibleVector<CCollectibleEntity>(IMMUNITY_SPRITE, COLLECTIBLE_COLLISION, POWERUPS_VECTOR, POWERUP, IMMUNITY, POWERUPS);

	InitializeDisplayCollectibles();
	InitializeDisplayPowerups();
}

void GameState::InitializeDisplayCollectibles()
{
	// Add the first COLLECTIBLE type based on 'Settings.h' enum
	m_displayCollectiblesManager = new CStaticEntityVector<CStaticEntity>(INVISIBLE_BOOK_SPRITE);
	for (int i = 1; i < MISSING_COLLECTIBLES_SPRITES.size(); i++)
	{
		m_displayCollectiblesManager->AddEntity(MISSING_COLLECTIBLES_SPRITES[i]);
	}
}

void GameState::InitializeDisplayPowerups()
{
	// Initialize the powerup management creation times
	m_lastPowerupCreationTimes.push_back(std::chrono::system_clock::now());

	// Add the first POWERUP type based on 'Settings.h' enum
	m_activePowerups.push_back(false);
	m_displayPowerupsManager = new CStaticEntityVector<CStaticEntity>(MISSING_IMMUNITY_POWERUP_SPRITE);
	for (int i = 1; i < MISSING_POWERUP_SPRITES.size(); i++)
	{
		SSpriteInfo powerup = MISSING_POWERUP_SPRITES[i];
		m_displayCollectiblesManager->AddEntity(powerup);
		m_lastPowerupCreationTimes.push_back(std::chrono::system_clock::now());

		// Make POWERUPS inactive at initialization
		m_activePowerups.push_back(false);

	}
}


//------------------------------------------------------------------------
// Game Over Condition
//------------------------------------------------------------------------
bool GameState::GameIsOver()
{
	if (m_hero->GetLifeValue() <= 0.0f)
	{
		return true;
	}
	return false;
}


void GameState::DetectCollision(collisionData collision_parameters, bool& entity_hit, bool& hero_hit)
{
	// Resolve collisions between the hero and one entity
	if (m_hero->GetInputActionCode() == ANIM_START_JUMP_ATTACK)
	{

		collision_parameters.hero_weapon_x -= HERO_JUMP_ATTACK_WEAPON_REACH;
		if (HelpFunctions::checkCollision(collision_parameters) == true)
		{
			hero_hit = true;
		}
		if (m_activePowerups[SUPER_ATTACK] == true)
		{
			collision_parameters.hero_x = 0.0f;
			collision_parameters.hero_y = 0.0f;
			collision_parameters.hero_width = APP_VIRTUAL_WIDTH;
			collision_parameters.hero_height = APP_VIRTUAL_HEIGHT;
		}
		else
		{
			collision_parameters.hero_weapon_x += 2 * HERO_JUMP_ATTACK_WEAPON_REACH;
		}
		if (HelpFunctions::checkCollision(collision_parameters) == true)
		{
			entity_hit = true;
		}
	}
	else if (m_hero->GetInputActionCode() == ANIM_ATTACK)
	{
		collision_parameters.hero_weapon_x -= HERO_JUMP_ATTACK_WEAPON_REACH;
		if (HelpFunctions::checkCollision(collision_parameters) == true)
		{
			hero_hit = true;
		}
		if (m_activePowerups[SUPER_ATTACK] == true)
		{
			collision_parameters.hero_x = 0.0f;
			collision_parameters.hero_y = 0.0f;
			collision_parameters.hero_width = APP_VIRTUAL_WIDTH;
			collision_parameters.hero_height = APP_VIRTUAL_HEIGHT;
		}
		else
		{
			collision_parameters.hero_weapon_x = HERO_ATTACK_WEAPON_REACH;
		}
		if (HelpFunctions::checkCollision(collision_parameters) == true)
		{
			entity_hit = true;
		}
	}
	else
	{
		if (HelpFunctions::checkCollision(collision_parameters) == true)
		{
			hero_hit = true;
		}
	}
}

template<class T>
void GameState::ResolveCollisions(std::vector<T>& entityVector)
{
	// Resolve collisions of a vector
	for (int i = 0; i < entityVector.size(); i++)
	{
		// If the enitty was hit with a sword
		bool entity_hit = false;
		// If the hero touched an entity
		bool hero_hit = false;

		// Create the collision parameters for passing to a Square Collision detection function
		float entity_x, entity_y, hero_x, hero_y;
		float hero_width, hero_height, entity_width, entity_height;

		entityVector[i].GetSprite()->GetPosition(entity_x, entity_y);
		m_hero->GetSprite()->GetPosition(hero_x, hero_y);

		entity_width = entityVector[i].GetSprite()->GetWidth();
		entity_height = entityVector[i].GetSprite()->GetHeight();
		hero_width = m_hero->GetSprite()->GetWidth();
		hero_height = m_hero->GetSprite()->GetWidth();

		collisionData collision_parameters = { hero_x, hero_y, entity_x, entity_y, hero_height, hero_width, entity_width, entity_height, 0.0f };


		// Check if the enemy was hit and if the hero touched an entity
		DetectCollision(collision_parameters, entity_hit, hero_hit);


		// SOLVE COLLISION

		// Entity Collision parameters 
		float lifeAddition = 0.0f, scoreAddition = 0.0f;
		// Collision Entity Type(ENEMY, COLLECTIBLE, POWERUP)
		unsigned int collectibleType = 0;

		// Resolve Collisions based on Active powerups, collision results and entity type
		if (entityVector[i].GetCollisionEntityType() == ENEMY && m_activePowerups[IMMUNITY] == false)
		{
			entityVector[i].ResolveCollision(scoreAddition, lifeAddition);
			if (hero_hit == true)
			{
				m_hero->SetLifeValue(min((float)((double)m_hero->GetLifeValue() - lifeAddition), HERO_LIFE_VALUE));
			}
			if (entity_hit == true)
			{

				m_score += scoreAddition;
			}
		}
		if (entityVector[i].GetCollisionEntityType() == COLLECTIBLE || entityVector[i].GetCollisionEntityType() == POWERUP)
		{
			entityVector[i].ResolveCollision(scoreAddition, collectibleType);
			if (hero_hit == true)
			{
				PlaySound(TEXT(COLLECT_SOUND), NULL, SND_ASYNC | SND_FILENAME);
				m_score += scoreAddition;
			}
		}
		if (entityVector[i].GetCollisionEntityType() == COLLECTIBLE)
		{
			if (hero_hit == true || entity_hit)
			{
				m_displayCollectiblesManager->ReplaceEntity(collectibleType, EXISTING_COLLECTIBLES_SPRITES[collectibleType]);
			}
		}
		if (entityVector[i].GetCollisionEntityType() == POWERUP)
		{
			if (hero_hit == true || entity_hit)
			{
				m_activePowerups[collectibleType] = true;
				m_displayPowerupsManager->ReplaceEntity(collectibleType, EXISTING_POWERUP_SPRITES[collectibleType]);
				m_lastPowerupCreationTimes[collectibleType] = std::chrono::system_clock::now();
			}
		}
		if (hero_hit == true || entity_hit == true)
		{
			if (entityVector[i].GetDisappearWhenHit() == true)
			{
				entityVector.erase(entityVector.begin() + i);
				break;
			}
		}
	}
}

template <class U>
void GameState::ResolveVectorCollisions(U manager)
{
	// Resolve collisions of a manager's vector
	auto entityVector = manager->GetEntityVector();
	ResolveCollisions(entityVector);
	manager->SetEntityVector(entityVector);
}


void GameState::ResolveVectorsCollisions()
{
	// Resolve collision by Manager
	ResolveVectorCollisions(m_ghostHorseVectorManager);
	ResolveVectorCollisions(m_ghostVectorManager);
	ResolveVectorCollisions(m_skullVectorManager);
	ResolveVectorCollisions(m_ghoulVectorManager);
	ResolveVectorCollisions(m_collectibleVectorManager);
	ResolveVectorCollisions(m_powerupVectorManager);
}


//------------------------------------------------------------------------
// Update Methods 
//------------------------------------------------------------------------

void GameState::UpdatePowerups()
{
	// Check if the time allocated to the power up is over
	for (int i = 0; i < m_activePowerups.size(); i++)
	{
		if (std::chrono::duration<double>POWERUP_TIME < (std::chrono::system_clock::now() - m_lastPowerupCreationTimes[i]))
		{
			// Make powerup inactive
			if (m_activePowerups[i] == true)
			{
				m_displayPowerupsManager->ReplaceEntity(i, MISSING_POWERUP_SPRITES[i]);
				m_activePowerups[i] = false;
			}
		}
	}
}


void GameState::UpdateGameScreen(float deltaTime)
{
	// Update gaemplay
	gameTime = std::chrono::system_clock::now() - startGameTime;

	// Pause Game if 'P' is pressed
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		m_background = App::CreateSprite(".\\TestData\\background_paused.bmp", 1, 1);
		m_background->SetPosition(650.0f, 340.0f);
		m_background->SetScale(1.8f);
		m_currentScreen = PAUSE;
	}

	// Update the hero
	m_hero->Update(deltaTime);

	// Add distance from last frame to current frame to the score(as an alternative to just time passed based score)
	m_score += m_hero->GetCurrentSpeed() / 1000.0f;

	// Update the background entities based on the player
	m_backgrounWallpaperVectorManager->UpdateEntities(deltaTime, m_hero->GetCurrentSpeed());
	m_backgroundFloorVectorManager->UpdateEntities(deltaTime, m_hero->GetCurrentSpeed());

	// Resolve Collisions with the entities
	ResolveVectorsCollisions();
	m_skullVectorManager->UpdateEntities(deltaTime, m_hero->GetCurrentSpeed());
	m_ghoulVectorManager->UpdateEntities(deltaTime, m_hero->GetCurrentSpeed());
	m_ghostHorseVectorManager->UpdateEntities(deltaTime, m_hero->GetCurrentSpeed());
	m_ghostVectorManager->UpdateEntities(deltaTime, m_hero->GetCurrentSpeed());

	m_collectibleVectorManager->UpdateEntities(deltaTime, m_hero->GetCurrentSpeed());
	m_powerupVectorManager->UpdateEntities(deltaTime, m_hero->GetCurrentSpeed());

	UpdatePowerups();

	// Go to Game Over Screen 
	if (GameIsOver() == true)
	{
		m_background = App::CreateSprite(".\\TestData\\background_lost.bmp", 1, 1);
		m_background->SetPosition(650.0f, 340.0f);
		m_background->SetScale(1.8f);
		m_bestScores.push_back(m_score);
		m_currentScreen = OVER;
	}
}

void GameState::UpdateGameOverScreen(float deltaTime)
{
	// Go to Main Menu from Game Over Screen pressing SPACE
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		m_background = App::CreateSprite(".\\TestData\\background_menu.bmp", 1, 1);
		m_background->SetPosition(650.0f, 340.0f);
		m_background->SetScale(1.8f);
		m_currentScreen = MENU;
	}
}

void GameState::UpdateMainMenuScreen(float deltaTime)
{
	// Start Game if press SPACE
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		InitializeNewGameData();
		m_currentScreen = GAME;
	}
}

void GameState::UpdatePauseScreen()
{
	// Resume Game if press P
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		m_currentScreen = GAME;
	}
}


//------------------------------------------------------------------------
// Render Methods 
//------------------------------------------------------------------------

void GameState::DrawLifeBar()
{
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float current_hero_life_points = m_hero->GetLifeValue();
	float life_line_x = 149.0f + (current_hero_life_points * 233.0f) / 5.0f;
	App::DrawLine(149.0f, 627.0f, life_line_x, 627.0f, 0.6f, 0.1f, 0.1f, 17.0f);
}

void GameState::RenderGameScreen()
{
	// Render Game Background
	m_backgrounWallpaperVectorManager->RenderEntities();
	m_backgroundFloorVectorManager->RenderEntities();

	// Render Hero
	m_hero->GetSprite()->Draw();

	// Render Enemies
	m_skullVectorManager->RenderEntities();
	m_ghoulVectorManager->RenderEntities();
	m_ghostHorseVectorManager->RenderEntities();
	m_ghostVectorManager->RenderEntities();

	// Render Collectibles as Collision and Found/Not Found Screen Display
	m_collectibleVectorManager->RenderEntities();
	m_displayCollectiblesManager->RenderEntities();

	// Render POWERUPS as Collision and Found/Not Found Screen Display
	m_powerupVectorManager->RenderEntities();
	m_displayPowerupsManager->RenderEntities();

	// Render Static Sprite entities
	m_healthBar->Draw();
	m_scoreBackground->Draw();

	// Draw moving part of the life bar 
	DrawLifeBar();

	// Draw the score
	char scoreBuffer[100];
	sprintf(scoreBuffer, "%i", int(m_score));
	App::Print(1205, 624, scoreBuffer, 0.9f, 0.7f, 0.3f, GLUT_BITMAP_TIMES_ROMAN_24);

	// Draw the time
	char timeBuffer[100];
	sprintf(timeBuffer, "%i:%i", (int)gameTime.count() / 60, (int)gameTime.count() % 60);
	App::Print(1110, 624, timeBuffer, 0.9f, 0.7f, 0.3f, GLUT_BITMAP_TIMES_ROMAN_24);


	// Player screen management message
	App::Print(1100, 20, "Press 'P' to Pause", 0.5f, 0.4f, 0.1f, GLUT_BITMAP_TIMES_ROMAN_24);

}

void GameState::RenderGameOverScreen()
{
	m_background->Draw();
	// Player screen management message
	App::Print(450, 20, "Press 'SPACE' to return to the Main Menu", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24);

	// Display the player score on the game over screen
	char scoreBuffer[100];
	sprintf(scoreBuffer, "%i", int(m_score));
	App::Print(450, 315, scoreBuffer, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24);

	// Sort the best scores for the leaderboard
	std::sort(m_bestScores.begin(), m_bestScores.begin() + m_bestScores.size(), greater<int>());
	// Display the first 3 best scores

	int firstScoreY = 250;
	for (int i = 0; i < 3; i++)
	{
		firstScoreY -= 25;
		char leaderboardBuffer[100];
		sprintf(leaderboardBuffer, "%i", int(m_bestScores[i]));
		App::Print(600, firstScoreY, leaderboardBuffer, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void GameState::RenderPauseScreen()
{
	m_background->Draw();
	// Player screen management message
	App::Print(450, 20, "Press 'P' to return to the Game", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24);

	// Draw instructions
	DrawInstructions();
}

void GameState::RenderMainMenuScreen()
{
	m_background->Draw();
	// Player screen management message
	App::Print(450, 20, "Press 'SPACE' to Start", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24);

	// Draw instructions
	DrawInstructions();

}

void GameState::DrawInstructions()
{
	m_instructionIcon->Draw();

	float x, y;
	App::GetMousePos(x, y);
	if (x > 1200.0f && x < 1250.0f && y>10.0f && y < 50.0f)
	{
		m_instructions->Draw();
	}
}