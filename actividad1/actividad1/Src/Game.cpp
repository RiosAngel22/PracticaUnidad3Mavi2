#include "Game.h"
#include "Box2DHelper.h"
#include "Ragdoll.h"
#include "ObstaculoDinamico.h"

// Constructor de la clase Game
Game::Game(int ancho, int alto, std::string titulo)
{
    // Inicialización de la ventana de renderizado
    wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
    wnd->setVisible(true);
    fps = 60;
    wnd->setFramerateLimit(fps);
    frameTime = 1.0f / fps;
    SetZoom(); // Configuración del zoom de la cámara
    InitPhysics(); // Inicialización del mundo físico
}

// Método principal que maneja el bucle del juego
void Game::Loop()
{
    while (wnd->isOpen())
    {
        wnd->clear(clearColor); // Limpia la ventana con un color especificado
        DoEvents(); // Procesa los eventos del sistema
        UpdatePhysics(); // Actualiza la simulación física
        DrawGame(); // Dibuja el juego en la ventana
        wnd->display(); // Muestra la ventana renderizada
    }
}

// Actualiza la simulación física
void Game::UpdatePhysics()
{
    phyWorld->Step(frameTime, 8, 8); // Avanza la simulación física
    phyWorld->ClearForces(); // Limpia las fuerzas aplicadas a los cuerpos
    phyWorld->DebugDraw();
}

// Dibuja los elementos del juego en la ventana
void Game::DrawGame()
{
    Color paredes = Color::Blue;

    // Dibujamos el suelo
    sf::RectangleShape groundShape(sf::Vector2f(500, 5));
    groundShape.setFillColor(paredes);
    groundShape.setPosition(0, 95);
    wnd->draw(groundShape);

    // Dibujamos las paredes
    sf::RectangleShape leftWallShape(sf::Vector2f(5, 100)); // Alto de la ventana
    leftWallShape.setFillColor(paredes);
    leftWallShape.setPosition(0, 0); // X = 100 para que comience donde termina el suelo
    wnd->draw(leftWallShape);

    sf::RectangleShape rightWallShape(sf::Vector2f(5, 100)); // Alto de la ventana
    rightWallShape.setFillColor(paredes);
    rightWallShape.setPosition(95, 0); // X = 90 para que comience donde termina el suelo
    wnd->draw(rightWallShape);

    sf::RectangleShape ceilingShape(sf::Vector2f(500, 5));
    ceilingShape.setFillColor(paredes);
    ceilingShape.setPosition(0, 0);
    wnd->draw(ceilingShape);


    Torreta->apuntar(wnd);
    Torreta->dibujarTorreta(wnd);

    caja1->dibujarCaja(wnd);
    caja2->dibujarCaja(wnd);
    caja3->dibujarCaja(wnd);
    caja4->dibujarCaja(wnd);

    plataforma1->DibujarObstaculo(wnd);
    plataforma2->DibujarObstaculo(wnd);
    plataforma3->DibujarObstaculo(wnd);

}

// Procesa los eventos del sistema
void Game::DoEvents()
{
    Event evt;
    while (wnd->pollEvent(evt))
    {
        switch (evt.type)
        {
        case Event::Closed:
            wnd->close(); // Cierra la ventana
            break;

        case Event::MouseButtonPressed:
            Torreta->disparar(phyWorld, wnd);
        }
    }
    
}

// Configura el área visible en la ventana de renderizado
void Game::SetZoom()
{
    View camara;
    camara.setSize(100.0f, 100.0f); // Tamaño del área visible
    camara.setCenter(50.0f, 50.0f); // Centra la vista en estas coordenadas
    wnd->setView(camara); // Asigna la vista a la ventana
}

// Inicializa el mundo físico y los elementos estáticos del juego
void Game::InitPhysics()
{    

    // Inicializa el mundo físico con la gravedad por defecto
    phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

    // Inicializa el renderizador de depuración para el mundo físico
    debugRender = new SFMLRenderer(wnd);
    debugRender->SetFlags(UINT_MAX); // Configura el renderizado para que muestre todo
    phyWorld->SetDebugDraw(debugRender);

    // Crea los elementos estáticos del juego (suelo y paredes)
    b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
    groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

    b2Body* ceilingBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
    ceilingBody->SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);
  
    b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
    leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

    b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
    rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

    Torreta = new torreta(phyWorld,Vector2f(15.0f, 10.0f), Vector2f(20.0f, 85.0f));

    caja1 = new ObstaculoDinamico(phyWorld, Vector2f(55.0f, 25.0f), Vector2f(5.0f, 6.0f));
    caja2 = new ObstaculoDinamico(phyWorld, Vector2f(35.0f, 65.0f), Vector2f(5.0f, 6.0f));
    caja3 = new ObstaculoDinamico(phyWorld, Vector2f(80.0f, 20.0f), Vector2f(5.0f, 6.0f));
    caja4 = new ObstaculoDinamico(phyWorld, Vector2f(65.0f, 50.0f), Vector2f(5.0f, 6.0f));


    plataforma1 = new ObstaculoEstatico(phyWorld, Vector2f(55.0f, 28.0f), Vector2f(10.0f, 2.0f),Color::Green);
    plataforma2 = new ObstaculoEstatico(phyWorld, Vector2f(35.0f, 60.0f), Vector2f(10.0f, 2.0f), Color::Green);
    plataforma3 = new ObstaculoEstatico(phyWorld, Vector2f(80.0f, 25.0f), Vector2f(10.0f, 2.0f), Color::Green);
    
    Resorte1 = Box2DHelper::CreateDistanceJoint(phyWorld, plataforma2->ObtenerBody(), plataforma2->ObtenerBody()->GetWorldCenter(), caja2->ObtenerBody(), caja2->ObtenerBody()->GetWorldCenter(), 10, 1,0.3);
    Resorte1->SetMaxLength(15);
    Resorte1->SetMinLength(1);

    Resorte2 = Box2DHelper::CreateDistanceJoint(phyWorld, plataforma1->ObtenerBody(), plataforma1->ObtenerBody()->GetWorldCenter(), caja4->ObtenerBody(), caja4->ObtenerBody()->GetWorldCenter(), 10, 0.2, 0.5);
    Resorte2->SetMaxLength(15);
    Resorte2->SetMinLength(1);

    Resorte1 = Box2DHelper::CreateDistanceJoint(phyWorld, plataforma3->ObtenerBody(), plataforma3->ObtenerBody()->GetWorldCenter(), caja4->ObtenerBody(), caja4->ObtenerBody()->GetWorldCenter(), 10, 0.2, 0.5);
    Resorte1->SetMaxLength(15);
    Resorte1->SetMinLength(1);


}

