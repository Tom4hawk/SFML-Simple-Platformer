#include "gracz.h"

void Gracz::Inicjalizacja(std::vector < std::vector <int> > &Mapa, int koordynatystartowe_x, int koordynatystartowe_y, float predkosc_poruszania, float predkosc_skakania, float grawitacja_p, const char *nazwapliku, int ileklatek_x, int ileklatek_y){
	startX = x = koordynatystartowe_x;
	startY = y = koordynatystartowe_y;
	predkoscPoruszania = predkosc_poruszania;
	skok_predkosc =  predkosc_skakania;	
	grawitacja = grawitacja_p;
	MapaKolizji = Mapa;
	wysokoscGruntu = (MapaKolizji.size() - 2) * BLOCKSIZE;

	//Ładowanie sprajta
	if(!ObrazekGracz.LoadFromFile(nazwapliku)){
		std::string wyjatek = nazwapliku;
		throw wyjatek;
	}
	animacja.Inicjalizacja(x, y, ileklatek_x, ileklatek_y, ObrazekGracz);

	//Zerowanie
	aktualnaRamkaX = aktualnaRamkaY = 0;
	skok = false;
	graczPrzyspieszenie.x = 0;
	graczPrzyspieszenie.y = 0;
}
void Gracz::UstawDzwiekSkoku(const char *nazwapliku){
	if( bufor.LoadFromFile(nazwapliku))
		DzwiekSkoku.SetBuffer(bufor);
	else{
		std::string wyjatek = nazwapliku;
		throw wyjatek;
	}
		
	czy_dzwiek_skok = true;
}

void Gracz::ZmusDoSkoku(){
		graczPrzyspieszenie.y = -1.3*skok_predkosc;
		aktualnaRamkaY = 0;
	
		skok = false;
		
		if(czy_dzwiek_skok)
			DzwiekSkoku.Play();

}


void Gracz::kolizjaigrawitacja(){
	float bottom = (y + 54) / BLOCKSIZE; //rozmiary gracza!!!!!
	float left = (x / BLOCKSIZE); 
	float right = (x + 32) / BLOCKSIZE;//szerokość
	float top = (y / BLOCKSIZE);
	
	bool kolizjaGoraLewo = false;
	bool kolizjaGoraPrawo = false;
	bool kolizjaDolLewo = false;
	bool kolizjaDolPrawo = false;
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

void Gracz::Aktualizacja(sf::RenderWindow &Window){
	CzySieRusza = false;
	
	animacja.ustawAktywne(true);

	if( Window.GetInput().IsKeyDown(sf::Key::Right) || (Window.GetInput().GetJoystickAxis(0, sf::Joy::AxisX) > 0) ){
		graczPrzyspieszenie.x =	predkoscPoruszania;
		aktualnaRamkaY = 3;
		CzySieRusza = true;
	} else if( Window.GetInput().IsKeyDown(sf::Key::Left) || (Window.GetInput().GetJoystickAxis(0, sf::Joy::AxisX) < 0) ){
		graczPrzyspieszenie.x =	-predkoscPoruszania;
		aktualnaRamkaY = 1;
		CzySieRusza = true;
	} else{
		graczPrzyspieszenie.x = 0;
	}

	if( ( Window.GetInput().IsKeyDown(sf::Key::Space) || Window.GetInput().IsJoystickButtonDown(0,1) ) && skok ){
		graczPrzyspieszenie.y = -skok_predkosc;
		aktualnaRamkaY = 0;
		CzySieRusza = true;
		skok = false;
		
		if(czy_dzwiek_skok)
			DzwiekSkoku.Play();
	}

	if(!skok){
		graczPrzyspieszenie.y += grawitacja;
		aktualnaRamkaY = 0;
		CzySieRusza = true;
	} else
		graczPrzyspieszenie.y = 0;


	kolizjaigrawitacja();

	x += graczPrzyspieszenie.x * Window.GetFrameTime();
	y += graczPrzyspieszenie.y * Window.GetFrameTime();

	skok = y + 15 >= wysokoscGruntu;

	if(skok)
		y = wysokoscGruntu - 15;
	
	if(!CzySieRusza){
		animacja.ustawAktywne(false);
	}

	animacja.ustawPozycje(1, x);
	animacja.ustawPozycje(2, y);
	animacja.ustawAktualnaRamke(2, aktualnaRamkaY);
	animacja.Aktualizacja(Window);

}

void Gracz::Rysuj(sf::RenderWindow &Window){
	animacja.Rysuj(Window);
}

float Gracz::pobierzY(){
	return y;
}


float Gracz::pobierzX(){
	return x;
}

