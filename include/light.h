class Light {
	private:

	public:
		sf::Vector2f position;
		sf::Color color;
		double radius;
};

class LightEngine {
	private:
		sf::RenderTexture texblack, texlight, texshadow, texfinal, textemp;
		sf::Sprite lspr, sspr, tspr, fspr;
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
	textemp.create (screen.x, screen.y);
	texlight.create (resolution, resolution);
	texshadow.create (resolution, 1);
	texfinal.create (screen.x, screen.y);
	texfinal.setSmooth (true);


	lspr.setTexture (texblack.getTexture ());
	sspr.setTexture (texlight.getTexture ());
	tspr.setTexture (textemp.getTexture ());
	fspr.setTexture (textemp.getTexture ());

	shadows.loadFromFile ("../shaders/shadow_map.frag", sf::Shader::Fragment);
//	shadows.setParameter ("texture", sf::Shader::CurrentTexture);
	shadows.setParameter ("resolution", resolution);

	dark.loadFromFile ("../shaders/dark.frag", sf::Shader::Fragment);
	dark.setParameter ("texture", sf::Shader::CurrentTexture);
	dark.setParameter ("ambient", ambientcolor);

	render.loadFromFile ("../shaders/shadow_render.frag", sf::Shader::Fragment);
	render.setParameter ("stexture", texshadow.getTexture ());
	render.setParameter ("screen", screen);

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

	texshadow.draw (sspr, &shadows);

	render.setParameter ("color", light.color);
	render.setParameter ("lightpos", light.position);
	render.setParameter ("radius", light.radius);
	textemp.draw (fspr, &render);

	texfinal.draw (tspr, rs_add);
}

void LightEngine::shine (sf::RenderTarget& rt) {
	sf::Sprite spr;
	spr.setTexture (texfinal.getTexture ());

	rt.draw (spr, rs_mul);
}
