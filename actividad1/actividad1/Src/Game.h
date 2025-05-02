#pragma once
#include "torreta.h"
#include "ObstaculoDinamico.h"
#include "ObstaculoEstatico.h"

using namespace sf;
class Game
{
private:
	//Propiedades de la ventana
	int alto;
	int ancho;
	RenderWindow *wnd;
	Color clearColor;

	//objetos de box2d
	b2World *phyWorld;
	SFMLRenderer *debugRender;

	//tiempo de frame
	float frameTime;
	int fps;

	int velocidad = 10000;

	torreta *Torreta;
	ObstaculoDinamico *caja1;
	ObstaculoDinamico *caja2;
	ObstaculoDinamico *caja3;
	ObstaculoDinamico* caja4;

	ObstaculoEstatico* plataforma1;
	ObstaculoEstatico* plataforma2;
	ObstaculoEstatico* plataforma3;

	b2DistanceJoint* Resorte1;
	b2DistanceJoint* Resorte2;
	b2DistanceJoint* Resorte3;


public:

	//Constructores, destructores e inicializadores
	Game(int ancho, int alto,std::string titulo);
	void CreateEnemy(int x, int y);
	void InitPhysics();

	//Main game loop
	void Loop();
	void DrawGame();
	void UpdatePhysics();
	void DoEvents();
	void SetZoom();
	

	
};

