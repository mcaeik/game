#include <cmath>

class Light {
	private:
		sf::RenderTexture rtex, btex, ntex;
		sf::Vector2f position;
		double radius;
		int rays;

	public:
		void setRadius (double);
		void setPosition (sf::Vector2f);
		void setPosition (double, double);
		void setRays (int);
		void setResolution (int, int);
		void clear ();
		void draw (const sf::Drawable&, const sf::RenderStates&);
		void shine (sf::RenderTarget&);
};

//
void Light::setRadius (double r) {
	radius = r;
	rtex.create (2*radius, 2*radius);
	btex.create (2*radius, 2*radius);
}
void Light::setPosition (sf::Vector2f p) {
	position = p;
}
void Light::setPosition (double x, double y) {
	position = sf::Vector2f (x, y);
}
void Light::setRays (int r) {
	rays = r;
}
void Light::setResolution (int x, int y) {
	ntex.create (x, y);
}
void Light::clear () {
	rtex.clear (sf::Color(255, 255, 255, 0));
	sf::View view = rtex.getDefaultView ();
	view.setCenter (position);
	rtex.setView (view);
}
void Light::draw (const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default) {
	rtex.draw (drawable, states);
}
void Light::shine (sf::RenderTarget& rt) {	
	sf::Image img;
	sf::Sprite spr, rspr;
	sf::ConvexShape sh;

	sh.setPointCount (rays);
	sh.setFillColor (sf::Color (255, 255, 255));

	spr.setTexture (rtex.getTexture ());
	spr.setColor (sf::Color (0, 0, 0));
	btex.clear (sf::Color (255, 255, 255, 0));
	btex.draw (spr);
	img = btex.getTexture().copyToImage ();

	double angel = 2.0*M_PI/rays, x, y;
	for (double i = 0, j = 0; i < 2*M_PI; i += angel, j ++) {
		for (int d = 0; d < radius; d ++) {
			x = (int) d*cos(i)+radius;
			y = (int) d*sin(i)+radius;

			if (img.getPixel (x, y).r != 255) {
				sh.setPoint ((int) j, sf::Vector2f (position.x + x - radius, position.y + y - radius));
				break;
			}
			else if (d == radius -1) {
				sh.setPoint ((int) j, sf::Vector2f (position.x + x - radius, position.y + y - radius));
			}
		}
	}

	ntex.clear (sf::Color(16, 16, 16));
	ntex.setView (rt.getView ());
	ntex.draw (sh);

	rspr.setTexture (ntex.getTexture ());
	rspr.setPosition (rt.getView().getCenter ().x, rt.getView().getCenter().y);
	rspr.setOrigin (rt.getView().getSize().x/2, rt.getView().getSize().y/2);
	rspr.setScale (1, -1);

	sf::RenderStates rs = sf::RenderStates::Default;
	rs.blendMode = sf::BlendMultiply;
	rt.draw (rspr, rs);
}
