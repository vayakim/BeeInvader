#include "stdafx.h"
#include "Global.h"
#include "FadaCaida.h"
using namespace Jogadores;

void FadaCaida::initShape()	
{
	setSize(50.f, 50.f);
	setTexture("Imagens/red_fairy.png");
	setOriginCenter();
	setPosition(80.f, 500.f);
}

FadaCaida::FadaCaida():
	Jogador(100,100, ID_JOGADOR, 20.f, 1),
	pOrbe(NULL)
{
	rapidez = 25.f;
	alturaPulo = 100.f;
	cooldownAtaqueMax = 30.f;
	colisaoBot = false;
	cooldownAtaque = 0.f;
	quantosPoteMel = 0;
	pontos = 0;
	initShape();
}

FadaCaida::~FadaCaida()
{
	if (pOrbe)
		delete pOrbe;
}


void FadaCaida::ataca(float dir_x, float dir_y)
{
	Orbe* pP = new Orbe(dir_x, dir_y, 80.f, getPosition().x, getPosition().y);
	pLista->incluaEntidade(static_cast<Entidade*>(pP));
}

void FadaCaida::coletouPoteMel()
{
	quantosPoteMel++;
}

const int FadaCaida::getPoteMel() const
{
	return quantosPoteMel;
}

void FadaCaida::update()
{
	updateAnimacao();
	updateTaVivo();
	barraVida.update();
}

void FadaCaida::operator+=(int i)
{
	pontos += i;
}

void FadaCaida::salvar()
{
	if (getShowing())
	{
		std::ofstream gravadorFada("./Carregamentos/FadaCaida.txt", std::ios::out);
		if (!gravadorFada)
		{
			std::cout << "arquivo n�o pode ser aberto" << std::endl;
			fflush(stdin);
			return;
		}
		gravadorFada << direcao.x << " "
			<< direcao.y << " "
			<< podeAtacar << " "
			<< podePular << " "
			<< pontos << " "
			<< velocidade.x << " "
			<< velocidade.y << " "
			<< vida << " "
			<< getPosition().x  << " "
			<< getPosition().y << std::endl;
		gravadorFada.close();
		
	}
}

void FadaCaida::recuperar()
{
	std::ifstream recuperarFada("./Carregamentos/FadaCaida.txt", std::ios::in);
	if (!recuperarFada)
	{
		std::cout << "arquivo n�o pode ser aberto" << std::endl;
		fflush(stdin);
		return;
	}
	float pos_x, pos_y;
	recuperarFada >> direcao.x >> direcao.y
		>> podeAtacar 
		>> podePular
		>> pontos
		>> velocidade.x >> velocidade.y
		>> vida
		>> pos_x >> pos_y;
	recuperarFada.close();
	setPosition(pos_x, pos_y);
}

void FadaCaida::setPontos(int pnts)
{
	pontos = pnts;
}
