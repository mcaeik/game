#define PI 3.141592;

uniform sampler2D texture;
uniform float resolution;

void main(void) {
	float angel = gl_TexCoord [0].x*2.0*PI;
	float cosx, sinx;
	float px, py;

	cosx = cos(angel);
	sinx = sin(angel);

	for (float distance = 0.0; distance < resolution/2.0; distance++) {
		px = cosx*distance+resolution/2.0;
		py = sinx*distance+resolution/2.0;

		if (texture2D (texture, vec2 (px/resolution, py/resolution)) != vec4 (1.0)) {
			gl_FragColor = vec4 (distance/resolution*2.0, distance/resolution*2.0, distance/resolution*2.0, 1.0);
			return;
		}
	}
	gl_FragColor = vec4 (1.0);
}
