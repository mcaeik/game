#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;
#include "../include/light.h"

int main () {
	sf::RenderWindow window (sf::VideoMode (800, 600, 16), "sfml");
	sf::Event event;

	vector <sf::RectangleShape> rs;
	sf::RectangleShape t;
	t.setSize (sf::Vector2f (50, 50));
	t.setFillColor (sf::Color::Red);

	sf::Clock fps;
	double time, atime = 0;

	LightEngine le;
	le.ambientcolor = sf::Color (16, 16, 16);
	le.screen = sf::Vector2f (800, 600);
	le.resolution = 256;
	le.init ();

	vector <Light> light;
	Light l;
	l.color = sf::Color::White;
	l.radius = 200;
	l.position = sf::Vector2f (400, 300);

	while (window.isOpen ()) {
		//fps
		time = fps.getElapsedTime ().asSeconds ();
		atime += time;
		fps.restart ();
		if (time != 0) cout << "\r" << 1.0/time << "     ";
		cout.flush ();

		while (window.pollEvent (event)) {
			if (event.type == sf::Event::Closed) window.close ();
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) window.close ();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				light.push_back (l);
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
				t.setPosition (sf::Mouse::getPosition (window).x-25, sf::Mouse::getPosition (window).y-25);
				rs.push_back (t);
			}
		}

		l.position = sf::Vector2f (sf::Mouse::getPosition (window).x, sf::Mouse::getPosition (window).y);

		window.clear (sf::Color::White);
		for (int i = 0; i < rs.size (); i ++) window.draw (rs [i]);

		le.clear ();
		for (int i = 0; i < rs.size (); i ++) le.draw (rs [i]);
		for (int i = 0; i < light.size (); i ++) le.add (light [i]);
		le.add (l);
		le.shine (window);

		window.display ();
	}

}
