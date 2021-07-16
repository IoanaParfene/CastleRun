#pragma once
//------------------------------------------------------------------------
// EntitySprites.h
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
//------------------------------------------------------------------------
#include "app\app.h"
#include "Settings.h"
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// SPRITE STRUCTS and DECLARATIONS
//------------------------------------------------------------------------

// Basic Sprite Animation Information struct
struct SSpriteAnimationInfo
{
	unsigned int id;
	float animationSpeed;
	std::vector<int> frames;
};

// Basic Sprite Information struct
struct SSpriteInfo
{
	const char* fileName;
	float x;
	float y;
	unsigned int nColumns;
	unsigned int nRows;
	float scale;
	std::vector<SSpriteAnimationInfo> animations;
};

// Ghouls Sprite Info
static SSpriteAnimationInfo GHOUL_ANIM_FORWARDS = { ANIM_FORWARDS, (1.0f / 15.0f), {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 12, 14, 15} };
static SSpriteInfo GHOUL_SPRITE = { ".\\TestData\\ghoul.bmp", 2000.0f, 190.0f, 16, 1, 8.0f, {GHOUL_ANIM_FORWARDS} };

// Ghost Horse Sprite Info
static SSpriteAnimationInfo GHOST_HORSE_ANIM_FORWARDS = { ANIM_FORWARDS, (1.0f / 10.0f), {0, 1, 2, 3} };
static SSpriteInfo GHOST_HORSE_SPRITE = { ".\\TestData\\ghost_horse.bmp", 2000.0f, 180.0f, 4, 1, 4.0f, {GHOST_HORSE_ANIM_FORWARDS} };

// Skull Sprite Info
static SSpriteAnimationInfo SKULL_ANIM_FORWARDS = { ANIM_FORWARDS, (1.0f / 15.0f), {0, 1, 2, 3, 4, 5, 6, 7} };
static SSpriteInfo SKULL_SPRITE = { ".\\TestData\\skull.bmp", 2000.0f, 500.0f, 8, 1, 2.0f, {SKULL_ANIM_FORWARDS} };

// Ghost Sprite Info
static SSpriteAnimationInfo GHOST_ANIM_FORWARDS = { ANIM_FORWARDS, (1.0f / 15.0f), {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10} };
static SSpriteInfo GHOST_SPRITE = { ".\\TestData\\ghost.bmp", 2000.0f, 500.0f, 9, 2, 3.0f, {GHOST_ANIM_FORWARDS} };

// Background Sprite Info
static SSpriteInfo ENTRANCE_SPRITE = { ".\\TestData\\entrance.bmp", 320.0f, 365.0f, 1, 1, 9.4f, {} };
static SSpriteInfo FIRST_ANGEL_SPRITE = { ".\\TestData\\angel.bmp", 860.0f, 365.0f, 1, 1, 9.5f, {} };
static SSpriteInfo ANGEL_SPRITE = { ".\\TestData\\angel.bmp", 295.0f, 365.0f, 1, 1, 9.5f, {} };
static SSpriteInfo CANDLES_SPRITE = { ".\\TestData\\candles.bmp", 295.0f, 365.0f, 1, 1, 9.4f, {} };
static SSpriteInfo WINDOW_SPRITE = { ".\\TestData\\window.bmp", 295.0f, 365.0f, 1, 1, 9.4f, {} };
static SSpriteInfo FIRST_TILE_SPRITE = { ".\\TestData\\big-tile.bmp", 14.0f, 30.0f, 1, 1, 6.0f, {} };
static SSpriteInfo BIG_TILE_SPRITE = { ".\\TestData\\big-tile.bmp", 64.0f, 30.0f, 1, 1, 6.0f, {} };

// Sprite Information Vectors for Background Pieces
static std::vector<SSpriteInfo> WALLPAPER_VECTOR{ ANGEL_SPRITE, CANDLES_SPRITE, WINDOW_SPRITE };
static std::vector<SSpriteInfo> FLOOR_VECTOR{ BIG_TILE_SPRITE };


// COLLECTIBLE Sprite Info for collision
static SSpriteInfo BOOK_SPRITE = { ".\\TestData\\book.bmp", 2000.0f, 300.0f, 1, 1, 0.7f, {} };
static SSpriteInfo SHIELD_SPRITE = { ".\\TestData\\shield.bmp", 2000.0f, 300.0f, 1, 1, 0.7f, {} };
static SSpriteInfo RING_SPRITE = { ".\\TestData\\ring.bmp", 2000.0f, 300.0f, 1, 1, 0.7f, {} };
static SSpriteInfo MASK_SPRITE = { ".\\TestData\\mask.bmp", 2000.0f, 300.0f, 1, 1, 0.7f, {} };
static SSpriteInfo COINS_SPRITE = { ".\\TestData\\coins.bmp", 2000.0f, 300.0f, 1, 1, 0.7f, {} };
static SSpriteInfo DIAMOND_SPRITE = { ".\\TestData\\diamond.bmp", 2000.0f, 300.0f, 1, 1, 0.7f, {} };

