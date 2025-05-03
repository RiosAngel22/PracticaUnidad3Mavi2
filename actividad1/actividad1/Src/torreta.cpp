#include "torreta.h"
#include "Ragdoll.h"
#include "Box2DHelper.h"
#include "Game.h"
#include "iostream"

torreta::torreta(b2World *phyWorld, Vector2f tamaño,Vector2f posicion) {
    Cañon.loadFromFile("cañon.png");
    Soporte.loadFromFile("soporte.png");

    PosicionTorreta = posicion;

    //Creamos el cuerpo de la torreta
    TorretaBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, tamaño.x, tamaño.y-2, 1, 10, 0.5);
    TorretaBody->SetTransform(b2Vec2(PosicionTorreta.x,PosicionTorreta.y), 0.0f);

    //creamos un avatar fisico para la torreta
    TorretaAvatar = new Avatar(TorretaBody, new Sprite(Cañon));
    TorretaAvatar->SetPosition(b2Vec2(TorretaBody->GetPosition().x, TorretaBody->GetPosition().y));

    //Creamos una imagen para el estante de la torreta
    EstanteShape.setSize(Vector2f(10, 15));
    EstanteShape.setPosition(Vector2f(PosicionTorreta.x, 85));
    EstanteShape.setOrigin(Vector2f(5, 5));
    EstanteShape.setTexture(&Soporte);

}

void torreta::apuntar(RenderWindow *wnd) {
    //atan2 devuelve el angulo entre la diferencia de 2 puntos
    float valor = std::atan2(Mouse::getPosition(*wnd).y * 0.17 - TorretaBody->GetPosition().y, Mouse::getPosition(*wnd).x * 0.125 - TorretaBody->GetPosition().x);

    //seteamos la rotacion de la torreta en grados
    ValorEnGrados = valor * 180.0 / 3.14;
    TorretaBody->SetTransform(b2Vec2(PosicionTorreta.x,PosicionTorreta.y), valor);
    TorretaAvatar->SetPosition(b2Vec2(TorretaBody->GetPosition().x, TorretaBody->GetPosition().y));

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

    //calculamos la velocidad entre la esquina inferior izquierda y la posicion actual del mouse
    //para obtener potencia maxima

    //usamos las posiciones basadas en la pantalla: 150 x , 800 y
    velocidad.x = ( Mouse::getPosition(*wnd).x - 150) * 50;
    velocidad.y = ((800 - Mouse::getPosition(*wnd).y) * 50);

    //le aplicamos la fuerza al torso del ragdoll, antes de meterlo al array
    ragdoll->ObtenerPartes(1)->AplicarImpulso(b2Vec2(velocidad.x, -velocidad.y), b2Vec2(-25, 25));
    municion.push_back(ragdoll);

    //corregimos el angulo del avatar torreta
    float valor = std::atan2(Mouse::getPosition(*wnd).y * 0.17 - TorretaBody->GetPosition().y, Mouse::getPosition(*wnd).x * 0.125 - TorretaBody->GetPosition().x);

    ValorEnGrados = valor * 180.0 / 3.14;
    TorretaBody->SetTransform(b2Vec2(12, 88), valor);
    }
   

void torreta::dibujarTorreta(RenderWindow *wnd) {
    //dibujamos torreta y balas
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
    //solo se muestran los ragdolls si estos existen
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