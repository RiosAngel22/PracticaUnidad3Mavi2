#include "ObstaculoEstatico.h"
#include "Box2DHelper.h"

ObstaculoEstatico::ObstaculoEstatico(b2World* phyworld, Vector2f Posicion, Vector2f Tama�o, Color color){
	ObstaculoBody = Box2DHelper::CreateRectangularStaticBody(phyworld, Tama�o.x, Tama�o.y);
	ObstaculoBody->SetTransform(b2Vec2(Posicion.x, Posicion.y), 0.0f);

	Obstaculo.setSize(Tama�o);
	Obstaculo.setOrigin(Vector2f(Tama�o.x / 2, Tama�o.y / 2));
	Obstaculo.setPosition(Vector2f(ObstaculoBody->GetPosition().x, ObstaculoBody->GetPosition().y));
	Obstaculo.setFillColor(color);
}

void ObstaculoEstatico::DibujarObstaculo(RenderWindow* wnd) {
	wnd->draw(Obstaculo);
}