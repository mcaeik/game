class Light {
	private:

	public:
		sf::Vector2f position;
		sf::Color color;
		double radius;
};

class LightEngine {
	private:
		sf::RenderTexture btex, ltex, ttex, stex;
		sf::Sprite lspr, sspr, tspr;
		sf::Shader shadows, dark, blur;
		sf::RenderStates rs_add, rs_mul;

	public:
		sf::Color ambientcolor;
		sf::Vector2f screen;
		double resolution;

		void init ();
		void clear ();
		void draw (const sf::Drawable&);
		void add (Light);
		void shine (sf::RenderTarget&);
};

void LightEngine::init () {
	btex.create (screen.x, screen.y);
	ltex.create (resolution, resolution);
	ttex.create (resolution, resolution);
	stex.create (screen.x, screen.y);

	lspr.setTexture (btex.getTexture ());
	tspr.setTexture (ltex.getTexture ());
	sspr.setTexture (ttex.getTexture ());

	shadows.loadFromFile ("../shaders/light.frag", sf::Shader::Fragment);
	shadows.setParameter ("texture", sf::Shader::CurrentTexture);
	shadows.setParameter ("height", resolution);
	shadows.setParameter ("width", resolution);

	dark.loadFromFile ("../shaders/dark.frag", sf::Shader::Fragment);
	dark.setParameter ("texture", sf::Shader::CurrentTexture);
	dark.setParameter ("ambient", ambientcolor);

	blur.loadFromFile ("../shaders/blur.frag", sf::Shader::Fragment);
	blur.setParameter ("texture", sf::Shader::CurrentTexture);
	blur.setParameter ("blur_radius", 0.005);

	rs_add.blendMode = sf::BlendAdd;
	rs_add.shader = &blur;

	rs_mul.blendMode = sf::BlendMultiply;
	rs_mul.shader = &blur;
}

void LightEngine::clear () {
	btex.clear (sf::Color::White);
	stex.clear (ambientcolor);
}

void LightEngine::draw (const sf::Drawable& drawable) {
	btex.draw (drawable, &dark);
}

void LightEngine::add (Light light) {
	lspr.setTextureRect (sf::IntRect (light.position.x-light.radius, screen.y-light.position.y-light.radius, light.radius*2, light.radius*2));
	lspr.setScale (resolution/(light.radius*2), resolution/(light.radius*2));

	ltex.clear (sf::Color::White);
	ltex.draw (lspr);

	shadows.setParameter ("lightpos", resolution/2, resolution/2);
	shadows.setParameter ("radius", resolution/2);
	shadows.setParameter ("light", light.color);

	ttex.clear (sf::Color::White);
	ttex.draw (tspr, &shadows);

	sspr.setScale ((light.radius*2)/resolution, (light.radius*2)/resolution);
	sspr.setPosition (light.position.x-light.radius, screen.y-light.position.y-light.radius);

	stex.draw (sspr, rs_add);
}

void LightEngine::shine (sf::RenderTarget& rt) {
	sf::Sprite spr;
	spr.setTexture (stex.getTexture ());

	rt.draw (spr, rs_mul);
}
