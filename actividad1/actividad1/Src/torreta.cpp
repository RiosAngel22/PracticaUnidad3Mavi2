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

    ValorEnGrados = valor * 180.0 / 3.14;

    Vector2f Pos;

    //el seno y -cos nos dan un angulo recto para la circunferencia de la torreta

    //cuenta calculada con un grafico
    //sen de grado + 90 (agregado para arreglar el angulo) con un radio multiplicado * 25
    Pos.x = sin((ValorEnGrados + 90) / 90) * 25;

    //-cos de grado + 90 (agregado para arreglar el angulo) con un radio multiplicado * 25
    Pos.y = -cos((ValorEnGrados + 90) / 90) * 25;

    velocidad.x = (Mouse::getPosition(*wnd).x -PosicionTorreta.x);
    velocidad.y = (PosicionTorreta.y - Mouse::getPosition(*wnd).y) * -1;
    
    std::cout << velocidad.x << " : " << velocidad.y<<std::endl;
    std::cout << Mouse::getPosition(*wnd).x << " : " << Mouse::getPosition(*wnd).y << std::endl;

    TorretaBody->setRotation(ValorEnGrados);
}

void torreta::disparar(b2World *phyworld,RenderWindow *wnd) {
    //creamos los ragdolls a disparar

    Vector2f Pos;

    //el seno y -cos nos dan un angulo recto para la circunferencia de la torreta

    //cuenta calculada con un grafico
    //sen de grado + 90 (agregado para arreglar el angulo) con un radio multiplicado * 25
    Pos.x = sin((ValorEnGrados + 90) / 90) * 25;

    //-cos de grado + 90 (agregado para arreglar el angulo) con un radio multiplicado * 25
    Pos.y = -cos((ValorEnGrados + 90) / 90) * 25;

    Ragdoll* ragdoll = new Ragdoll(phyworld, Vector2f(Pos.x + 4.5, Pos.y + 104.5), ValorEnGrados);

    velocidad.x = ( Mouse::getPosition(*wnd).x - PosicionTorreta.x) * 50;
    velocidad.y = ((PosicionTorreta.y - Mouse::getPosition(*wnd).y) * 50) * -1;


    ragdoll->ObtenerPartes(1)->AplicarImpulso(b2Vec2(velocidad.x, velocidad.y), b2Vec2(-25, 25));
    municion.push_back(ragdoll);
    }
   

void torreta::dibujarTorreta(RenderWindow* wnd) {
    wnd->draw(*TorretaBody);
}

void torreta::dibujarBalas(RenderWindow* wnd) {
    if (!municion.empty()){
        for (int i = 0; i < municion.size(); i++) {
                for (int j = 0; j < 5; j++) {
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