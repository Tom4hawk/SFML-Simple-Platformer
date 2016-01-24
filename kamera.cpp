#include "kamera.h"

void Kamera::Aktualizacja(int x, int y, int rozmiar_mapy){
	kameraX = -(SzerokoscEkranu /2) + x;


	if (kameraX < 0)
		kameraX = 0;
	if ( (kameraX + SzerokoscEkranu) > (rozmiar_mapy * BLOCKSIZE) )
		kameraX =(rozmiar_mapy * BLOCKSIZE) - SzerokoscEkranu;


	PozycjaKamery.SetFromRect( sf::FloatRect(kameraX, 0, kameraX + SzerokoscEkranu, 0 + WysokoscEkranu) );
}

void Kamera::Rysuj(sf::RenderWindow &Window){
	Window.SetView(PozycjaKamery);
}
