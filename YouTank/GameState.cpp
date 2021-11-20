#include "stdafx.h"
#include "GameState.h"

void GameState::runFase()
{
	switch (fase)
	{
	case 1:
		fasePrimeira = new FasePrimeira();
		fasePrimeira->spawnPlataforma();
		pInput->setFase(static_cast<Fase*>(fasePrimeira));
		break;

	case 2:
		break;

	default:
		std::cout << "ERROR::GAMESTATE::Fase n�o existente" << std::endl;
		break;
	}
}

//Construtora e Destrutora
GameState::GameState(std::stack<State*>* state, InputManager* pIM, short f):
	State(state,pIM),
	fasePrimeira(NULL)
{
	stateID = GAME_STATE;
	fase = f;
	runFase();
	
}

GameState::~GameState()
{
	switch (fase)
	{
	case 1:
		delete fasePrimeira;
		break;

	case 2:
		break;

	default:
		std::cout << "ERROR::GAMESTATE::Fase n�o existente" << std::endl;
		break;
	}
}

void GameState::setPause(bool p)
{
	pause = p;
}

const short GameState::getState()
{
	return stateID;
}

const bool GameState::getPause() const
{
	return pause;
}

void GameState::endState()
{
	std::cout << "ending game state" << std::endl;
}


void GameState::updatePause()
{
	if (pause == true)
	{
		states->push(new PauseState(states, pInput));
	}
		
}

void GameState::updateInput()
{
	verificarPause();
}

void GameState::update()
{
	updateInput();
	updatePause();
	switch (fase)
	{
	case 1:
		fasePrimeira->update();
		break;

	case 2:
		break;

	default:
		std::cout << "ERROR::GAMESTATE::Fase n�o existente" << std::endl;
		break;
	}
	
}

void GameState::render()
{
	switch (fase)
	{
	case 1:
		fasePrimeira->renderFasePrimeira();
		break;

	case 2:
		break;

	default:
		std::cout << "ERROR::GAMESTATE::Fase n�o existente" << std::endl;
		break;
	}
	
}
