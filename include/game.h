#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

//klasa zawierajaca gre, ladowanie itd
class Game {
    private:

    public:
        void load (string filename);
        void play (sf::RenderWindow& window);
};

void Game::play (sf::RenderWindow& window) {
    sf::Event event;

    while (window.isOpen ()) {
        while (window.pollEvent (event)) {
            if (event.type == sf::Event::Closed) window.close ();
        }

        window.clear (sf::Color (255, 255, 255));
        window.display ();
    }
}


#endif // GAME_H_INCLUDED
