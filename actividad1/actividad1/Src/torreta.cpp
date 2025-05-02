#include "torreta.h"
#include "Ragdoll.h"
#include "Box2DHelper.h"
#include "Game.h"
#include "iostream"

torreta::torreta(b2World *phyWorld, Vector2f tamaño,Vector2f posicion) {
    Cañon.loadFromFile("cañon.png");
    Soporte.loadFromFile("soporte.png");

    PosicionTorreta = posicion;

    TorretaBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, tamaño.x-2, tamaño.y, 1, 10, 0.5);

    TorretaAvatar = new Avatar(TorretaBody, new Sprite(Cañon));
    TorretaAvatar->SetPosition(b2Vec2(TorretaBody->GetPosition().x,TorretaBody->GetPosition().y+5));

    estante = Box2DHelper::CreateRectangularStaticBody(phyWorld, 5.0f, 10.0f);
    estante->SetTransform(b2Vec2(PosicionTorreta.x, 90), 0.0f);

    EstanteShape.setSize(Vector2f(10, 10));
    EstanteShape.setPosition(Vector2f(estante->GetPosition().x, estante->GetPosition().y));
    EstanteShape.setOrigin(Vector2f(5, 5));
    EstanteShape.setTexture(&Soporte);

}

void torreta::apuntar(RenderWindow *wnd) {
    //atan2 devuelve el angulo entre la diferencia de 2 puntos
    float valor = std::atan2(Mouse::getPosition(*wnd).y * 0.17 - TorretaBody->GetPosition().y, Mouse::getPosition(*wnd).x * 0.125 - TorretaBody->GetPosition().x);

    ValorEnGrados = valor * 180.0 / 3.14;
    TorretaBody->SetTransform(b2Vec2(PosicionTorreta.x,PosicionTorreta.y), valor);
}

void torreta::disparar(b2World *phyworld,RenderWindow *wnd) {
    
    Vector2f Pos;

    //el seno y -cos nos dan un angulo recto para la circunferencia de la torreta

    //cuenta calculada con un grafico
    //sen de grado + 90 (agregado para arreglar el angulo) con un radio multiplicado * 25
    Pos.x = sin((ValorEnGrados + 90) / 90) * 10;

    //-cos de grado + 90 (agregado para arreglar el angulo) con un radio multiplicado * 25
    Pos.y = -cos((ValorEnGrados + 90) / 90) * 10;

    //creamos los ragdolls a disparar
    Ragdoll* ragdoll = new Ragdoll(phyworld, Vector2f(Pos.x + PosicionTorreta.x-2, Pos.y + PosicionTorreta.y+2), ValorEnGrados);

    velocidad.x = ( Mouse::getPosition(*wnd).x - PosicionTorreta.x) * 50;
    velocidad.y = ((PosicionTorreta.y - Mouse::getPosition(*wnd).y) * 50) * -1;


    ragdoll->ObtenerPartes(1)->AplicarImpulso(b2Vec2(velocidad.x, velocidad.y), b2Vec2(-25, 25));
    municion.push_back(ragdoll);

    float valor = std::atan2(Mouse::getPosition(*wnd).y * 0.17 - TorretaBody->GetPosition().y, Mouse::getPosition(*wnd).x * 0.125 - TorretaBody->GetPosition().x);

    ValorEnGrados = valor * 180.0 / 3.14;
    TorretaBody->SetTransform(b2Vec2(12, 88), valor);
    }
   

void torreta::dibujarTorreta(RenderWindow *wnd) {
    TorretaAvatar->Actualizar();
    TorretaAvatar->Dibujar(*wnd);
    wnd->draw(EstanteShape);
    
   
   
    

    dibujarBalas(wnd);
}

void torreta::dibujarBalas(RenderWindow* wnd) {
    if (!municion.empty()){
        for (int i = 0; i < municion.size(); i++) {
                for (int j = 0; j < 6; j++) {
                    municion[i]->ObtenerPartes(j)->Actualizar();
                    municion[i]->ObtenerPartes(j)->Dibujar(*wnd);
                }
            }
    }
}

bool torreta::listoParaDisparar() {
    if (municion.empty()) {
        return false;
    }
    else {
        return true;
    }
}

b2Body* torreta::ObtenerBody() {
    return TorretaBody;
}