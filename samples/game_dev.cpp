#include <SFML/Graphics.hpp>
#include <string.h>

using namespace std;
#include "../include/game.h"

int main()
{
    sf::RenderWindow window (sf::VideoMode (800, 600, 0), "sfml-test", sf::Style::None | sf::Style::Close);

    Game game;
    game.play (window);

    return 0;
}
