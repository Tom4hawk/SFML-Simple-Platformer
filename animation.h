#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "globalne.h"

class Animation
{
	public:
		void Inicjalizacja(float x, float y, int FrameX, int FrameY, sf::Image &tymczasowy);
		void Aktualizacja(sf::RenderWindow &Window);
		void Rysuj(sf::RenderWindow &Window);

		void ustawAktywne(bool wart);
		void ustawAktualnaRamke(int os, int wart);
		void ustawPozycje(int os, int wart);
	private:
		//Funkcje
		float pobierzPozycje(int os);
		int pobierzAktualnaRamke(int os);	
		bool pobierzAktywne();		
		//Zmienne
		int SzerokoscKlatki, WysokoscKlatki;
		sf::Sprite Sprajt;
		sf::Clock Zegar;
		bool aktywna;
		float licznikKlatek, zmienKlatke;
		float x, y;
		int aktualnaRamkaX, aktualnaRamkaY, ileKlatekX, ileKlatekY;
};

#endif
