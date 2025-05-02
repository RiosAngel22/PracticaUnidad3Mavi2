#include "ObstaculoEstatico.h"
#include "Box2DHelper.h"

ObstaculoEstatico::ObstaculoEstatico(b2World* phyworld, Vector2f Posicion, Vector2f Tama�o, Color color){
	textura.loadFromFile("plataforma.png");

	ObstaculoBody = Box2DHelper::CreateRectangularStaticBody(phyworld, Tama�o.x, Tama�o.y);
	ObstaculoBody->SetTransform(b2Vec2(Posicion.x, Posicion.y), 0.0f);

	ObstaculoAvatar = new Avatar(ObstaculoBody, new Sprite(textura));
}

void ObstaculoEstatico::DibujarObstaculo(RenderWindow* wnd) {
	ObstaculoAvatar->Actualizar();
	ObstaculoAvatar->Dibujar(*wnd);
}

b2Body* ObstaculoEstatico::ObtenerBody() {
	return ObstaculoBody;
}