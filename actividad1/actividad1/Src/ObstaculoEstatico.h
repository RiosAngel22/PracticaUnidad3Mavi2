#pragma once
#include "SFMLRenderer.h"
#include "Avatar.h"

class ObstaculoEstatico
{
private:
	b2Body* ObstaculoBody;
	Avatar* ObstaculoAvatar;

	Texture textura;

public:
	ObstaculoEstatico(b2World *phyworld, Vector2f Posicion, Vector2f Tamaño, Color color);
	void DibujarObstaculo(RenderWindow* wnd);
	b2Body* ObtenerBody();
};

