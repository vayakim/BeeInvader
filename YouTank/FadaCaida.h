#pragma once
#include "Jogador.h"
#include "Orbe.h"


class FadaCaida :
    public Jogador
{
private:
    Orbe* pOrbe;
    bool colisaoBot;
    int quantosPoteMel;
    //private functions
    void initShape();

public:
    FadaCaida();
    ~FadaCaida();

    void ataca(float dir_x, float dir_y);
    void coletouPoteMel();
    const int getPoteMel() const;
    void update();

    void operator+=(int i);
    void salvar();
    void recuperar();

    void setPontos(int pnts);
};


