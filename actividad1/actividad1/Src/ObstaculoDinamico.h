#pragma once
#include "SFMLRenderer.h"
#include "Avatar.h"


class ObstaculoDinamico
{
private:
	b2Body* ObstaculoBody;
	Avatar* ObstaculoAvatar;
	Texture textura;

public:
	ObstaculoDinamico(b2World *Phyworld, Vector2f Posicion, Vector2f Tamaño);
	void dibujarCaja(RenderWindow* wnd);
	b2Body* ObtenerBody();
};

