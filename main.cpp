#include <iostream>

#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "raytracer.h"

int main()
{
    int width  = 800;
    int height = 600;

    Raytracer rt(width, height);

    //Mesh* box = new Mesh("res/box.obj", Vec3(-1.0f, 0.0f, 14.0f));
    //box->material = Material(Color(Color::LIGHT_GRAY), 20.0f, 0.0f);
    //rt.add(box);

    Light_Direction* light1 = new Light_Direction( Vec3(1.0f, -1.0f, 1.0f),
                                                   Color(0.9f, 0.88f, 0.83f),
                                                   1.0f );

    Light_Direction* light2 = new Light_Direction( Vec3( -1.0f, -0.5f,  1.0f),
                                                   Color( 0.45f, 0.45f, 0.5f),
                                                   1.0f );

    rt.add(light1);
    rt.add(light2);

    Sphere* sphere_left   = new Sphere( Vec3(-3.5f, -0.5f, 10.0f),  1.5f);
    sphere_left->material = Material(Color(Color::ORANGE), 40.0f, 0.0f);

    Sphere* sphere_middle   = new Sphere( Vec3( 0.0f, 1.0f, 12.0f), 3.0f);
    sphere_middle->material = Material(Color(Color::GREEN), 200.0f, 0.0f);

    Sphere* sphere_right   = new Sphere( Vec3( 2.5f, -0.5f, 9.0f), 1.5f);
    sphere_right->material = Material(Color(Color::PURPLE), 40.0f, 0.0f);

    rt.add(sphere_left);
    rt.add(sphere_middle);
    rt.add(sphere_right);

    Plane* plane = new Plane(Vec3(0.0f, -2.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    plane->material = Material(Color(Color::LIGHT_GRAY), 0.0, 0.0f);
    rt.add(plane);

    //uint8_t* img_data = rt.render();
    uint8_t* img_data = rt.frame;
    sf::Thread t1([&rt]() {
        rt.render();
    });
    t1.launch();


    sf::RenderWindow window(sf::VideoMode(width, height), "Raytracer");

    // Icon
    sf::Image icon;
    icon.loadFromFile("res/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    

    sf::Texture texture;
    texture.create(width, height);
    
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        texture.update(img_data);

        window.clear(sf::Color(Color::LIGHT_GRAY));
        window.draw(sprite);
        window.display();

        sf::sleep(sf::seconds(0.1f));
    }

    return 0;
}