#include "interfejs.h"


void Interfejs::Inicjalizacja(const char *nazwapliku){
	if(!FontInterfejsu.LoadFromFile(nazwapliku)){
		std::string wyjatek = nazwapliku;
		throw wyjatek;
	}

}


void Interfejs::Aktualizacja(int ile_hp, int ile_pkt){
	hp = ile_hp;
	pkt = ile_pkt;
}

void Interfejs::Rysuj(sf::RenderWindow &Window){
	sf::String Text;
	Text.SetFont(FontInterfejsu);
	Text.SetSize(60);
	
	ss.str("");
	ss << "zycia: " << hp;
	Text.SetText(ss.str());
	Window.Draw(Text);
	ss.str("");
	ss << "punkty: " << pkt;
	Text.SetText(ss.str());
	Text.Move(700.f, 0.f);
	Window.Draw(Text);
}
