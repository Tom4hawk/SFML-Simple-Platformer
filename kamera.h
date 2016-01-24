#ifndef KAMERA_H
#define KAMERA_H

#include <SFML/Graphics.hpp>
#include "globalne.h"


class Kamera
{
	public:
		void Aktualizacja(int x, int y, int rozmiar_mapy);
		void Rysuj(sf::RenderWindow &Window);
		
	protected:
		sf::View PozycjaKamery;
		float kameraX, kameraY;
};

#endif
