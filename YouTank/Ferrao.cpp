#include "stdafx.h"
#include "Global.h"
#include "Ferrao.h"

Ferrao::Ferrao(float pos_x, float pos_y, float x_jogador, float y_jogador):
	Projetil(ID_FERRAO)
{
	setTexture("Imagens/ferrao.png");
	setSize(30.f, 30.f);
	setOriginCenter();
	setPosition(pos_x, pos_y);
	setRapidez(1.f);
	jogX = x_jogador;
	jogY = y_jogador;
	x_jogador -= getPosition().x;
	y_jogador -= getPosition().y;
	direcao.x = x_jogador / sqrtf(static_cast<float>(pow(x_jogador, 2)) + static_cast<float>(pow(y_jogador, 2)));
	direcao.y = y_jogador / sqrtf(static_cast<float>(pow(x_jogador, 2)) + static_cast<float>(pow(y_jogador, 2)));
}

Ferrao::~Ferrao()
{
}

void Ferrao::updateFerrao()
{
	move(direcao.x * rapidez, direcao.y * rapidez);
	rotate(2.f);
}

void Ferrao::salvar()
{
	if (getShowing())
	{
		std::ofstream gravador("./Carregamentos/Ferrao.txt", std::ios::app);
		if (!gravador)
		{
			std::cout << "arquivo n�o pode ser aberto" << std::endl;
			fflush(stdin);
			return;
		}
		gravador
			<< jogX+getPosition().x << " "
			<< jogY+getPosition().y << " "
			<< getPosition().x << " "
			<< getPosition().y << std::endl;
		gravador.close();
	}
}
