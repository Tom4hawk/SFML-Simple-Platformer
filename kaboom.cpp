#include "kaboom.h"

void kaboom::Init(){
	bufor.LoadFromFile("kaboom.wav");
	Wybuch.SetBuffer(bufor);
}

void kaboom::DajDzwiek(){
	Wybuch.Play();
}
	
