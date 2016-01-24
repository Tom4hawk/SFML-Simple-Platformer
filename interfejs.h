#ifndef INTERFEJS_H
#define INTERFEJS_H

#include <SFML/Graphics.hpp>
#include <sstream>

class Interfejs
{
	public:
		void Inicjalizacja(const char *nazwapliku);
		void Aktualizacja(int ile_hp, int ile_pkt);
		void Rysuj(sf::RenderWindow &Window);
	private:
		sf::View Interfejs;
		sf::Font FontInterfejsu;

		int hp, pkt;
		std::ostringstream ss;
};

#endif
