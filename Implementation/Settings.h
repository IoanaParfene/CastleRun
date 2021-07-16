#pragma once
//------------------------------------------------------------------------
// Settings.h
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// GameState Constant Data
//------------------------------------------------------------------------
#define GAME_OVER				true
#define GAME_OVER_SCREEN		false
#define CURRENT_SCREEN			MENU

// Possible Game Speeds
#define NORMAL_SPEED			(1.0f)
#define FAST_SPEED				(1.2f)
#define SLOW_SPEED				(0.8f)
#define SPEED_INCREASE_VALUE	(0.00003f)

// Sounds
#define SWORD_SOUND
#define COLLECT_SOUND			".\\TestData\\collect.wav"
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Hero Constant Data
//------------------------------------------------------------------------

// Sprite Arguments
#define HERO_ANIMATION_SPEED			(1.0f / 15.0f)  
#define HERO_POSITION_X					(160.0f)
#define HERO_POSITION_Y					(160.0f)
#define HERO_SPRITE_SCALE				(8.5f)

// Speed and Action State Codes
#define CURRENT_SPRITE_TYPE				RUN_SPRITE
#define INPUT_ACTION_CODE				ANIM_FORWARDS
#define INPUT_SPEED_CODE				ANIM_FORWARDS

// Life Points
#define HERO_LIFE_VALUE					(5.0f)

// Action Data
#define HERO_IS_JUMPING					false
#define HERO_IS_ATTACKING				false
#define HERO_IS_JUMP_ATTACKING			false
// Jumping
#define JUMP_HEIGHT						(30.0f)
#define HERO_ALL_JUMP_FRAMES			(40)
#define HERO_START_JUMP_MINIMUM_FRAME	(30)
#define HERO_MID_JUMP_MINIMUM_FRAME		(8)
// Attacking
#define HERO_ALL_ATTACK_FRAMES			(10)


// Jump Attacking 
#define HERO_ALL_JUMP_ATTACK_FRAMES				(40)
#define HERO_START_JUMP_ATTACK_MINIMUM_FRAME	(30)
#define HERO_MID_JUMP_ATTACK_MINIMUM_FRAME		(15)
#define HERO_JUMP_ATTACK_FRAME					(8)
#define HERO_ATTACK_WEAPON_REACH				(50.0f)
#define HERO_JUMP_ATTACK_WEAPON_REACH			(60.0f)
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Entity Constant Data
#define ENTITY_SPEED				(12.0f)
#define MIN_ENTITY_VECTOR_SIZE		(30)
#define MIN_ENTITY_Y				(100.0f)
#define MAX_ENTITY_Y				(600.0f)
#define ENTITY_Y_SPEED				(4.0f)
#define MIN_ENTITY_X				(-1000.0f)
#define POWERUP_TIME				(8.0f)
#define COLLECTIBLE_SCORE_POINTS	(50.0f)
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Background Constant Data
//------------------------------------------------------------------------
#define BACKGROUND_SPEED				(7.0f)
#define DEFAULT_SPEED					(7.0f)
#define MIN_WALLPAPER_VECTOR_SIZE		(12)
#define MIN_FLOOR_VECTOR_SIZE			(20)
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Enums
//------------------------------------------------------------------------

//  The Game Screens
enum
{	
	MENU,
	GAME,
	PAUSE,
	OVER
};

// Hero Sprites
enum
{
	RUN_SPRITE,
	CROUCH_SPRITE,
	JUMP_SPRITE,
	ATTACK_SPRITE,
	JUMP_ATTACK_SPRITE
};

// Hero Animations
enum
{	
	// RUN_SPRITE Animations
	ANIM_FORWARDS,
	ANIM_FAST,
	ANIM_SLOW,

	// ATTACK_SPRITE Animation
	ANIM_ATTACK,
	ANIM_START_JUMP_ATTACK,
	ANIM_MID_JUMP_ATTACK,
	ANIM_JUMP_ATTACK,
	ANIM_END_JUMP_ATTACK,

	// JUMP_SPRITE and JUMP_ATTACK_SPRITE Animation
	ANIM_START_JUMP,
	ANIM_END_JUMP,
	ANIM_MID_JUMP,

	// SLIDE_SPRITE Animation
	ANIM_SLIDE
};

// Collision Entity Types
enum
{
	COLLECTIBLE, 
	ENEMY,
	POWERUP
};

// COLLECTIBLE OPTIONS
enum
{
	BOOK,
	SHIELD,
	RING,
	MASK,
	COINS,
	DIAMOND
};

// POWERUP OPTIONS
enum
{
	IMMUNITY,
	SUPER_ATTACK
};


// Struct for passing to the box collision calculating function
struct collisionData
{
	float hero_x;
	float hero_y;
	float entity_x;
	float entity_y;
	float hero_height;
	float hero_width;
	float entity_width;
	float entity_height;
	float hero_weapon_x;
};
typedef struct collisionData CollisionData;