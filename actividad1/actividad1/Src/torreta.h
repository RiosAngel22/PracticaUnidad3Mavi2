#pragma once
#include "SFMLRenderer.h"
#include "Avatar.h"
#include "Ragdoll.h"

class torreta
{
private:
	RectangleShape* TorretaBody;
	Texture textura;
	std::vector <Ragdoll*> municion;
	Vector2f PosicionTorreta;
	Vector2f TamañoTorreta;

	Vector2f velocidad;

	float ValorEnGrados;

public:


	torreta(Vector2f tamaño , Vector2f posicion);
	void apuntar(RenderWindow *wnd);
	void disparar(b2World *phyworld,RenderWindow *wnd);
	void dibujarTorreta(RenderWindow *wnd);
	void dibujarBalas(RenderWindow* wnd);
	bool listoParaDisparar();

};

