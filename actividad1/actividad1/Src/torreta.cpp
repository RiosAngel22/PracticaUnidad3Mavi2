#include "torreta.h"
#include "Ragdoll.h"
#include "Box2DHelper.h"
#include "Game.h"
#include "iostream"

torreta::torreta(Vector2f tamaño,Vector2f posicion) {
    //creamos la torreta
    PosicionTorreta = posicion;
    TamañoTorreta = tamaño;
    TorretaBody = new RectangleShape(TamañoTorreta);
    TorretaBody->setFillColor(Color::Green);
    TorretaBody->setPosition(PosicionTorreta);

}

void torreta::apuntar(RenderWindow *wnd) {
    //atan2 devuelve el angulo entre la diferencia de 2 puntos
    float valor = std::atan2(Mouse::getPosition(*wnd).y * 0.17 - TorretaBody->getPosition().y, Mouse::getPosition(*wnd).x * 0.125 - TorretaBody->getPosition().x);

    ValorEnGrados = valor * 180 / 3.14;

    TorretaBody->setRotation(ValorEnGrados);
}

void torreta::disparar(b2World *phyworld,RenderWindow *wnd) {
    //creamos los ragdolls a disparar

    Ragdoll* ragdoll = new Ragdoll(phyworld, Vector2f(PosicionTorreta.x+10,PosicionTorreta.y-15), ValorEnGrados);

    velocidad.x = (Mouse::getPosition(*wnd).x - PosicionTorreta.x);
    velocidad.y = (Mouse::getPosition(*wnd).y - PosicionTorreta.y);


    for (int i = 0; i < 6; i++) {
        ragdoll->ObtenerPartes(i)->AplicarImpulso(b2Vec2(velocidad.x, -velocidad.y), b2Vec2(0.0f, 0.0f));
    }
    municion.push_back(ragdoll);
}

void torreta::dibujarTorreta(RenderWindow* wnd) {
    wnd->draw(*TorretaBody);
}

void torreta::dibujarBalas(RenderWindow* wnd) {
    for (int i = 0; i < municion.size(); i++) {
        for (int j = 0; j < 5; j++) {
            municion[i]->ObtenerPartes(j)->Actualizar();
            municion[i]->ObtenerPartes(j)->Dibujar(*wnd);
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