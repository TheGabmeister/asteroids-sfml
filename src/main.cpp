#include <SFML/Graphics.hpp>
#include <iostream>
#include <numbers>

int main()
{

    const sf::Vector2u windowDimensions{600u, 800u};
    auto window = sf::RenderWindow(sf::VideoMode(windowDimensions), "Asteroids");
    window.setFramerateLimit(144);

    // Initialize
    /////////////////////////////////////////////////////////////////////////////////////
    
    sf::Vector2f playerPosition{
        window.getSize().x / 2.f,
        window.getSize().y / 2.f
    };
    sf::Vector2f newPosition = playerPosition;
    float playerRotation = 0.f;

    const float movementSpeed = 200.0f;
    const float rotationSpeed = 200.0f;
    sf::Clock deltaClock;
    float deltaTime = 0.f;

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile(RESOURCES_PATH "image.png")) {
        throw std::runtime_error("Failed to load image.png");
    }
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setOrigin(playerSprite.getGlobalBounds().getCenter());

    // Game Loop
    /////////////////////////////////////////////////////////////////////////////////////
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        deltaTime = deltaClock.restart().asSeconds();

        // Get player's forward vector
        float radians = playerRotation * std::numbers::pi_v<float> / 180.0f;
        sf::Vector2f forward{ std::cos(radians), std::sin(radians) };

        // Handle input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            playerRotation = playerRotation - (rotationSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            playerRotation = playerRotation + (rotationSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            newPosition = playerPosition + forward * movementSpeed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            newPosition = playerPosition - forward * movementSpeed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
 
        }

        // Check if out of bounds
        if (newPosition.x < 0 || newPosition.x > windowDimensions.x)
        {
            newPosition.x = playerPosition.x;
        }
        if (newPosition.y < 0 || newPosition.y > windowDimensions.y)
        {
            newPosition.y = playerPosition.y;
        }

        playerPosition = newPosition;
        playerSprite.setPosition(playerPosition); 
        playerSprite.setRotation(sf::degrees(playerRotation));

        // DRAW
        ////////////////////////////////////////////////////////////////////////////////////
        window.clear();

        window.draw(playerSprite);

        window.display();
    }
}