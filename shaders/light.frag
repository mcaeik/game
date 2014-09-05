uniform sampler2D texture;
uniform vec2 lightpos;
uniform float radius;
uniform float height;
uniform float width;
uniform vec4 light;

void main(void) {
	vec2 pos = gl_FragCoord.xy;
	pos.y = height - pos.y;

	float dis = distance (lightpos, pos);

	if (dis > radius) {
		gl_FragColor = gl_Color*vec4(0.0, 0.0, 0.0, 1.0);
		return;
	}

	float angel = atan (pos.y-lightpos.y, pos.x-lightpos.x);
	float px;
	float py;
	for (float d = 0.0; d < dis; d++) {
		px = cos(angel)*d+lightpos.x;
		py = sin(angel)*d+lightpos.y;

		if (texture2D (texture,vec2(px/width, py/height)) != vec4 (1.0, 1.0, 1.0, 1.0)) {
			gl_FragColor = gl_Color*vec4(0.0, 0.0, 0.0, 1.0);
			return;
		}
	}

	float att = 1.0-(dis/radius);
	gl_FragColor = gl_Color*(vec4(0.0, 0.0, 0.0, 1.0)+light*att);
}
