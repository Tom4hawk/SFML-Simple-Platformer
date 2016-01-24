#include "wrog.h"


Wrog::Wrog(){
	Init();
	prawo = false;
}
void Wrog::kolizjaigrawitacja(){
	float bottom = (y + 54) / BLOCKSIZE; //rozmiary gracza!!!!!
	float left = (x / BLOCKSIZE); 
	float right = (x + 32) / BLOCKSIZE;//szerokość
	float top = (y / BLOCKSIZE);
	
	kolizjaGoraLewo = false;
	kolizjaGoraPrawo = false;
	kolizjaDolLewo = false;
	kolizjaDolPrawo = false;
	//Czy dwie poniże potrzebne?
	bool kolizjaGrawLewo = false;
	bool kolizjaGrawPrawo = false;
	float orygx = x;
	
	if( y < 0 )
		y = 0;
	if( x < 0 )
		x = 0;
		
	if(MapaKolizji[(int)top][(int)left] >= 0){
		kolizjaGoraLewo = true;
	}
	if(MapaKolizji[(int)top][(int)right] >= 0){
		kolizjaGoraPrawo = true;
	}
	if(MapaKolizji[(int)bottom][(int)left] >= 0){
		kolizjaDolLewo = true;
	}
	if(MapaKolizji[(int)bottom][(int)right] >= 0){
		kolizjaDolPrawo = true;
	}

	if(MapaKolizji[(int)bottom+1][(int)right] >= 0){
		kolizjaGrawLewo = true;
	}
	
	if(MapaKolizji[(int)bottom+1][(int)left] >= 0){
		kolizjaGrawPrawo = true;
	}

	//Wylapywanie kolizji
	if (kolizjaGoraPrawo){
		x = orygx - 1;
		graczPrzyspieszenie.y = 2*grawitacja;
		graczPrzyspieszenie.x = 0;
	}

	if (kolizjaDolPrawo){
		if(!kolizjaGoraPrawo){
			x = orygx - 1;
			graczPrzyspieszenie.x = 0;
		}
	}

	if (kolizjaGoraLewo){
		x = orygx + 1;
		graczPrzyspieszenie.y = 2*grawitacja;
		graczPrzyspieszenie.x = 0;
	}

	if (kolizjaDolLewo){
		if(!kolizjaGoraPrawo){
			x = orygx + 1;
			graczPrzyspieszenie.x = 0;
		}
	}
	//Grawitacja i związana z tym kolizja
	if ( (kolizjaGrawPrawo == false) && (kolizjaGrawLewo == false)){
		wysokoscGruntu = ((int)bottom + 1) * BLOCKSIZE;
	}


	if ( kolizjaDolLewo==true && kolizjaDolPrawo==true){ //rozwiązuje problem grawitacji
			wysokoscGruntu = ((int)bottom - 1) * BLOCKSIZE;
	}
	
	
}

void Wrog::Aktualizacja(sf::RenderWindow &Window){
	animacja.ustawAktywne(true);
	
	kolizjaigrawitacja();
	
	if(!skok){
		graczPrzyspieszenie.y += grawitacja;
		aktualnaRamkaY = 0;
	} else
		graczPrzyspieszenie.y = 0;
	
	if(kolizjaGoraLewo || kolizjaDolLewo){
		prawo = true;
		DajDzwiek();
	}
	if(kolizjaGoraPrawo || kolizjaDolPrawo){
		prawo = false;
		DajDzwiek();
	}
		
	if(prawo){
		graczPrzyspieszenie.x =	predkoscPoruszania;
		aktualnaRamkaY = 3;
	} else {
		graczPrzyspieszenie.x =	-predkoscPoruszania;
		aktualnaRamkaY = 1;
	}
		
	x += graczPrzyspieszenie.x * Window.GetFrameTime();
	y += graczPrzyspieszenie.y * Window.GetFrameTime();

	skok = y + 15 >= wysokoscGruntu;

	if(skok)
		y = wysokoscGruntu - 15;
	

	animacja.ustawPozycje(1, x);
	animacja.ustawPozycje(2, y);
	animacja.ustawAktualnaRamke(2, aktualnaRamkaY);
	animacja.Aktualizacja(Window);

}