// COLLECTIBLE Sprite Info for display on screen as found/not found
static SSpriteInfo EXISTING_BOOK_SPRITE = { ".\\TestData\\book.bmp", 630.0f, 630.0f, 1, 1, 0.6f, {} };
static SSpriteInfo EXISTING_SHIELD_SPRITE = { ".\\TestData\\shield.bmp", 710.0f, 630.0f, 1, 1, 0.6f, {} };
static SSpriteInfo EXISTING_RING_SPRITE = { ".\\TestData\\ring.bmp", 790.0f, 630.0f, 1, 1, 0.7f, {} };
static SSpriteInfo EXISTING_MASK_SPRITE = { ".\\TestData\\mask.bmp", 870.0f, 630.0f, 1, 1, 0.6f, {} };
static SSpriteInfo EXISTING_DIAMOND_SPRITE = { ".\\TestData\\diamond.bmp", 950.0f, 630.0f, 1, 1, 0.7f, {} };
static SSpriteInfo EXISTING_COINS_SPRITE = { ".\\TestData\\coins.bmp", 1030.0f, 630.0f, 1, 1, 0.6f, {} };

static SSpriteInfo INVISIBLE_BOOK_SPRITE = { ".\\TestData\\no_book.bmp", 630.0f, 630.0f, 1, 1, 0.6f, {} };
static SSpriteInfo INVISIBLE_SHIELD_SPRITE = { ".\\TestData\\no_shield.bmp", 710.0f, 630.0f, 1, 1, 0.6f, {} };
static SSpriteInfo INVISIBLE_RING_SPRITE = { ".\\TestData\\no_ring.bmp", 790.0f, 630.0f, 1, 1, 0.7f, {} };
static SSpriteInfo INVISIBLE_MASK_SPRITE = { ".\\TestData\\no_mask.bmp", 870.0f, 630.0f, 1, 1, 0.6f, {} };
static SSpriteInfo INVISIBLE_DIAMOND_SPRITE = { ".\\TestData\\no_diamond.bmp", 950.0f, 630.0f, 1, 1, 0.7f, {} };
static SSpriteInfo INVISIBLE_COINS_SPRITE = { ".\\TestData\\no_coins.bmp", 1030.0f, 630.0f, 1, 1, 0.6f, {} };

// COLLECTIBLE Sprite Info vectors display on screen as found/not found
static std::vector<SSpriteInfo> EXISTING_COLLECTIBLES_SPRITES{ EXISTING_BOOK_SPRITE, EXISTING_SHIELD_SPRITE, EXISTING_RING_SPRITE, EXISTING_MASK_SPRITE, EXISTING_COINS_SPRITE, EXISTING_DIAMOND_SPRITE };
static std::vector<SSpriteInfo> MISSING_COLLECTIBLES_SPRITES{ INVISIBLE_BOOK_SPRITE, INVISIBLE_SHIELD_SPRITE, INVISIBLE_RING_SPRITE, INVISIBLE_MASK_SPRITE, INVISIBLE_COINS_SPRITE, INVISIBLE_DIAMOND_SPRITE };


// POWERUP Sprite Info for collision
static SSpriteInfo IMMUNITY_SPRITE = { ".\\TestData\\immunity.bmp", 2000.0f, 300.0f, 1, 1, 0.7f, {} };
static SSpriteInfo SUPER_ATTACK_SPRITE = { ".\\TestData\\super_attack.bmp", 2000.0f, 300.0f, 1, 1, 0.7f, {} };

// POWERUP Sprite Info for display on screen as active/not active
static SSpriteInfo EXISTING_IMMUNITY_POWERUP_SPRITE = { ".\\TestData\\immunity.bmp", 450.0f, 640.0f, 1, 1, 0.6f, {} };
static SSpriteInfo EXISTING_SUPER_ATTACK_POWERUP_SPRITE = { ".\\TestData\\super_attack.bmp", 520.0f, 640.0f, 1, 1, 0.6f, {} };

static SSpriteInfo MISSING_IMMUNITY_POWERUP_SPRITE = { ".\\TestData\\immunity.bmp", 2000.0f, 640.0f, 1, 1, 0.6f, {} };
static SSpriteInfo MISSING_SUPER_ATTACK_POWERUP_SPRITE = { ".\\TestData\\super_attack.bmp", 2000.0f, 640.0f, 1, 1, 0.6f, {} };

