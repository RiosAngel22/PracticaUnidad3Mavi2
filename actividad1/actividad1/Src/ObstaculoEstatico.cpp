#include "ObstaculoEstatico.h"
#include "Box2DHelper.h"

ObstaculoEstatico::ObstaculoEstatico(b2World* phyworld, Vector2f Posicion, Vector2f Tamaño, Color color){
	ObstaculoBody = Box2DHelper::CreateRectangularStaticBody(phyworld, Tamaño.x, Tamaño.y);
	ObstaculoBody->SetTransform(b2Vec2(Posicion.x, Posicion.y), 0.0f);

	Obstaculo.setSize(Tamaño);
	Obstaculo.setOrigin(Vector2f(Tamaño.x / 2, Tamaño.y / 2));
	Obstaculo.setPosition(Vector2f(ObstaculoBody->GetPosition().x, ObstaculoBody->GetPosition().y));
	Obstaculo.setFillColor(color);
}

void ObstaculoEstatico::DibujarObstaculo(RenderWindow* wnd) {
	wnd->draw(Obstaculo);
}