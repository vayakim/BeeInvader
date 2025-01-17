#include "stdafx.h"
#include "FasePrimeira.h"
#include "Global.h"
using namespace Fases;
using namespace Jogadores;
using namespace ElementosVisuais;

FasePrimeira::FasePrimeira() :
	Fase()
{
	Ente::pLista = &listaEntidades;
	initInimigo();
	gerenciadorColisao.setGerenciadorGrafico(pGrafico);
	obstaculosMAX = rand() % 3 + 3;
	contaPoteMel = 0;
}

FasePrimeira::~FasePrimeira()
{

}

void FasePrimeira::criarPoteMel()
{

	/*=====================POTES DE MEL=========================*/
	/*															*/
	/*	CRIA POTES DE MEL RANDOMICAMENTE					    */
	/*	Potes de mel d�o ao player pontos para o ranking		*/
	/*==========================================================*/

	if (contaPoteMel < 1)
	{
		PoteMel* pote = new PoteMel();
		listaEntidades.incluaEntidade(static_cast<Entidade*>(pote));
		contaPoteMel++;
	}
}

void FasePrimeira::criarObstaculos()
{

	/*=====================OBSTACULOS===========================*/
	/*															*/
	/*  CRIA OBSTACULOS PELA FASE DE FORMA RANDOMICA			*/
	/*==========================================================*/
	if (contaObstaculos < obstaculosMAX)
	{
		Espinhos* espinhos = new Espinhos((float)(rand() % 1180 + 100), 620.f);
		listaEntidades.incluaEntidade(static_cast<Entidade*>(espinhos));
		contaObstaculos++;
	}

}

void FasePrimeira::criarPlataforma()
{
	/*=====================PLATAFORMAS==========================*/
	/*															*/
	/*	CRIA PLATAFORMAS OU FAVOS DE MEL RANDOMICAMENTE			*/
	/*==========================================================*/


	//chao principal
	Plataforma* plat = new Plataforma();
	listaEntidades.incluaEntidade(static_cast<Entidade*>(plat));

	//favo mel principal
	FavoMel* favo = new FavoMel(60.f, 600.f);
	favo->setVelocidadeY(0.0f);
	listaEntidades.incluaEntidade(static_cast<Entidade*>(favo));

	//plataformas ou favos de mel ao longo do eixo x na fase
	int random;
	int contaPlat = 0;
	for (int i = 180; i <= 1140; i += 120)
	{
		random = rand() % 2;
		if (random || contaPlat > 5)
		{	//cria nova plataforma em uma posi��o x randomizada
			FavoMel* favo1 = new FavoMel((float) i, static_cast<float>(rand() % 400 + 100));
			listaEntidades.incluaEntidade(static_cast<Entidade*>(favo1));
		}
		else
		{	//cria nova plataforma em uma posi��o y randomizada
			Plataforma* plat1 = new Plataforma(100.f, 20.f, (float) i, static_cast<float>(rand() % 400 + 100));
			listaEntidades.incluaEntidade(static_cast<Entidade*>(plat1));
			contaPlat++;
		}
			
	}
}

void FasePrimeira::updateFasePrimeira()
{
	for (int i = 0; i < listaEntidades.getTamanho(); i++)
	{
		switch (listaEntidades.operator[](i)->getId())
		{
		case ID_POTEMEL:
		{
			//update contato com o pote de mel, objetivo que d� pontos
			if (gerenciadorColisao.verificaContatoJogador(listaEntidades.operator[](i), static_cast<Jogador*>(pFadaCaida)))
			{
				listaEntidades.operator[](i)->setShowing(false);
				pFadaCaida->coletouPoteMel();
				contaPoteMel--;
			}
		}
		break;
		case ID_PLATAFORMA:
		{
			//movimenta as plataformas para cima e para baixo
			if (listaEntidades.operator[](i)->getPosition().y > 550)
				listaEntidades.operator[](i)->setVelocidadeY(listaEntidades.operator[](i)->getVelocidadeY() * -1);
			else if (listaEntidades.operator[](i)->getPosition().y < 100)
				listaEntidades.operator[](i)->setVelocidadeY(listaEntidades.operator[](i)->getVelocidadeY() * -1);
			listaEntidades.operator[](i)->movePlataforma();
		}
		break;
		case ID_FAVOMEL:
		{
			//movimenta os favos de mel para cima e para baixo
			if (listaEntidades.operator[](i)->getPosition().y > 550)
				listaEntidades.operator[](i)->setVelocidadeY(listaEntidades.operator[](i)->getVelocidadeY() * -1);
			else if (listaEntidades.operator[](i)->getPosition().y < 100)
				listaEntidades.operator[](i)->setVelocidadeY(listaEntidades.operator[](i)->getVelocidadeY() * -1);
			listaEntidades.operator[](i)->movePlataforma();
		}
		break;
		}
	}
}

void FasePrimeira::update()
{
	updateColisoes();
	limpeza();
	criarCogumelos();
	criarAbelhas(1);
	criarObstaculos();
	criarPoteMel();
	updateMovimento();
	updateCombate();
	updateInimigoPlataforma();
	updateFasePrimeira();
	pFadaCaida->update();

	if (pCurandeira != NULL)
		pCurandeira->update();
}

void FasePrimeira::renderFasePrimeira()
{
	plano_fundo.render();

	for (int i = 0; i < listaEntidades.getTamanho(); i++)
	{
		if (listaEntidades.operator[](i)->getShowing())
		{
			listaEntidades.operator[](i)->render();
		}
		
	}

	pFadaCaida->renderJogador();

	if (pCurandeira != NULL)
		pCurandeira->renderJogador();
}

void FasePrimeira::salvar()
{
	reiniciarArquivos();
	for (int i = 0; i < listaEntidades.getTamanho(); i++)
	{
		listaEntidades[i]->salvar();
	}
	pFadaCaida->salvar();

	if (pCurandeira != NULL)
		pCurandeira->salvar();
}

void FasePrimeira::recuperar()
{
	recuperarObstaculos();
	recuperarAbelhas();
	recuperarCogumelos();
	pFadaCaida->recuperar();
	recuperarProjetil();
	recuperarPoteMel();

	if (pCurandeira != NULL)
		pCurandeira->recuperar();
}

void FasePrimeira::recuperarPoteMel()
{
	std::ifstream recuperar("./Carregamentos/PoteMel.txt", std::ios::in);
	if (!recuperar)
	{
		std::cout << "arquivo n�o pode ser aberto" << std::endl;
		fflush(stdin);
		return;
	}
	float posX, posY;
	while (recuperar >> posX >> posY)
	{
		PoteMel* pAux = new PoteMel();
		pAux->setPosition(posX, posY);
		listaEntidades.incluaEntidade(pAux);
		contaPoteMel++;
	}
	recuperar.close();
}

const bool FasePrimeira::getTerminou() const
{
	if (pFadaCaida->getPoteMel() >= 1)
		return true;
	else
		return false;
}