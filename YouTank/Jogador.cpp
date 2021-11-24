#include "stdafx.h"
#include "Jogador.h"

void Jogador::setDirecao_x(float dir_x)
{
	direcao.x = dir_x;
}

void Jogador::setDirecao_y(float dir_y)
{
	direcao.y = dir_y;
}

Jogador::Jogador(int vida, int dano, int id, int barraVida_y, int player):
	Personagem(vida, dano, id),
	colisaoBot(false),
	barraVida(static_cast<Personagem*>(this), 25.f, barraVida_y, 210.f, 25.f, player)
{
	direcao.x = 0.0f;
	direcao.y = 0.0f;
}

Jogador::~Jogador()
{
}

void Jogador::setOlhaEsquerda(bool x)
{
	olhaEsquerda = x;
}


const bool Jogador::olhandoEsquerda() const
{
	return olhaEsquerda;
}


const bool Jogador::getExisteNaFase() const
{
	return aparece;
}


void Jogador::naColisao()
{
	if (direcao.x < 0.0f)
	{
		//colisao na esquerda
		setVelocidadeX(0.0f);
		colisaoBot = false;
	}
	else if (direcao.x > 0.0f)
	{
		//colisao na direita
		setVelocidadeX(0.0f);
		colisaoBot = false;
	}
	if (direcao.y > 0.0f)
	{
		//colisao embaixo
		velocidade.y = 0.0f;
		podePular = true;
		colisaoBot = true;
	}
	else if (direcao.y < 0.0f)
	{
		//colisao em cima
		velocidade.y = 0.0f;
		colisaoBot = false;
	}
}

void Jogador::update()
{
	updateTaVivo();
	updateAnimacao();
	barraVida.update();
}

const bool Jogador::getColisaoBot() const
{
	return colisaoBot;
}

void Jogador::renderBarraVida()
{
	barraVida.renderBodyBack();
	barraVida.render();
}



void Jogador::updateAnimacao()
{
	if (olhaEsquerda)
	{
		body.setScale(1.f, 1.f);
	}
	else if (!olhaEsquerda)
	{
		body.setScale(-1.f, 1.f);
	}
	//caso esteja andando para a esquerda, vira a imagem

}

void Jogador::updateTaVivo()
{
	if (vida <= 0)
		aparece = false;
}