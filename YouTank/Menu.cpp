#include "stdafx.h"
#include "Menu.h"

GraphicManager* Menu::pGraphic = NULL;

Menu::Menu():
	background()
{
	fonte = pGraphic->getFont();
}

Menu::Menu(const char* file, float escala):
	background(file,escala)
{
	fonte = pGraphic->getFont();
}

Menu::~Menu()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void Menu::setGraphicManager(GraphicManager* pGM)
{
	if (pGM)
		pGraphic = pGM;

	else
		std::cout << "ERROR::STATE::SETGRAPHICMANAGER::Ponteiro Nulo" << std::endl;
}

void Menu::renderButtons()
{
	for (auto& it : buttons)
	{
		it.second->render();
		it.second->renderText();
	}
}

void Menu::renderText()
{
	pGraphic->render(texto);
}