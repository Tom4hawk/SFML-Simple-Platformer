#ifndef GRACZ_H
#define GRACZ_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include "animation.h"
#include "globalne.h"

class Gracz
{
	public:
		//Niezbedne do wywolania funkcje
		void Inicjalizacja(
			std::vector < std::vector <int> > &Mapa,
			int koordynatystartowe_x,
			int koordynatystartowe_y,
			float predkosc_poruszania,
			float predkosc_skakania,
			float grawitacja_p,
			const char *nazwapliku,
			int ileklatek_x,
			int ileklatek_y
		);
		void UstawDzwiekSkoku(const char *nazwapliku);
		void Aktualizacja(sf::RenderWindow &Window);
		void Rysuj(sf::RenderWindow &Window);
		//Funkcje pozwalające się dobrać do koordynatów postaci z zewnątrz
		float pobierzX();
		float pobierzY();
		void ZmusDoSkoku();
		float startX, startY;
		float x, y;
	protected:
		Animation animacja;
		bool skok;
		//Zmienne SFML
		sf::Image ObrazekGracz;
		sf::Vector2f graczPrzyspieszenie;
		//zmienne STD
		std::vector < std::vector <int> > MapaKolizji;
		//Zmienne
		
		int aktualnaRamkaX, aktualnaRamkaY;
		int wysokoscGruntu;

		float predkoscPoruszania;
		float grawitacja;
		float skok_predkosc;
		bool CzySieRusza;
		//Funkcje
		void kolizjaigrawitacja();

	private:
		sf::Sound DzwiekSkoku;
		sf::SoundBuffer bufor;
		bool czy_dzwiek_skok;

};

#endif
