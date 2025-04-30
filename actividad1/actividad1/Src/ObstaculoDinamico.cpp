#include "ObstaculoDinamico.h"
#include "Box2DHelper.h"
#include "Game.h"

ObstaculoDinamico::ObstaculoDinamico(b2World *Phyworld, Vector2f Posicion, Vector2f Tamaño){
	textura.loadFromFile("rectangulo.png");

	ObstaculoBody = Box2DHelper::CreateRectangularDynamicBody(Phyworld, Tamaño.x, Tamaño.y, 1.5f, 0.5f, 0.2f);

	ObstaculoAvatar = new Avatar(ObstaculoBody, new sf::Sprite(textura));
	ObstaculoAvatar->SetPosition(b2Vec2(Posicion.x,Posicion.y));
}

void ObstaculoDinamico::dibujarCaja(RenderWindow *wnd){
	ObstaculoAvatar->Actualizar();
	ObstaculoAvatar->Dibujar(*wnd);
}