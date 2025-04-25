#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    static sf::Texture texture;
    static bool loaded = false;
    static std::unique_ptr<sf::Sprite> sprite;
    if (!loaded) {
        if (!texture.loadFromFile(RESOURCES_PATH "image.png")) {
            // Handle error (optional)
        }
        sprite = std::make_unique<sf::Sprite>(texture);
        loaded = true;
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();


        if (sprite) {
            window.draw(*sprite);
        }

        window.display();
    }
}

void Initialize()
{

}