#ifndef KABOOM_H
#define KABOOM_H
#include <SFML/Audio.hpp>
class kaboom
{
	public:
		void Init();
		void DajDzwiek();
		sf::Sound Wybuch;
		sf::SoundBuffer bufor;		
};

#endif
