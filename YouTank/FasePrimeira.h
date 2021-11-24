#pragma once
#include "Fase.h"
class FasePrimeira :
    public Fase
{
private:

    unsigned int contaPoteMel;

public:
    FasePrimeira();
    ~FasePrimeira();

    //Fun�oes
    void criarPlataforma();
    void criarObstaculos();
    void criarPoteMel();
    void updateFasePrimeira();
    void update();

    void renderFasePrimeira();

    const bool getTerminou() const;
};

