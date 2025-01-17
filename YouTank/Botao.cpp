#include "stdafx.h"
#include "Global.h"
#include "Botao.h"
using namespace ElementosVisuais;


bool Botao::mousePressionado = false;

void Botao::initText(std::string text)
{
	//Inicializa o texto do bot�o
	fonte = pGrafico->getFont();

	texto.setFont(*fonte);
	texto.setString(text);
	texto.setFillColor(sf::Color::White);
	texto.setOutlineColor(sf::Color::Black);
	texto.setOutlineThickness(1.f);
	texto.setCharacterSize(40);
	texto.setPosition(
		getPosition().x + getBounds().width / 2.f - texto.getGlobalBounds().width / 2.f,
		getPosition().y + getBounds().height / 3.f - texto.getGlobalBounds().height / 2.f);
}

void Botao::initShape(float x, float y)
{
	//Inicializa a forma e cor do bot�o
	setSize(260, 50);
	setPosition(x, y);
	setOutline(2.f);
	red = 100;
	green = 100;
	blue = 100;

	setCor(red, green, blue, 255);
}

Botao::Botao(float y, std::string text):
	Ente()
{
	id = ID_BUTTON;
	estadoBotao = BT_IDLE;

	initShape(510,y);
	initText(text);
}

Botao::~Botao()
{
}

const bool Botao::estaPressionado() const
{
	//Indica se o bot�o est� pressionado ou n�o
	if (estadoBotao == BT_PRESSIONADO)
		return true;
	else
		return false;
}

void Botao::update(const float posX, const float posY)
{
	estadoBotao = BT_IDLE;

	//mouse em cima do borao
	if (contem(posX, posY))
	{
		estadoBotao = BT_EMCIMA;

		//botao pressionado
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//s� um clique permitido nos bot�o
			if (mousePressionado == false)
			{
				mousePressionado = true;
				estadoBotao = BT_PRESSIONADO;
			}
		}
		else
		{
			mousePressionado = false;
		}
	}

	/*Muda a cor do bot�o dependendo do seu estado*/
	switch (estadoBotao)
	{
	case BT_IDLE:
		setCor(red, green, blue, 255);
		break;

	case BT_EMCIMA:
		setCor(red, green, blue+60, 255);
		break;

	case BT_PRESSIONADO:
		setCor(red, green, blue+120, 255);
		break;

	default:
		setCor(255, 0, 0, 255);
		break;
	}
}

void Botao::setText(std::string novoTexto)
{
	texto.setString(novoTexto);

	texto.setPosition(
		getPosition().x + getBounds().width / 2.f - texto.getGlobalBounds().width / 2.f,
		getPosition().y + getBounds().height / 3.f - texto.getGlobalBounds().height / 2.f);
}

void Botao::renderText()
{
	renderTexto(texto);
}
