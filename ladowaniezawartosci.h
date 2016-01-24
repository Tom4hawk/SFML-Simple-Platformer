#ifndef LADOWANIEZAWARTOSCI_H
#define LADOWANIEZAWARTOSCI_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#include "globalne.h"


class LadowanieZawartosci
{
	public:
		LadowanieZawartosci(const char *filename);
		void DrawMap(sf::RenderWindow &Window);
		std::vector < std::vector <int> > MapVector;
		std::vector < sf::Image > textureVector;
	private:
		enum Identifier { MAP, TEXTURE };
		int loadType;
};

#endif
