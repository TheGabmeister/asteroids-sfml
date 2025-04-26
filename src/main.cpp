#include <SFML/Graphics.hpp>



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
    const float speed = 3.0f;

    sf::Texture texture;
    if (!texture.loadFromFile(RESOURCES_PATH "image.png")) {
        throw std::runtime_error("Failed to load image.png");
    }
    sf::Sprite playerSprite(texture);
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


        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            newPosition.x = playerPosition.x - speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            newPosition.x = playerPosition.x + speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            newPosition.y = playerPosition.y - speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            newPosition.y = playerPosition.y + speed;
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


        // DRAW
        ////////////////////////////////////////////////////////////////////////////////////
        window.clear();

        window.draw(playerSprite);


        window.display();
    }
}