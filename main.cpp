//Zewnetrzne biblioteki
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>
//Moje klasy
#include "gracz.h"
#include "globalne.h"
#include "kamera.h"
#include "interfejs.h"
#include "wrog.h"
#include "wrog_lewy.h"
#include "ladowaniezawartosci.h"


template <class Swoj, class Obcy>
void Kolizja(Swoj &player, Obcy &wrog, sf::Sound &kolizja, int &punkty, int &zycia){

    if((player.pobierzX() < wrog.pobierzX() + SZEROBIEKTU &&
		player.pobierzX() > wrog.pobierzX() &&
		player.pobierzY() + WYSGRACZ/2 > wrog.pobierzY() &&
		player.pobierzY() + WYSGRACZ/2 < wrog.pobierzY() + WYSOOBIEKTU)
			||
		(player.pobierzX() + SZERGRACZ > wrog.pobierzX() &&
		player.pobierzX() + SZERGRACZ < wrog.pobierzX() + SZEROBIEKTU &&
		player.pobierzY() + WYSGRACZ/2 > wrog.pobierzY() &&
		player.pobierzY() + WYSGRACZ/2 < wrog.pobierzY() + WYSOOBIEKTU)	
			||
		(player.pobierzX() + SZERGRACZ/2 > wrog.pobierzX() &&
		player.pobierzX() + SZERGRACZ/2 < wrog.pobierzX() + SZEROBIEKTU &&
		player.pobierzY() > wrog.pobierzY() &&
		player.pobierzY() + WYSGRACZ < wrog.pobierzY() + WYSOOBIEKTU))
	{
		kolizja.Play();
		player.x = player.startX;
		player.y = player.startY;
		--zycia;
	} else {
		if(player.pobierzX() + SZERGRACZ/2 > wrog.pobierzX() - 5 &&
			player.pobierzX() + SZERGRACZ/2 < wrog.pobierzX() + SZEROBIEKTU + 5 &&
			player.pobierzY() + WYSGRACZ > wrog.pobierzY()	&&
			player.pobierzY() < wrog.pobierzY() + WYSOOBIEKTU)
		{
			player.ZmusDoSkoku();
			
			if(typeid(wrog) == typeid (Wrog)){
				++punkty;
			} else if(typeid(wrog) == typeid (Wrog_Lewy)){
				punkty +=5;
			} else 
				punkty +=10;
		}
	}
}


int main(){
//STD
int punkty = 0,
	zycia = 3;
//Używane klasy SFML
	sf::RenderWindow Ekran(sf::VideoMode(SzerokoscEkranu, WysokoscEkranu, 32), "Gra 2D z prostymi przeciwnikami");
	sf::SoundBuffer bufor;
	sf::Sound kolizja;
	sf::Shape niezydetyfikowany_niebieski_obiekt = sf::Shape::Rectangle(0, 0, SZEROBIEKTU, WYSOOBIEKTU, sf::Color::Blue);
	sf::Event Zdarzenie;
	sf::View Gra;
	sf::View Inter;
//Moje klasy
	Gracz gracz;
	Kamera kamera;
	Interfejs miedzymordzie;
	Wrog enemy, enemy2;
	Wrog_Lewy enemy3;
	LadowanieZawartosci zawartosc("mapy/mapa1.txt");

//Inicjalizacja potrzebnego stuffu
	if( bufor.LoadFromFile("Kolizja.wav"))
		kolizja.SetBuffer(bufor);

	try{
		gracz.Inicjalizacja(zawartosc.MapVector, 100, 100, 400, 1000, 50, "player.png", 6, 4);
		gracz.UstawDzwiekSkoku("Jump.wav");
		enemy.Inicjalizacja(zawartosc.MapVector, 700, 100, 100, 1000, 50, "wrog.png", 6, 4);
		enemy2.Inicjalizacja(zawartosc.MapVector, 900, 100, 100, 1000, 50, "wrog.png", 6, 4);
		enemy3.Inicjalizacja(zawartosc.MapVector, 200, 100, 100, 1000, 50, "wrog2.png", 6, 4);
		
		miedzymordzie.Inicjalizacja("biblio.ttf");
	}
	catch(std::string wyj){
		std::cout << "Problem z załadowaniem pliku " << wyj << std::endl;
		return 0;
	}
	
	int rozmiar_mapy = zawartosc.MapVector[0].size();
	
	Ekran.UseVerticalSync(true);

//Główna pętla gry
	while( Ekran.IsOpened() ){

		while( Ekran.GetEvent(Zdarzenie)){
			if( (Zdarzenie.Type == sf::Event::Closed) || (Zdarzenie.Key.Code == sf::Key::Escape) )
				Ekran.Close();
		}

		Ekran.SetView(Gra);
		
		gracz.Aktualizacja(Ekran);
		
		enemy.Aktualizacja(Ekran);
		enemy2.Aktualizacja(Ekran);
		enemy3.Aktualizacja(Ekran);
		
		kamera.Aktualizacja(gracz.pobierzX(), gracz.pobierzY(), rozmiar_mapy);
		Kolizja(gracz, enemy, kolizja, punkty, zycia);
		Kolizja(gracz, enemy2, kolizja, punkty, zycia);
		Kolizja(gracz, enemy3, kolizja, punkty, zycia);


		Ekran.Clear();
		kamera.Rysuj(Ekran);
		zawartosc.DrawMap(Ekran);
		//Ekran.Draw(niezydetyfikowany_niebieski_obiekt);
		gracz.Rysuj(Ekran);
		
		enemy.Rysuj(Ekran);
		enemy2.Rysuj(Ekran);
		enemy3.Rysuj(Ekran);
		
		Ekran.SetView(Inter);
		miedzymordzie.Aktualizacja(zycia, punkty);
		miedzymordzie.Rysuj(Ekran);
		
		Ekran.Display();
	}

}
