#define PI 3.141592

uniform sampler2D texture;
uniform sampler2D stexture;
uniform vec4 color;
uniform vec2 lightpos;
uniform vec2 screen;
uniform float radius;

void main(void) {
	vec2 pos = gl_FragCoord.xy;
	pos.y = screen.y - pos.y;

	float dis = distance (pos, lightpos);
	if (dis >= radius) {
		gl_FragColor = vec4 (0.0, 0.0, 0.0, 1.0);
		return;
	}

	float angel = atan (pos.y - lightpos.y, pos.x - lightpos.x);

	if (angel < 0.0) angel = angel+2.0*PI;
	vec2 shadow = vec2 (angel/(2.0*PI), 0.0);

	if (dis/radius > texture2D (stexture, shadow).r) {
		gl_FragColor = vec4 (0.0, 0.0, 0.0, 1.0);
		return;
	}

	float att = 1.0 - pow(dis/radius, 0.5);

	gl_FragColor = vec4 (att, att, att, 1.0)*color;
}
