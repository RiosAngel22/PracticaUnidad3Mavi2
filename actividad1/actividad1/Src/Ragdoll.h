#pragma once
#include "SFMLRenderer.h"
#include "Avatar.h"

class Ragdoll
{
private:
	//cuerpo de box2d 
	b2Body* cabezaBody;
	Avatar* cabezaAvatar;

	b2Body* torsoBody;
	Avatar* torsoAvatar;

	b2Body* brazoIzqBody;
	Avatar* brazoIzqAvatar;

	b2Body* brazoDerBody;
	Avatar* brazoDerAvatar;

	b2Body* piernaIzqBody;
	Avatar* piernaIzqAvatar;

	b2Body* piernaDerBody;
	Avatar* piernaDerAvatar;

	b2DistanceJoint* cuello;

	b2DistanceJoint* hombroIzq;
	b2DistanceJoint* hombroDer;

	b2DistanceJoint* rodillaIzq;
	b2DistanceJoint* rodillaDer;

	std::vector<Avatar*> Extremidades;

	Texture Cara;
	Texture Torso;
	Texture Mano;
	Texture Pierna;


public:

	Ragdoll(b2World* phyworld,Vector2f posicion,float angulo);
	Avatar* ObtenerPartes(int extremidad);
};

