#include "stdafx.h"
#include "Components.h"



void KeyboardInputComponent::Update(Hero& hero)
{
	hero.SetInputActionCode(ANIM_FORWARDS);
	hero.SetInputSpeedCode(ANIM_FORWARDS);

	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		hero.SetInputActionCode(ANIM_FAST);
		hero.SetInputSpeedCode(ANIM_FAST);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		hero.SetInputActionCode(ANIM_SLOW);
		hero.SetInputSpeedCode(ANIM_SLOW);
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		hero.SetInputActionCode(ANIM_START_JUMP);
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		hero.SetInputActionCode(ANIM_SLIDE);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
	{
		hero.SetInputActionCode(ANIM_ATTACK);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_Y, true))
	{
		hero.SetInputActionCode(ANIM_START_JUMP_ATTACK);
	}
}


void PhysicsComponent::Update(Hero& hero)
{
	hero.SetSpeedIncrease(hero.GetSpeedIncrease() + SPEED_INCREASE_VALUE);

	if (hero.GetJumping() == true)
	{

		if (hero.GetRemainingJumpFrames() > 0)
		{
			hero.SetRemainingJumpFrames(hero.GetRemainingJumpFrames() - 1);

			if (hero.GetRemainingJumpFrames() > HERO_START_JUMP_MINIMUM_FRAME)
			{
				hero.SetInputActionCode(ANIM_START_JUMP);
				hero.SetPositionY(hero.GetPositionY() + hero.GetJumpHeight());
			}
			else if (hero.GetRemainingJumpFrames() > HERO_MID_JUMP_MINIMUM_FRAME)
			{
				hero.SetInputActionCode(ANIM_MID_JUMP);
			}
			else if (hero.GetRemainingJumpFrames() <= HERO_MID_JUMP_MINIMUM_FRAME)
			{
				hero.SetInputActionCode(ANIM_END_JUMP);
				hero.SetPositionY(hero.GetPositionY() - hero.GetJumpHeight());
			}
		}
		else
		{
			hero.SetJumping(false);
		}
	}
	else if (hero.GetAttacking() == true)
	{
		if (hero.GetRemainingAttackFrames() > 0)
		{
			hero.SetRemainingAttackFrames(hero.GetRemainingAttackFrames() - 1);
			hero.SetInputActionCode(ANIM_ATTACK);

		}
		else
		{
			hero.SetAttacking(false);
		}
	}
	else if (hero.GetJumpAttacking() == true)
	{
		if (hero.GetRemainingJumpAttackFrames() > 0)
		{
			hero.SetRemainingJumpAttackFrames(hero.GetRemainingJumpAttackFrames() - 1);

			if (hero.GetRemainingJumpAttackFrames() > HERO_START_JUMP_ATTACK_MINIMUM_FRAME)
			{
				hero.SetInputActionCode(ANIM_START_JUMP_ATTACK);
				hero.SetPositionY(hero.GetPositionY() + hero.GetJumpHeight());
			}
			else if (hero.GetRemainingJumpAttackFrames() > HERO_MID_JUMP_ATTACK_MINIMUM_FRAME)
			{
				hero.SetInputActionCode(ANIM_MID_JUMP_ATTACK);
			}
			else if (hero.GetRemainingJumpAttackFrames() > HERO_JUMP_ATTACK_FRAME)
			{
				hero.SetInputActionCode(ANIM_JUMP_ATTACK);
			}
			else if (hero.GetRemainingJumpAttackFrames() <= HERO_JUMP_ATTACK_FRAME)
			{
				hero.SetInputActionCode(ANIM_END_JUMP_ATTACK);
				hero.SetPositionY(hero.GetPositionY() - hero.GetJumpHeight());
			}

		}
		else
		{
			hero.SetJumpAttacking(false);
		}
	}
	else
	{
		if (hero.GetInputActionCode() == ANIM_START_JUMP)
		{
			hero.SetJumping(true);
			hero.SetRemainingJumpFrames(HERO_ALL_JUMP_FRAMES);
		}
		if (hero.GetInputActionCode() == ANIM_ATTACK)
		{
			hero.SetAttacking(true);
			hero.SetRemainingAttackFrames(HERO_ALL_ATTACK_FRAMES);
		}
		if (hero.GetInputActionCode() == ANIM_START_JUMP_ATTACK)
		{
			hero.SetJumpAttacking(true);
			hero.SetRemainingJumpAttackFrames(HERO_ALL_JUMP_ATTACK_FRAMES);
		}
	}
	if (hero.GetInputSpeedCode() == ANIM_FORWARDS)
	{
		hero.SetCurrentSpeed(NORMAL_SPEED + hero.GetSpeedIncrease());
	}
	if (hero.GetInputSpeedCode() == ANIM_FAST)
	{
		hero.SetCurrentSpeed(FAST_SPEED + hero.GetSpeedIncrease());
	}
	if (hero.GetInputSpeedCode() == ANIM_SLOW)
	{
		hero.SetCurrentSpeed(SLOW_SPEED + hero.GetSpeedIncrease());
	}
}


void GraphicsComponent::Update(Hero& hero)
{

	if (hero.GetInputActionCode() == ANIM_FORWARDS || hero.GetInputActionCode() == ANIM_FAST || hero.GetInputActionCode() == ANIM_SLOW)
	{
		if (hero.GetCurrentSpriteType() != RUN_SPRITE)
		{
			hero.SetSprite(hero.GetRunSprite());
			hero.SetCurrentSpriteType(RUN_SPRITE);
		}
	}
	else if (hero.GetInputActionCode() == ANIM_START_JUMP || hero.GetInputActionCode() == ANIM_END_JUMP || hero.GetInputActionCode() == ANIM_MID_JUMP)
	{
		if (hero.GetCurrentSpriteType() != JUMP_SPRITE)
		{
			hero.SetSprite(hero.GetJumpSprite());
			hero.SetCurrentSpriteType(JUMP_SPRITE);
		}
	}
	else if (hero.GetInputActionCode() == ANIM_START_JUMP_ATTACK || hero.GetInputActionCode() == ANIM_END_JUMP_ATTACK || hero.GetInputActionCode() == ANIM_MID_JUMP_ATTACK || hero.GetInputActionCode() == ANIM_JUMP_ATTACK)
	{
		if (hero.GetCurrentSpriteType() != JUMP_ATTACK_SPRITE)
		{
			App::PlaySound(".\\TestData\\slice4.wav");
			hero.SetSprite(hero.GetJumpAttackSprite());
			hero.SetCurrentSpriteType(JUMP_ATTACK_SPRITE);
		}
	}
	else if (hero.GetInputActionCode() == ANIM_SLIDE)
	{
		hero.SetSprite(hero.GetCrouchSprite());
		hero.SetCurrentSpriteType(CROUCH_SPRITE);
		
	}
	else if (hero.GetInputActionCode() == ANIM_ATTACK)
	{
		if (hero.GetCurrentSpriteType() != ATTACK_SPRITE)
		{
			PlaySound(TEXT(".\\TestData\\sword.wav"), NULL, SND_ASYNC | SND_FILENAME);
			hero.SetSprite(hero.GetAttackSprite());
			hero.SetCurrentSpriteType(ATTACK_SPRITE);
		}
	}


	hero.GetSprite()->SetAnimation(hero.GetInputActionCode());

	hero.GetSprite()->SetPosition(hero.GetPositionX(), hero.GetPositionY());
}
