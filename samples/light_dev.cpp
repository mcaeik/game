#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#include "../include/light.h"

int main () {
	sf::RenderWindow window (sf::VideoMode (800, 600, 16), "sfml");
	sf::Event event;

	sf::RectangleShape rs;
	rs.setPosition (350, 275);
	rs.setSize (sf::Vector2f (100, 50));
	rs.setFillColor (sf::Color::Red);

	sf::RectangleShape rg;
	rg.setPosition (300, 200);
	rg.setSize (sf::Vector2f (50, 50));
	rg.setFillColor (sf::Color::Green);

	Light l;
	l.setResolution (800, 600);
	l.setPosition (0, 0);
	l.setRadius (200);
	l.setRays (60);

	sf::Clock fps;
	double time;

	while (window.isOpen ()) {
		//fps
		time = fps.getElapsedTime ().asSeconds ();
		fps.restart ();

		if (time != 0) cout << "\r" << 1.0/time << "     ";
		cout.flush ();


		while (window.pollEvent (event)) {
			if (event.type == sf::Event::Closed) window.close ();
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) window.close ();
		}

		l.setPosition (sf::Mouse::getPosition (window).x, sf::Mouse::getPosition(window).y);

		window.clear (sf::Color (255, 255, 255));

		l.clear ();
		
		l.draw (rs);
		l.draw (rg);

		window.draw (rs);
		window.draw (rg);

		l.shine (window);
		window.display ();
	}

}