// POWERUP Sprite Info vectors display on screen as active/not active
static std::vector<SSpriteInfo> EXISTING_POWERUP_SPRITES{ EXISTING_IMMUNITY_POWERUP_SPRITE, EXISTING_SUPER_ATTACK_POWERUP_SPRITE };
static std::vector<SSpriteInfo> MISSING_POWERUP_SPRITES{ MISSING_IMMUNITY_POWERUP_SPRITE };// , MISSING_SUPER_ATTACK_POWERUP_SPRITE };


// Collision Information for an entity
struct SCollisionInfo
{
	float speed;
	float minVariationY;
	float maxVariationY;
	bool disappearWhenHit;
};

// ENEMY Collision Info
static SCollisionInfo GHOUL_COLLISION = { 7.0f, 0.0f, 0.0f, true};
static SCollisionInfo GHOST_HORSE_COLLISION = { 7.0f, 0.0f, 0.0f, false};
static SCollisionInfo SKULL_COLLISION = { 7.0f, 100.0f, 250.0f, true};
static SCollisionInfo GHOST_COLLISION = { 7.0f, 100.0f, 250.0f, false};
static SCollisionInfo COLLECTIBLE_COLLISION = { 7.0f, 30.0f, 40.0f, true };


// Collision Creation Data for collision entity vector management class objects
struct SCollisionEntityVectorData
{
	float minSpeed;
	float maxSpeed;
	float minSecondsUntilNextEntity;
	float maxSecondsUntilNextEntity;
	float secondsUntilFirstEntity;
};

// ENEMY Collision Info for the vector management class
static SCollisionEntityVectorData GHOUL_VECTOR = { 8.0f, 11.0f, 2.0f, 3.0f, 0.0f };
static SCollisionEntityVectorData GHOST_HORSE_VECTOR = { 8.0f, 10.0f, 20.0f, 5.0f, 10.0f };
static SCollisionEntityVectorData SKULL_VECTOR = { 8.0f, 11.0f, 3.0f, 5.0f, 3.0f };
static SCollisionEntityVectorData GHOST_VECTOR = { 7.0f, 8.5f, 20.0f, 30.0f, 20.0f };
static SCollisionEntityVectorData COLLECTIBLE_VECTOR = { 7.0f, 7.0f, 20.0f, 30.0f, 20.0f };
static SCollisionEntityVectorData POWERUPS_VECTOR = { 7.0f, 7.0f, 20.0f, 30.0f, 1.0f };

// ENEMY hit points
static const float GHOUL_HIT_SCORE = 10.0f;
static const float GHOST_HIT_SCORE = 0.0f;
static const float GHOST_HORSE_HIT_SCORE = 0.0f;
static const float SKULL_HIT_SCORE = 15.0f;

// ENEMY life points
static const float GHOUL_HERO_DAMAGE = 0.2f;
static const float GHOST_HERO_DAMAGE = -0.01f;
static const float GHOST_HORSE_HERO_DAMAGE = 0.01f;
static const float SKULL_HERO_DAMAGE = 0.2f;


// Struct with collectible sprites and collision type options
struct SCollectibleData
{
	SSpriteInfo collectibleSprite;
	unsigned int collectibleType;
};

// Sprite and option ids for COLLECTIBLES
static SCollectibleData BOOK_DATA = { BOOK_SPRITE, BOOK };
static SCollectibleData SHIELD_DATA = { SHIELD_SPRITE, SHIELD };
static SCollectibleData RING_DATA = { RING_SPRITE, RING };
static SCollectibleData MASK_DATA = { MASK_SPRITE, MASK };
static SCollectibleData COINS_DATA = { COINS_SPRITE, COINS };
static SCollectibleData DIAMOND_DATA = { DIAMOND_SPRITE, DIAMOND };

// Vector of sprites and options ids for COLLECTIBLES
static std::vector<SCollectibleData> COLLECTIBLES{ BOOK_DATA, SHIELD_DATA, RING_DATA, MASK_DATA, COINS_DATA, DIAMOND_DATA };

// Sprite and option ids for POWERUPS
static SCollectibleData IMMUNITY_DATA = { IMMUNITY_SPRITE, IMMUNITY };
static SCollectibleData SUPER_ATTACK_DATA = { SUPER_ATTACK_SPRITE, SUPER_ATTACK };

// Vector of sprites and options ids for POWERUPS
static std::vector<SCollectibleData> POWERUPS{ IMMUNITY_DATA };//, SUPER_ATTACK_DATA};