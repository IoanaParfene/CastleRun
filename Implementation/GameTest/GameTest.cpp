//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "GameState.h"
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Game Object
//------------------------------------------------------------------------
GameState* game_state;
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Game Object Initialization
//------------------------------------------------------------------------
void Init()
{
	//------------------------------------------------------------------------
	// Instantiate the Game Object
	game_state = new GameState();
}


//------------------------------------------------------------------------
// Physics and game Logic updates per frame
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	//------------------------------------------------------------------------
	// Change between screens
	//------------------------------------------------------------------------
	if (game_state->GetCurrentScreen() == MENU)
	{
		game_state->UpdateMainMenuScreen(deltaTime);
	}
	else if (game_state->GetCurrentScreen() == GAME)
	{
		game_state->UpdateGameScreen(deltaTime);
	}
	else if (game_state->GetCurrentScreen() == PAUSE)
	{
		game_state->UpdatePauseScreen();
	}
	else if (game_state->GetCurrentScreen() == OVER)
	{
		game_state->UpdateGameOverScreen(deltaTime);
	}
}


//------------------------------------------------------------------------
// Display calls for all the sprites
//------------------------------------------------------------------------
void Render()
{	
	//------------------------------------------------------------------------
	// Render the sprites for the specific screen
	//------------------------------------------------------------------------
	if (game_state->GetCurrentScreen() == MENU)
	{
		game_state->RenderMainMenuScreen();
	}
	else if (game_state->GetCurrentScreen() == GAME)
	{
		game_state->RenderGameScreen();
	}
	else if (game_state->GetCurrentScreen() == PAUSE)
	{
		game_state->RenderPauseScreen();
	}
	else if (game_state->GetCurrentScreen() == OVER)
	{
		game_state->RenderGameOverScreen();
	}
}

//------------------------------------------------------------------------
// Shutdown Code
//------------------------------------------------------------------------
void Shutdown()
{	
	//game_state->Shutdown();
	//------------------------------------------------------------------------
	// Example Sprite Code....
	// delete &sprite_vector;
	//------------------------------------------------------------------------
}