#ifndef WROG_H
#define WROG_H

#include "gracz.h"
#include "kaboom.h"

class Wrog: public Gracz, public kaboom
{
	public:
		Wrog();
		void Aktualizacja(sf::RenderWindow &Window);
		void kolizjaigrawitacja();
	protected:
		bool prawo;//true - idzie w prawo, false idzie w lewo
		bool kolizjaGoraLewo;
		bool kolizjaGoraPrawo;
		bool kolizjaDolLewo;
		bool kolizjaDolPrawo;


};

#endif
