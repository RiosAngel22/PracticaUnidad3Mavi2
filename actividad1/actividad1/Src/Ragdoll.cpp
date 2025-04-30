#include "Ragdoll.h"
#include "Box2DHelper.h"
#include "Game.h"

using namespace sf;

Ragdoll::Ragdoll(b2World* phyWorld,Vector2f posicion,float angulo) {
    textura.loadFromFile("rectangulo.png");

    //cabeza---------------------------------------------------------------------
    cabezaBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 1.8 , 2 , 5, 1, 1);
    cabezaBody->SetTransform(b2Vec2(posicion.x,posicion.y-0.5), 0.0f);

    cabezaAvatar = new Avatar(cabezaBody, new sf::Sprite(textura));


    //torso------------------------------------------------------------------------
    torsoBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 3, 7, 5, 1, 0);
    torsoBody->SetTransform(b2Vec2(posicion.x, posicion.y+4.5f), 0.0f);

    torsoAvatar = new Avatar(torsoBody, new sf::Sprite(textura));

    //brazos-------------------------------------------------------------------------
    brazoIzqBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 1, 5, 2, 1, 0.5);
    brazoIzqBody->SetTransform(b2Vec2(posicion.x-2.0f, posicion.y+4.5f), 0.0f);

    brazoIzqAvatar = new Avatar(brazoIzqBody, new sf::Sprite(textura));

    brazoDerBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 1, 5, 2, 1, 0.5);
    brazoDerBody->SetTransform(b2Vec2(posicion.x+2.0f, posicion.y+4.5f), 0.0f);

    brazoDerAvatar = new Avatar(brazoDerBody, new sf::Sprite(textura));



    //piernas----------------------------------------------------------------------------
    piernaIzqBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 1.3, 6, 2, 1, 0.5);
    piernaIzqBody->SetTransform(b2Vec2(posicion.x-1.0f, posicion.y+11.5f), 0.0f);

    piernaIzqAvatar = new Avatar(piernaIzqBody, new sf::Sprite(textura));

    piernaDerBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 1.3, 6, 2, 1, 0.5);
    piernaDerBody->SetTransform(b2Vec2(posicion.x+1.0f, posicion.y+11.5f), 0.0f);

    piernaDerAvatar = new Avatar(piernaDerBody, new sf::Sprite(textura));

    //creamos los resortes
    cuello = Box2DHelper::CreateDistanceJoint(phyWorld, cabezaBody, b2Vec2(cabezaBody->GetWorldCenter().x, cabezaBody->GetWorldCenter().y), torsoBody, b2Vec2(torsoBody->GetWorldCenter().x, torsoBody->GetWorldCenter().y-4), 1.0f, 5.0f, 0.5f);

    hombroIzq = Box2DHelper::CreateDistanceJoint(phyWorld, brazoIzqBody, b2Vec2(brazoIzqBody->GetWorldCenter().x, brazoIzqBody->GetWorldCenter().y - 3), torsoBody, b2Vec2(torsoBody->GetWorldCenter().x - 0.5, torsoBody->GetWorldCenter().y - 2.5f), 0.0f, 15.0f, 3.0f);
    hombroDer = Box2DHelper::CreateDistanceJoint(phyWorld, brazoDerBody, b2Vec2(brazoDerBody->GetWorldCenter().x, brazoDerBody->GetWorldCenter().y - 3), torsoBody, b2Vec2(torsoBody->GetWorldCenter().x + 0.5, torsoBody->GetWorldCenter().y - 2.5f), 0.0f, 15.0f, 3.0f);

    rodillaIzq = Box2DHelper::CreateDistanceJoint(phyWorld, piernaIzqBody, b2Vec2(piernaIzqBody->GetWorldCenter().x, piernaIzqBody->GetWorldCenter().y - 3), torsoBody, b2Vec2(torsoBody->GetWorldCenter().x - 0.2, torsoBody->GetWorldCenter().y + 3), -1.0f, 5.0f, 8.0f);
    rodillaDer = Box2DHelper::CreateDistanceJoint(phyWorld, piernaDerBody, b2Vec2(piernaDerBody->GetWorldCenter().x, piernaDerBody->GetWorldCenter().y - 3), torsoBody, b2Vec2(torsoBody->GetWorldCenter().x + 0.2, torsoBody->GetWorldCenter().y + 3), -1.0f, 5.0f, 8.0f);
    
    //agregamos las extremidades al vector
    Extremidades.push_back(cabezaAvatar);
    Extremidades.push_back(torsoAvatar);
    Extremidades.push_back(brazoIzqAvatar);
    Extremidades.push_back(brazoDerAvatar);
    Extremidades.push_back(piernaIzqAvatar);
    Extremidades.push_back(piernaDerAvatar);

    torsoBody->SetTransform(b2Vec2(torsoBody->GetPosition().x, torsoBody->GetPosition().y), angulo);
}

Avatar* Ragdoll::ObtenerPartes(int extremidad) {
    return Extremidades[extremidad];
}