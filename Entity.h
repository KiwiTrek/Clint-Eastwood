#pragma once
//Aqu� solo se declara la clase Entity con todas sus funciones y variables
/*Si quer�is hacer m�s clases, creais un header con declaraciones y luego un cpp
con las funciones definidas (como con el Game.h y el Game.cpp)*/
//No se hacen #include de game. Solo se declara la clase.
class Entity {
public:
	Entity();
	bool IsAlive();
private:
	bool is_alive;
};