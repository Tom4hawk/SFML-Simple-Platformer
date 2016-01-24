#include "animation.h"

void Animation::Inicjalizacja(float x, float y, int FrameX, int FrameY, sf::Image &tymczasowy){
	licznikKlatek = 0;
	zmienKlatke = 0.5;
	aktywna = false;
	this -> x = x;
	this -> y = y;
	this -> ileKlatekX = FrameX;
	this -> ileKlatekY = FrameY;
	Sprajt.SetImage(tymczasowy);
	SzerokoscKlatki = Sprajt.GetImage()->GetWidth() / ileKlatekX;
	WysokoscKlatki = Sprajt.GetImage()->GetHeight() / ileKlatekY;
}

void Animation::ustawAktywne(bool wart){
	aktywna = wart;
}

bool Animation::pobierzAktywne(){
	return aktywna;
}

int Animation::pobierzAktualnaRamke(int os){
	if(os == 1){
		return aktualnaRamkaX;
	} else{
		return aktualnaRamkaY;
	}
}

void Animation::ustawAktualnaRamke(int os, int wart){
	if(os == 1){
		aktualnaRamkaX = wart;
	} else{
		aktualnaRamkaY = wart;
	}
}

float Animation::pobierzPozycje(int os){
	if(os == 1){
		return x;
	} else{
		return y;
	}
}

void Animation::ustawPozycje(int os, int wart){
	if(os == 1){
		x = wart;
	} else{
		y = wart;
	}

}

void Animation::Aktualizacja(sf::RenderWindow &Window){

	if(aktywna)
		licznikKlatek += Zegar.GetElapsedTime();
	else
		licznikKlatek = 0;

	if(licznikKlatek >= zmienKlatke){
		licznikKlatek = 0;
		Zegar.Reset();
		aktualnaRamkaX += SzerokoscKlatki;

		if( (unsigned int)aktualnaRamkaX >= Sprajt.GetImage()->GetWidth() )
			aktualnaRamkaX = 0;
	}

	Sprajt.SetSubRect( sf::IntRect(aktualnaRamkaX, aktualnaRamkaY * WysokoscKlatki, aktualnaRamkaX + SzerokoscKlatki, aktualnaRamkaY * WysokoscKlatki + WysokoscKlatki) );
	Sprajt.SetPosition(x, y);
}

void Animation::Rysuj(sf::RenderWindow &Window){
	Window.Draw(Sprajt);
}
