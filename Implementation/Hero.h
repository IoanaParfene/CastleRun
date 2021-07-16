#pragma once
//------------------------------------------------------------------------
// Hero.h
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "app\app.h"
#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "Components.h"
//------------------------------------------------------------------------


class KeyboardInputComponent;
class GraphicsComponent;
class PhysicsComponent;


class Hero
{
public:
	// Constructor for the animation speed, position coordinates, dimension and jump height
	Hero();

	// Method for position related actions
	void Update(float deltaTime);

	// Sets and Gets for the various attributes of the Character class
	CSimpleSprite* GetSprite() { return sprite; }
	CSimpleSprite* GetRunSprite() { return run_sprite; }
	CSimpleSprite* GetAttackSprite() { return attack_sprite; }
	CSimpleSprite* GetJumpSprite() { return jump_sprite; }
	CSimpleSprite* GetJumpAttackSprite() { return jump_attack_sprite; }
	CSimpleSprite* GetCrouchSprite() { return crouch_sprite; }

	float GetCurrentSpeed() { return current_speed; }
	float GetSpeedIncrease() { return speed_increase; }
	float GetLifeValue() { return life_value; }
	float GetPositionX() { return position_x; }
	float GetPositionY() { return position_y; }
	float GetScale() { return scale; }
	float GetJumpHeight() { return jump_height; }
	int GetRemainingJumpFrames() { return remaining_jump_frames; }
	int GetRemainingAttackFrames() { return remaining_attack_frames; }
	int GetRemainingJumpAttackFrames() { return remaining_jump_attack_frames; }
	bool GetJumping() { return jumping; }
	bool GetAttacking() { return attacking; }
	bool GetJumpAttacking() { return jump_attacking; }
	int GetInputActionCode() { return input_action_code; }
	int GetInputSpeedCode() { return input_speed_code; }
	int GetCurrentSpriteType() { return current_sprite_type; }


	void SetSprite(CSimpleSprite* new_sprite) { sprite = new_sprite; }
	void SetLifeValue(float new_life_value) { life_value = new_life_value; }
	void SetCurrentSpeed(float new_speed) { current_speed = new_speed; }
	void SetJumping(bool new_jumping) { jumping = new_jumping; }
	void SetAttacking(bool new_attacking) { attacking = new_attacking; }
	void SetJumpAttacking(bool new_jump_attacking) { jump_attacking = new_jump_attacking; }
	void SetRemainingJumpFrames(int new_remaining_jump_frames) { remaining_jump_frames = new_remaining_jump_frames; }
	void SetRemainingAttackFrames(int new_remaining_attack_frames) { remaining_attack_frames = new_remaining_attack_frames; }
	void SetRemainingJumpAttackFrames(int new_remaining_jump_attack_frames) { remaining_jump_attack_frames = new_remaining_jump_attack_frames; }
	void SetInputActionCode(int new_input_action_code) { input_action_code = new_input_action_code; }
	void SetInputSpeedCode(int new_input_speed_code) { input_speed_code = new_input_speed_code; }
	void SetJumpHeight(float new_jump_height) { jump_height = new_jump_height; }
	void SetPositionX(float new_position_x) { position_x = new_position_x; }
	void SetPositionY(float new_position_y) { position_y = new_position_y; }
	void SetCurrentSpriteType(int new_sprite_type) { current_sprite_type = new_sprite_type; }
	void SetSpeedIncrease(float new_speed_increase) { speed_increase = new_speed_increase; }



private:
	// The hero sprite
	CSimpleSprite* sprite;
	CSimpleSprite* crouch_sprite;
	CSimpleSprite* jump_sprite;
	CSimpleSprite* run_sprite;
	CSimpleSprite* jump_attack_sprite;
	CSimpleSprite* attack_sprite;

	// True if the hero is currently jumping
	bool jumping = HERO_IS_JUMPING;
	// True if the hero is currently jumping
	bool attacking = HERO_IS_ATTACKING;
	bool jump_attacking = HERO_IS_JUMP_ATTACKING;
	// The number of frames that the jump will last
	int remaining_jump_frames = HERO_ALL_JUMP_FRAMES;
	// The number of frames that the jump will last
	int remaining_attack_frames = HERO_ALL_ATTACK_FRAMES;
	int remaining_jump_attack_frames = HERO_ALL_JUMP_ATTACK_FRAMES;
	// The change is speed based on backwards/foorwards keys
	float current_speed = NORMAL_SPEED;
	// The height of the ascending/descending jump animation of a frame
	float jump_height = JUMP_HEIGHT;
	// Remaining hearts, death on 0
	float life_value = HERO_LIFE_VALUE;
	// Scale of hero sprites
	float scale = HERO_SPRITE_SCALE;
	// Coordinates of the character
	float position_x = HERO_POSITION_X;
	float position_y = HERO_POSITION_Y;
	// Coordinates of the character
	float animation_speed = HERO_ANIMATION_SPEED;

	int current_sprite_type = CURRENT_SPRITE_TYPE;

	KeyboardInputComponent* input_component;
	int input_action_code = INPUT_ACTION_CODE;
	int input_speed_code = INPUT_SPEED_CODE;

	GraphicsComponent* graphics_component;
	PhysicsComponent* physics_component;

	float speed_increase = 0.0f;

};

#endif
