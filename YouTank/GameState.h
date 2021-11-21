#pragma once
#include "State.h"
#include "FasePrimeira.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "FaseSegunda.h"

class GameState: public State
{
private:
    FadaCaida* jogador1;

    FasePrimeira* fasePrimeira;
    FaseSegunda* faseSegunda;

   
    short fase;
    bool multiplayer;

    //aux
    sf::Clock clock;
    float deltaTime;

    //Fun��es Inicializadoras
    void runFase();
    void updateDeltaTime();
    
public:

    //Construtora e Destrutora
    GameState(std::stack<State*>* state, InputManager* pIM, short fase, bool multip = false);
    ~GameState();

    void setPause(bool p);
    const short getState();
    const bool getPause() const;
    void endState();

    void verificarGameOver();

    void updatePause();
    void updateGameOver();
    void updateInput();
    void update();
    void render();
    
    
};

