#pragma once
#include "SFMLRenderer.h"

class ObstaculoEstatico
{
private:
	RectangleShape Obstaculo;
	b2Body* ObstaculoBody;

public:
	ObstaculoEstatico(b2World *phyworld, Vector2f Posicion, Vector2f Tama�o, Color color);
	void DibujarObstaculo(RenderWindow* wnd);
};

