class Light {
	private:

	public:
		sf::Vector2f position;
		sf::Color color;
		double radius;
};

class LightEngine {
	private:
		sf::RenderTexture texblack, texlight, texshadow, texfinal;
		sf::Sprite lspr, sspr, tspr;
		sf::Shader shadows, dark, render, blur;
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
	texblack.create (screen.x, screen.y);
	texlight.create (resolution, resolution);
	texshadow.create (resolution, 1);
	texfinal.create (screen.x, screen.y);

	lspr.setTexture (texblack.getTexture ());
	sspr.setTexture (texlight.getTexture ());
	tspr.setTexture (texlight.getTexture ());

	shadows.loadFromFile ("../shaders/shadow_map.frag", sf::Shader::Fragment);
//	shadows.setParameter ("texture", sf::Shader::CurrentTexture);
	shadows.setParameter ("resolution", resolution);

	dark.loadFromFile ("../shaders/dark.frag", sf::Shader::Fragment);
	dark.setParameter ("texture", sf::Shader::CurrentTexture);
	dark.setParameter ("ambient", ambientcolor);

	render.loadFromFile ("../shaders/shadow_render.frag", sf::Shader::Fragment);
	render.setParameter ("texture", sf::Shader::CurrentTexture);
	render.setParameter ("resolution", resolution);
	render.setParameter ("stexture", texshadow.getTexture ());

	rs_add.blendMode = sf::BlendAdd;
	rs_mul.blendMode = sf::BlendMultiply;
}

void LightEngine::clear () {
	texblack.clear (sf::Color::White);
	texfinal.clear (ambientcolor);
}

void LightEngine::draw (const sf::Drawable& drawable) {
	texblack.draw (drawable, &dark);
}

void LightEngine::add (Light light) {
	lspr.setTextureRect (sf::IntRect (light.position.x-light.radius, screen.y-light.position.y-light.radius, light.radius*2, light.radius*2));
	lspr.setScale (resolution/(light.radius*2), resolution/(light.radius*2));

	texlight.clear (sf::Color::White);
	texlight.draw (lspr);

	texshadow.clear (sf::Color::Red);
	texshadow.draw (sspr, &shadows);

	texlight.clear (sf::Color::White);
	render.setParameter ("color", light.color);
	texlight.draw (sspr, &render);

	tspr.setScale ((light.radius*2)/resolution, (light.radius*2)/resolution);
	tspr.setPosition (light.position.x - light.radius, screen.y-light.position.y - light.radius);
	texfinal.draw (tspr, rs_add);
}

void LightEngine::shine (sf::RenderTarget& rt) {
	sf::Sprite spr;
	spr.setTexture (texfinal.getTexture ());

	rt.draw (spr, rs_mul);
}
