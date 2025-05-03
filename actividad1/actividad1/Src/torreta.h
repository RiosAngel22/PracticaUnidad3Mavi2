#pragma once
#include "SFMLRenderer.h"
#include "Avatar.h"
#include "Ragdoll.h"

using namespace std;

class torreta
{
private:
	b2Body* TorretaBody;
	Avatar* TorretaAvatar;
	
	RectangleShape EstanteShape;

	Texture Ca�on;
	Texture Soporte;

	vector <Ragdoll*> municion;
	Vector2f PosicionTorreta;
	Vector2f Tama�oTorreta;

	Vector2f velocidad;

	float ValorEnGrados = 0;

public:


	torreta(b2World *phyworld,Vector2f tama�o , Vector2f posicion);
	void apuntar(RenderWindow *wnd);
	void disparar(b2World *phyworld,RenderWindow *wnd);
	void dibujarTorreta(RenderWindow *wnd);
	void dibujarBalas(RenderWindow* wnd);
	bool listoParaDisparar();

	b2Body* ObtenerBody();
};

