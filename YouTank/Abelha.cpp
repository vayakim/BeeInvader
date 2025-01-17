#include "stdafx.h"
#include "Global.h"
#include "Abelha.h"
using namespace Inimigos;

Abelha::Abelha(int i):
	Inimigo(1, 1, ID_ABELHA, 2)
{
	initShape();
	if (i == 1)
	{
		int x = rand() % 2;
		if (x)
			setPosition(10.f, static_cast<float>(rand() % 500 + 25));
		else
			setPosition(1200.f, static_cast<float>(rand() % 500 + 25));
	}
	else if(i == 2)
		setPosition(static_cast<float> (rand() % 1100 + 25), static_cast<float>(rand() % 50 + 25));
	
		
	setRapidez(8.f);
	olhaEsquerda = true;
}

Abelha::Abelha(float posX, float posY) :
	Inimigo(1, 1, ID_ABELHA, 2)
{
	initShape();
	setRapidez(8.f);
	olhaEsquerda = true;
	setPosition(posX, posY);
}

Abelha::~Abelha()
{
}

float Abelha::getDirecao_x()
{
	return direcao.x;
}

float Abelha::getDirecao_y()
{
	return direcao.y;
}

void Abelha::setShowing(bool x)
{
	aparece = x;
}

const bool Abelha::getShowing() const
{
	return aparece;
}

void Abelha::persegue(float x_jogador, float y_jogador)
{
	
	x_jogador -= getPosition().x;
	y_jogador -= getPosition().y;
	
	//normaliza o vetor dire��o, que aponta para o jogador
	direcao.x = x_jogador / sqrtf(static_cast<float>(pow(x_jogador, 2)) + static_cast<float>(pow(y_jogador, 2)));
	direcao.y = y_jogador / sqrtf(static_cast<float>(pow(x_jogador, 2)) + static_cast<float>(pow(y_jogador, 2)));
	if (direcao.x > 0)
	{
		if(olhaEsquerda)
			body.setScale(-1.f * body.getScale().x, body.getScale().y);
		olhaEsquerda = false;
	}
	else if (direcao.x < 0)
	{
		if (!olhaEsquerda)
			body.setScale(-1.f * body.getScale().x, body.getScale().y);
		olhaEsquerda = true;
	}

	//movimenta a abelha na dire��o do jogador com sua rapidez
	this->body.move(direcao.x * rapidez, direcao.y * rapidez);
}

void Abelha::salvar()
{
	if (getShowing())
	{
		std::ofstream gravador("./Carregamentos/Abelha.txt", std::ios::app);
		if (!gravador)
		{
			std::cout << "arquivo n�o pode ser aberto" << std::endl;
			fflush(stdin);
			return;
		}
		gravador
			<< getPosition().x << " "
			<< getPosition().y << std::endl;
		gravador.close();
	}
}


void Abelha::initShape()
{
	setSize(30.f, 30.f);
	setTexture("Imagens/bee.png");
	setOriginCenter();
	
}
