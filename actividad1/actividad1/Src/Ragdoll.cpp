#include "Ragdoll.h"
#include "Box2DHelper.h"
#include "Game.h"
#include "vector"

using namespace sf;

Ragdoll::Ragdoll(b2World* phyWorld,Vector2f posicion) {
    //cabeza---------------------------------------------------------------------
    cabezaBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 5, 6, 5, 1, 1);
    cabezaBody->SetTransform(b2Vec2(posicion.x,posicion.y), 0.0f);

    cabezaAvatar = new Avatar(cabezaBody, new sf::Sprite(textura));


    //torso------------------------------------------------------------------------
    torsoBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 8, 12, 5, 1, 0);
    torsoBody->SetTransform(b2Vec2(posicion.x, posicion.y+10.0f), 0.0f);

    torsoAvatar = new Avatar(torsoBody, new sf::Sprite(textura));

    //brazos-------------------------------------------------------------------------
    brazoIzqBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 2, 10, 2, 1, 0.5);
    brazoIzqBody->SetTransform(b2Vec2(posicion.x-5.0f, posicion.y+10.0f), 0.0f);

    brazoIzqAvatar = new Avatar(brazoIzqBody, new sf::Sprite(textura));

    brazoDerBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 2, 10, 2, 1, 0.5);
    brazoDerBody->SetTransform(b2Vec2(posicion.x+5.0f, posicion.y+10.0f), 0.0f);

    brazoDerAvatar = new Avatar(brazoDerBody, new sf::Sprite(textura));



    //piernas----------------------------------------------------------------------------
    piernaIzqBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 3, 12, 2, 1, 0.5);
    piernaIzqBody->SetTransform(b2Vec2(posicion.x-2.0f, posicion.y+20.0f), 0.0f);

    piernaIzqAvatar = new Avatar(piernaIzqBody, new sf::Sprite(textura));

    piernaDerBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 3, 12, 2, 1, 0.5);
    piernaDerBody->SetTransform(b2Vec2(posicion.x+2.0f, posicion.y+20.0f), 0.0f);

    piernaDerAvatar = new Avatar(piernaDerBody, new sf::Sprite(textura));

    //creamos los resortes
    cuello = Box2DHelper::CreateDistanceJoint(phyWorld, cabezaBody, b2Vec2(cabezaBody->GetWorldCenter().x, cabezaBody->GetWorldCenter().y + 3), torsoBody, b2Vec2(torsoBody->GetWorldCenter().x, torsoBody->GetWorldCenter().y - 5), 1.0f, 5.0f, 0.5f);

    hombroIzq = Box2DHelper::CreateDistanceJoint(phyWorld, brazoIzqBody, b2Vec2(brazoIzqBody->GetWorldCenter().x, brazoIzqBody->GetWorldCenter().y - 5), torsoBody, b2Vec2(torsoBody->GetWorldCenter().x - 4, torsoBody->GetWorldCenter().y - 6), 0.0f, 15.0f, 2.0f);
    hombroDer = Box2DHelper::CreateDistanceJoint(phyWorld, brazoDerBody, b2Vec2(brazoDerBody->GetWorldCenter().x, brazoDerBody->GetWorldCenter().y - 5), torsoBody, b2Vec2(torsoBody->GetWorldCenter().x + 4, torsoBody->GetWorldCenter().y - 6), 0.0f, 15.0f, 2.0f);

    rodillaIzq = Box2DHelper::CreateDistanceJoint(phyWorld, piernaIzqBody, b2Vec2(piernaIzqBody->GetWorldCenter().x, piernaIzqBody->GetWorldCenter().y - 5), torsoBody, b2Vec2(torsoBody->GetWorldCenter().x - 2, torsoBody->GetWorldCenter().y + 6), 0.0f, 5.0f, 2.0f);
    rodillaDer = Box2DHelper::CreateDistanceJoint(phyWorld, piernaDerBody, b2Vec2(piernaDerBody->GetWorldCenter().x, piernaDerBody->GetWorldCenter().y - 5), torsoBody, b2Vec2(torsoBody->GetWorldCenter().x + 2, torsoBody->GetWorldCenter().y + 6), 0.0f, 5.0f, 2.0f);
    
    //agregamos las extremidades al vector
    Extremidades.push_back(cabezaAvatar);
    Extremidades.push_back(torsoAvatar);
    Extremidades.push_back(brazoIzqAvatar);
    Extremidades.push_back(brazoDerAvatar);
    Extremidades.push_back(piernaIzqAvatar);
    Extremidades.push_back(piernaDerAvatar);
}

Avatar* Ragdoll::ObtenerPartes(int extremidad) {
    return Extremidades[extremidad];
}