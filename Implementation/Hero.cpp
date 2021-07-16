#pragma once
//------------------------------------------------------------------------
// Hero.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "Hero.h"
//------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------------
Hero::Hero()
{
	
	run_sprite = App::CreateSprite(".\\TestData\\hero-run.bmp", 12, 1);
	run_sprite->SetPosition(position_x, position_y);
	// Running at normal speed
	run_sprite->CreateAnimation(ANIM_FORWARDS, animation_speed, { 0,1,2,3,4,5,6,7,8,9,10,11 });
	// Running at a slower speed
	run_sprite->CreateAnimation(ANIM_SLOW, animation_speed * FAST_SPEED, { 0,1,2,3,4,5,6,7,8,9,10,11 });
	// Running at a faster speed
	run_sprite->CreateAnimation(ANIM_FAST, animation_speed * SLOW_SPEED, { 0,1,2,3,4,5,6,7,8,9,10,11 });
	run_sprite->SetScale(scale);

	
	jump_sprite  = App::CreateSprite(".\\TestData\\hero-jump.bmp", 5, 1);
	jump_sprite->SetPosition(position_x, position_y);
	jump_sprite->CreateAnimation(ANIM_START_JUMP, animation_speed, { 2 });
	// Mid-air part of the jump animation
	jump_sprite->CreateAnimation(ANIM_MID_JUMP, animation_speed, { 3 });
	// Descending part of the jump animation
	jump_sprite->CreateAnimation(ANIM_END_JUMP, animation_speed, { 4 });
	jump_sprite->SetScale(scale);

	
	jump_attack_sprite = App::CreateSprite(".\\TestData\\hero-jump-attack.bmp", 6, 1);
	jump_attack_sprite->SetPosition(position_x, position_y);
	jump_attack_sprite->CreateAnimation(ANIM_START_JUMP_ATTACK, animation_speed, { 4 });
	// Mid-air part of the jump animation
	jump_attack_sprite->CreateAnimation(ANIM_MID_JUMP_ATTACK, animation_speed, { 2 });
	// Sliding animation
	jump_attack_sprite->CreateAnimation(ANIM_JUMP_ATTACK, animation_speed, { 2 });
	// Descending part of the jump animation
	jump_attack_sprite->CreateAnimation(ANIM_END_JUMP_ATTACK, animation_speed, { 5 });
	jump_attack_sprite->SetScale(scale);

	
	attack_sprite = App::CreateSprite(".\\TestData\\hero-attack.bmp", 6, 1);
	attack_sprite->SetPosition(position_x, position_y);
	attack_sprite->CreateAnimation(ANIM_ATTACK, animation_speed, { 2,3,4 });
	attack_sprite->SetScale(scale);

	
	crouch_sprite = App::CreateSprite(".\\TestData\\hero-crouch.bmp", 3, 1);
	crouch_sprite->SetPosition(position_x, position_y);
	crouch_sprite->CreateAnimation(ANIM_SLIDE, animation_speed, { 2 });
	crouch_sprite->SetScale(scale);

	sprite = run_sprite;
}
//------------------------------------------------------------------------------------------------------------


// Action per frame for the hero
void Hero::Update(float deltaTime)
{
	//speed_increase +=

	input_component->Update(*this);
	physics_component->Update(*this);
	graphics_component->Update(*this);
	sprite->Update(deltaTime);

	float x, y;
	sprite->GetPosition(x, y);
	position_x = x;
	position_y = y;

}