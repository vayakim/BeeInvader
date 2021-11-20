#pragma once
#include "GameState.h"
#include "Background.h"
#include "Button.h"

class MenuState :
    public State
{
private:
    Background background;
    std::map<std::string, Button*> buttons;

    void initButtons();

public:
    MenuState(std::stack<State*>* state, InputManager* pIM);
    ~MenuState();

    const short getState();
    
    void endState();

    void updateButtons();
    void updateInput();
    void update();

    void renderButtons();
    void render();
};

