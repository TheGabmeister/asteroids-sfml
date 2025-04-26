#include <SFML/Graphics.hpp>



int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({600u, 800u}), "CMake SFML Project");
    window.setFramerateLimit(144);


    // Initialize
    /////////////////////////////////////////////////////////////////////////////////////
    
    sf::Vector2f playerPosition{
        window.getSize().x / 2.f,
        window.getSize().y / 2.f
    };
    
    sf::Texture texture;
    if (!texture.loadFromFile(RESOURCES_PATH "image.png")) {
        throw std::runtime_error("Failed to load image.png");
    }
    sf::Sprite sprite(texture);
    //float spriteLength = sprite.getGlobalBounds().getCenter().x
    //std::cout << "Sprite length: " << spriteLength << std::endl;
    sprite.setOrigin(sprite.getGlobalBounds().getCenter());
    

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

        sprite.setPosition(playerPosition); 


        // DRAW
        ////////////////////////////////////////////////////////////////////////////////////
        window.clear();

        window.draw(sprite);


        window.display();
    }
}