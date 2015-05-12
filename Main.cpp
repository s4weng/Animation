#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <iostream>

int main()
{
    // setup window
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    window.setFramerateLimit(60);

    // load texture (spritesheet)
    sf::Texture textureWalk, textureStand;
    if (!textureWalk.loadFromFile("ArcherWalk.png") || !textureStand.loadFromFile("ArcherStand.png")){
        std::cout << "Failed to load player spritesheet!" << std::endl;
        return 1;
    }

    // set up the animations for all four directions (set spritesheet and push frames)
    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(textureWalk);
    walkingAnimationRight.addFrame(sf::IntRect(11, 11, 48, 70));
    walkingAnimationRight.addFrame(sf::IntRect(91, 12, 48, 70));
    walkingAnimationRight.addFrame(sf::IntRect(167, 8, 48, 70));
    walkingAnimationRight.addFrame(sf::IntRect(248, 10, 48, 70));
    walkingAnimationRight.addFrame(sf::IntRect(329, 10, 48, 70));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(textureWalk);
    walkingAnimationLeft.addFrame(sf::IntRect(330, 97, 48, 70));
    walkingAnimationLeft.addFrame(sf::IntRect(246, 97, 48, 70));
    walkingAnimationLeft.addFrame(sf::IntRect(172, 97, 48, 70));
    walkingAnimationLeft.addFrame(sf::IntRect(93, 97, 48, 70));
    walkingAnimationLeft.addFrame(sf::IntRect(9, 95, 48, 70));

    Animation standingDefaultRight;
    standingDefaultRight.setSpriteSheet(textureStand);
    standingDefaultRight.addFrame(sf::IntRect(9,9,48,70));

    Animation standingDefaultLeft;
    standingDefaultLeft.setSpriteSheet(textureStand);
    standingDefaultLeft.addFrame(sf::IntRect(10,98,48,70));


    Animation* currentAnimation = &standingDefaultRight;

    // set up AnimatedSprite
    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

    sf::Clock frameClock;

    float speed = 80.f;
    bool noKeyWasPressed = true;
    int direction = 1; //1 for right, 0 for left

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        sf::Time frameTime = frameClock.restart();

        // if a key was pressed set the correct animation and move correctly
        sf::Vector2f movement(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

            currentAnimation = &walkingAnimationLeft;
            movement.x -= speed;
            noKeyWasPressed = false;
            direction = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

            currentAnimation = &walkingAnimationRight;
            movement.x += speed;
            noKeyWasPressed = false;
            direction = 1;
        }

        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());

        // if no key was pressed stop the animation
        if (noKeyWasPressed){

        	if (direction == 1)
        		currentAnimation = &standingDefaultRight;
        	else
        		currentAnimation = &standingDefaultLeft;

            animatedSprite.stop();
        }

        noKeyWasPressed = true;

        // update AnimatedSprite
        animatedSprite.update(frameTime);

        // draw
        window.clear();
        window.draw(animatedSprite);
        window.display();
    }

    return 0;
}